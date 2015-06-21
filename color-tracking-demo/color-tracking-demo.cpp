// color-tracking-demo.cpp

#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <deque>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

// class to track objects with
class CTracker
{
public:
  typedef std::vector<int> tObjects;
  typedef cv::Point3i tPosition;
  typedef std::deque<tPosition> tPositions;
  typedef std::map<int, tPositions> tObjectPositions;

  CTracker();
  virtual ~CTracker();

  void setSize(const size_t size);
  void setObject(const int index, const tPosition& position);

  const size_t getSize() const;
  const tObjects getObjects() const;
  const tPosition getObjectPosition(const int index) const;

  const tPosition getLastKnownObjectPosition(const int index, int& where) const;

private:
  void resizeObjects();

  tObjectPositions positions_;
  size_t size_;

};

CTracker::CTracker()
 : size_(10)
{}

CTracker::~CTracker()
{}

void
CTracker::setObject(const int index, const tPosition& position)
{
  positions_[index].push_back(position);
  if (positions_[index].size() > size_)
  {
    positions_[index].pop_front();
  }

  for (tObjectPositions::const_iterator itrPositions = positions_.begin()
                                      ; itrPositions != positions_.end()
                                      ; ++itrPositions)
  {
    std::cout << itrPositions->first << " :";
    for (tPositions::const_iterator itrPosition = itrPositions->second.begin()
                                  ; itrPosition != itrPositions->second.end()
                                  ; ++itrPosition)
    {
      std::cout << " " << *itrPosition;
    }
    std::cout << std::endl;
  }
}

void
CTracker::setSize(const size_t size)
{
  size_ = size;
  this->resizeObjects();
}

const CTracker::tObjects
CTracker::getObjects() const
{
  tObjects objects;
  for (tObjectPositions::const_iterator itr = positions_.begin()
                                      ; itr != positions_.end()
                                      ; ++itr)
  {
    objects.push_back(itr->first);
  }
  return objects;
}

const CTracker::tPosition
CTracker::getObjectPosition(const int index) const
{
  tPosition position(-1, -1, -1);
  const tObjectPositions::const_iterator itr = positions_.find(index);
  if (itr != positions_.end())
  {
    position = itr->second.back();
  }
  return position;
}

const CTracker::tPosition
CTracker::getLastKnownObjectPosition(const int index, int& where) const
{
  where = -1;
  tPosition position(-1, -1, -1);
  const tObjectPositions::const_iterator itr = positions_.find(index);
  if (itr != positions_.end())
  {
    for (int i = itr->second.size() - 1; i > 0 ; --i)
    {
      const tPosition& lastKnownPosition = itr->second.at(i);
      if (lastKnownPosition.x == -1 &&
          lastKnownPosition.y == -1 &&
          lastKnownPosition.z == -1)
      {
        // position invalid
      }
      else
      {
        // position valid
        position = lastKnownPosition;
        where = itr->second.size() - i - 1;
      }
    }
  }
  else
  {
    std::cerr << "CTracker::getLastKnownObjectPosition() requested index " << index << " does not exist" << std::endl;
  }
  return position;
}

void
CTracker::resizeObjects()
{
  for (tObjectPositions::iterator itr = positions_.begin()
                                ; itr != positions_.end()
                                ; ++itr)
  {
    while (itr->second.size() > size_)
    {
      itr->second.pop_front();
    }
  }
}

// HSV high/low ranges struct
class CHSVRanges
{
public:
  CHSVRanges();
  virtual ~CHSVRanges();

  int iLowH; int iHighH;
  int iLowS; int iHighS;
  int iLowV; int iHighV;
};

CHSVRanges::CHSVRanges()
 : iLowH(0), iHighH(179)
 , iLowS(0), iHighS(255)
 , iLowV(0), iHighV(255)
{}

CHSVRanges::~CHSVRanges()
{}

// clicked point class
class CClickedPoint
{
public:
  CClickedPoint();
  virtual ~CClickedPoint();

  cv::Point point_;
  bool bUpdated_;
};

CClickedPoint::CClickedPoint()
 : point_(0, 0)
 , bUpdated_(false)
{}

CClickedPoint::~CClickedPoint()
{}

// clicked trackbar class
class CClickedTrackbar
{
public:
  CClickedTrackbar();
  virtual ~CClickedTrackbar();

  int iPosition_;
  bool bUpdated_;
};

CClickedTrackbar::CClickedTrackbar()
 : iPosition_(0)
 , bUpdated_(false)
{}

CClickedTrackbar::~CClickedTrackbar()
{}

// callback for mouse events on a window
void
mouseCallbackOnWindow(int event, int x, int y, int flags, void* pData)
{
  CClickedPoint* pClickedPoint = static_cast<CClickedPoint*>(pData);
  if (pClickedPoint != NULL)
  {
    if (event == cv::EVENT_LBUTTONDOWN)
    {
      pClickedPoint->point_.x = x;
      pClickedPoint->point_.y = y;
      pClickedPoint->bUpdated_ = true;
    }
  }
}

// callback for mouse events on a trackbar
void
mouseCallbackOnTrackbar(int position, void* pData)
{
  CClickedTrackbar* pClickedTrackbar = static_cast<CClickedTrackbar*>(pData);
  if (pClickedTrackbar != NULL)
  {
    pClickedTrackbar->iPosition_ = position;
    pClickedTrackbar->bUpdated_ = true;
  }
}

// init
bool
initVideoCapture(cv::VideoCapture& videoCapture)
{
  // set video capture properties for MacBook' iSight camera
  videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 500);
  videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 600);

  // try to open the video source
  videoCapture.open(0);
  if (!videoCapture.isOpened())
  {
    std::cerr << "Could not open video capture device" << std::endl;
    return false;
  }
  return true;
}

// create a window
bool
createWindow(const std::string& sWindowName, const CClickedPoint* pCallbackData = NULL)
{
  // create window
  cv::namedWindow(sWindowName, CV_WINDOW_AUTOSIZE);
  // bind mouse callback function
  cv::setMouseCallback(sWindowName, mouseCallbackOnWindow, (void*)pCallbackData);
  // should always succeed
  return true;
}

// add a trackbar to a window
bool
addTrackbar(
  const std::string& sWindowName,
  const std::string& sTrackbarName,
  int* value,
  const int count = 255,
  const CClickedTrackbar* pCallbackData = NULL)
{
  cv::createTrackbar(sTrackbarName, sWindowName, value, count, mouseCallbackOnTrackbar, (void*)pCallbackData);
  return true;
}

// main entry point
int
main(int argc, char** argv)
{
  int iDebug = 0;
  if (argc == 2)
  {
    iDebug = std::atoi(argv[1]);
    std::cout << "debug level=" << iDebug << std::endl;
  }

  // create video capture object
  cv::VideoCapture videoCapture;
  const bool bVideoCaptureInitialized = initVideoCapture(videoCapture);

  // create windows
  // Input
  const std::string sInputWindow("Input");
  CClickedPoint InputWindowClickedPoint;
  createWindow(sInputWindow, &InputWindowClickedPoint);
  // const std::string sInputWindowHSV("Input HSV");
  // createWindow(sInputWindowHSV, NULL);
  // Result
  const std::string sResultWindow("Result");
  const std::string sTrackingResultWindow("Tracking");
  createWindow(sTrackingResultWindow, NULL);
  // Controls
  const std::string sControlsWindow("Controls");
  createWindow(sControlsWindow);
  const std::string sControlRangeH("Range H");
  const std::string sControlRangeS("Range S");
  const std::string sControlRangeV("Range V");
  int rangeH = 10; // initial range value
  int rangeS = 10; // initial range value
  int rangeV = 10; // initial range value
  const int maxRangeH = 50; // really large ranges make no sense
  const int maxRangeS = 50; // really large ranges make no sense
  const int maxRangeV = 50; // really large ranges make no sense
  CClickedTrackbar ControlsWindowClickedTrackbarH;
  CClickedTrackbar ControlsWindowClickedTrackbarS;
  CClickedTrackbar ControlsWindowClickedTrackbarV;
  addTrackbar(sControlsWindow, sControlRangeH, &rangeH, maxRangeH, &ControlsWindowClickedTrackbarH);
  addTrackbar(sControlsWindow, sControlRangeS, &rangeS, maxRangeS, &ControlsWindowClickedTrackbarS);
  addTrackbar(sControlsWindow, sControlRangeV, &rangeV, maxRangeV, &ControlsWindowClickedTrackbarV);

  // init Kalman filter
  int dynamParams = 4; // ?
  int measureParams = 2; // ?
  cv::KalmanFilter kf1(dynamParams, measureParams);
  cv::KalmanFilter kf2(dynamParams, measureParams);
  // kf.transitionMatrix
  // kf.controlMatrix
  // kf.measurementMatrix

  kf1.transitionMatrix = *(cv::Mat_<float>(4, 4) <<
    1,0,1,0,
    0,1,0,1,
    0,0,1,0,
    0,0,0,1);
  kf2.transitionMatrix = *(cv::Mat_<float>(4, 4) <<
    1,0,1,0,
    0,1,0,1,
    0,0,1,0,
    0,0,0,1);

  // init...
  setIdentity(kf1.measurementMatrix);
  setIdentity(kf1.processNoiseCov, cv::Scalar::all(1e-4));
  setIdentity(kf1.measurementNoiseCov, cv::Scalar::all(1e-1));
  setIdentity(kf1.errorCovPost, cv::Scalar::all(.1));
  setIdentity(kf2.measurementMatrix);
  setIdentity(kf2.processNoiseCov, cv::Scalar::all(1e-4));
  setIdentity(kf2.measurementNoiseCov, cv::Scalar::all(1e-1));
  setIdentity(kf2.errorCovPost, cv::Scalar::all(.1));

  const int iUsePredictionIfLost = 1; // use prediction 1 time if object is lost (temporarily)

  if (bVideoCaptureInitialized)
  {
    // always start updating the first color
    int iColorToUpdateIndex = 0;
    typedef std::set<std::string> tSetOfNames;
    tSetOfNames setOfWindowNames;
    std::map<int, cv::Mat> mThresholdedSelectedImg;
    typedef std::map<int, cv::Vec3b> tSelectedColor;
    tSelectedColor mHSVSelectedColor;
    typedef std::map<int, CHSVRanges> tSelectedRanges;
    tSelectedRanges mHSVRanges;
    typedef std::map<int, cv::KalmanFilter> tKalmanFilters;
    tKalmanFilters kalmanFilters;
    typedef std::map<int, CTracker> tTrackers;
    tTrackers trackers;
    typedef std::map<int, int> tTrackersPredictions;
    tTrackersPredictions trackersPredictions;

    // forever
    for(;;)
    {
      cv::Mat frame;
      // grab frame
      videoCapture >> frame;
      // flip to make it mirror-like
      cv::flip(frame, frame, 1);

      cv::Mat imgTracking;
      frame.copyTo(imgTracking);

      // show it
      cv::imshow(sInputWindow, frame);

      // convert to HSV
      cv::Mat imgHSV;
      cv::cvtColor(frame, imgHSV, cv::COLOR_BGR2HSV);
      // cv::imshow(sInputWindowHSV, imgHSV);

      // get clicked point color
      bool bPointHasChanged = false;
      if (InputWindowClickedPoint.bUpdated_ == true)
      {
        if (iDebug > 1)
        {
          std::cout << "InputWindowClickedPoint updated" << std::endl;
        }
        const int x = InputWindowClickedPoint.point_.x;
        const int y = InputWindowClickedPoint.point_.y;
        InputWindowClickedPoint.bUpdated_ = false;
        const cv::Vec3b hsv = imgHSV.at<cv::Vec3b>(y, x);
        if (iDebug > 3)
        {
          std::cout <<  "h=" << static_cast<int>(hsv[0])
                    << " s=" << static_cast<int>(hsv[1])
                    << " v=" << static_cast<int>(hsv[2]) << std::endl;
        }
        mHSVSelectedColor[iColorToUpdateIndex] = hsv;
        bPointHasChanged = true;
      }

      if (ControlsWindowClickedTrackbarH.bUpdated_ == true ||
          ControlsWindowClickedTrackbarS.bUpdated_ == true ||
          ControlsWindowClickedTrackbarV.bUpdated_ == true ||
          bPointHasChanged == true)
      {
        bPointHasChanged = false;
        if (iDebug > 1)
        {
          std::cout << "ControlsWindowClickedTrackbar updated" << std::endl;
        }
        ControlsWindowClickedTrackbarH.bUpdated_ = false;
        ControlsWindowClickedTrackbarS.bUpdated_ = false;
        ControlsWindowClickedTrackbarV.bUpdated_ = false;
        if (iDebug > 3)
        {
          std::cout <<  "h range=" << rangeH
                    << " s range=" << rangeS
                    << " v range=" << rangeV << std::endl;
        }

        // get references to the values to be updated
        CHSVRanges& ranges = mHSVRanges[iColorToUpdateIndex];
        cv::Vec3b& hsv = mHSVSelectedColor[iColorToUpdateIndex];
        // update range thresholds
        ranges.iLowH  = hsv[0] - rangeH;
        ranges.iHighH = hsv[0] + rangeH;
        ranges.iLowS  = hsv[1] - rangeS;
        ranges.iHighS = hsv[1] + rangeS;
        ranges.iLowV  = hsv[2] - rangeV;
        ranges.iHighV = hsv[2] + rangeV;
      }

      // threshold images
      for (tSelectedRanges::const_iterator itr = mHSVRanges.begin()
                                         ; itr != mHSVRanges.end()
                                         ; ++itr)
      {
        // check if kalman filter is initialized
        const tKalmanFilters::const_iterator itrKalmanFound = kalmanFilters.find(itr->first);
        if (itrKalmanFound == kalmanFilters.end())
        {
          // not found; create
          // std::cout << "creating KalmanFilter for object " << itr->first << std::endl;
          // kalmanFilters[itr->first] = kf1;//cv::KalmanFilter(kf);
        }

        if (itr->first == 0)
        {
          std::cout << "using kf1" << std::endl;
          kalmanFilters[itr->first] = kf1;
        }
        else
        {
          std::cout << "using kf2" << std::endl;
          kalmanFilters[itr->first] = kf2;
        }

        // first predict
        cv::Mat prediction = kalmanFilters[itr->first].predict();
        // correct prediction so it is inside image bounds
        if (prediction.at<float>(0) > imgTracking.cols)
        {
          prediction.at<float>(0) = imgTracking.cols;
        }
        else if (prediction.at<float>(0) < 0.0)
        {
          prediction.at<float>(0) = 0.0;
        }
        if (prediction.at<float>(1) > imgTracking.rows)
        {
          prediction.at<float>(1) = imgTracking.rows;
        }
        else if (prediction.at<float>(1) < 0.0)
        {
          prediction.at<float>(1) = 0.0;
        }
        if (iDebug > 6)
        {
          std::cout << "predicted object " << itr->first << " is at: x=" << prediction.at<float>(0) << ", y=" << prediction.at<float>(1) << std::endl;
        }

        cv::Point cross_v_top(prediction.at<float>(0),    std::max((float)0, prediction.at<float>(1) - 10));
        cv::Point cross_v_bottom(prediction.at<float>(0), std::min((float)imgTracking.rows, prediction.at<float>(1) + 10));
        cv::Point cross_h_left(std::max((float)0,                 prediction.at<float>(0) - 10), prediction.at<float>(1));
        cv::Point cross_h_right(std::min((float)imgTracking.cols, prediction.at<float>(0) + 10), prediction.at<float>(1));

        cv::line(imgTracking, cross_v_top, cross_v_bottom, cv::Scalar(0, 255, 0));
        cv::line(imgTracking, cross_h_left, cross_h_right, cv::Scalar(0, 255, 0));

        cv::Mat imgThresholded;
        cv::inRange(
          imgHSV,
          cv::Scalar(itr->second.iLowH,  itr->second.iLowS,  itr->second.iLowV),
          cv::Scalar(itr->second.iHighH, itr->second.iHighS, itr->second.iHighV),
          imgThresholded);

        // use the same index to store the image
        mThresholdedSelectedImg[itr->first] = imgThresholded;

        // contours variables
        typedef std::vector<std::vector<cv::Point> > tContours;
        tContours contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::Mat dilatedThreshold;
        const int iDilationSize = 10; // TODO: make configurable
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, // || cv::MORPH_CROSS || cv::MORPH_ELLIPSE
                                                    cv::Size(2*iDilationSize+1, 2*iDilationSize+1),
                                                    cv::Point(iDilationSize, iDilationSize));
        // apply some dilation
        // TODO: see what is the best filtering / blob detection method
        cv::dilate(imgThresholded, dilatedThreshold, element);
        // find contours
        cv::findContours(
          dilatedThreshold,
          contours,
          hierarchy,
          CV_RETR_EXTERNAL, // retrieves only the extreme outer contours
          CV_CHAIN_APPROX_SIMPLE);

        bool bObjectFound = false;
        if (contours.size() > 0)
        // for (tContours::const_iterator itrContours = contours.begin()
        //                              ; itrContours != contours.end()
        //                              ; ++itrContours)
        {
          // idea: use area as z-axis parameter indicator
          const double area = cv::contourArea(*(contours.end()-1));
          // object may not be too small nor too big
          if (area > 500 && area < 5000) // todo: make configurable
          {
            bObjectFound = true;
          }

          if (bObjectFound == true)
          {
            trackersPredictions[itr->first] = 0;
            const cv::Rect obj = boundingRect(*(contours.end()-1)); // largest contour is at end
            if (iDebug > 6)
            {
              std::cout << "object " << itr->first << " is at: x=" << obj.x + obj.width / 2 << ", y=" << obj.y + obj.height / 2 << " area=" << area << std::endl;
            }

            const int obj_center_x = obj.x + obj.width / 2;
            const int obj_center_y = obj.y + obj.height / 2;

            cv::Mat measurement(2, 1, CV_32F);
            measurement.at<float>(0, 0) = obj_center_x;
            measurement.at<float>(0, 1) = obj_center_y;

            // correct
            cv::Mat estimated = kalmanFilters[itr->first].correct(measurement);
            estimated.at<float>(0); // x
            estimated.at<float>(1); // y

            if (iDebug > 6)
            {
              std::cout << "object " << itr->first << " estimated is at: x=" << estimated.at<float>(0) << ", y=" << estimated.at<float>(1) << std::endl;
            }

            const CTracker::tPosition position(estimated.at<float>(0), estimated.at<float>(1), -1);
            trackers[itr->first].setObject(0, position);

            cv::Point cross_v_top(estimated.at<float>(0),    std::max((float)0, estimated.at<float>(1) - 10));
            cv::Point cross_v_bottom(estimated.at<float>(0), std::min((float)imgTracking.rows, estimated.at<float>(1) + 10));
            cv::Point cross_h_left(std::max((float)0,                 estimated.at<float>(0) - 10), estimated.at<float>(1));
            cv::Point cross_h_right(std::min((float)imgTracking.cols, estimated.at<float>(0) + 10), estimated.at<float>(1));

            cv::line(imgTracking, cross_v_top, cross_v_bottom, cv::Scalar(0, 0, 255));
            cv::line(imgTracking, cross_h_left, cross_h_right, cv::Scalar(0, 0, 255));

            // draw rectangle around contour in the same color as the selected color
            cv::Mat hsv(1, 1, imgTracking.type(), cv::Scalar(mHSVSelectedColor[itr->first][0], mHSVSelectedColor[itr->first][1], mHSVSelectedColor[itr->first][2]));
            cv::Mat bgr;
            cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);
            const cv::Vec3b colorVec = bgr.at<cv::Vec3b>(0, 0);
            const cv::Scalar rectColor(colorVec[0], colorVec[1], colorVec[2]);
            cv::line(imgTracking, cv::Point(obj.x, obj.y), cv::Point(obj.x, obj.y+obj.height), rectColor);
            cv::line(imgTracking, cv::Point(obj.x, obj.y), cv::Point(obj.x+obj.width, obj.y), rectColor);
            cv::line(imgTracking, cv::Point(obj.x+obj.width, obj.y+obj.height), cv::Point(obj.x+obj.width, obj.y), rectColor);
            cv::line(imgTracking, cv::Point(obj.x+obj.width, obj.y+obj.height), cv::Point(obj.x, obj.y+obj.height), rectColor);
          }
          else
          {
            if (iDebug > 3)
            {
              std::cout << "no object found! too small or too big object!" << std::endl;
            }
            if (trackersPredictions[itr->first] < iUsePredictionIfLost)
            {
              trackersPredictions[itr->first]++;
              if (iDebug > 3)
              {
                std::cout << "using latest prediction for object " << itr->first << std::endl;
              }
              const CTracker::tPosition position(prediction.at<float>(0), prediction.at<float>(1), -1);
              trackers[itr->first].setObject(0, position);
            }
            else
            {
              const CTracker::tPosition position(-1, -1, -1);
              trackers[itr->first].setObject(0, position);
            }
          }
        }
        else
        {
          if (iDebug > 3)
          {
            std::cout << "no object found!" << std::endl;
          }
          if (trackersPredictions[itr->first] < iUsePredictionIfLost)
          {
            trackersPredictions[itr->first]++;
            if (iDebug > 3)
            {
              std::cout << "using latest prediction for object " << itr->first << std::endl;
            }
            const CTracker::tPosition position(prediction.at<float>(0), prediction.at<float>(1), -1);
            trackers[itr->first].setObject(0, position);
          }
          else
          {
            const CTracker::tPosition position(-1, -1, -1);
            trackers[itr->first].setObject(0, position);
          }
        }

        if (iDebug > 0)
        {
          // combine thresholded on original image
          frame.copyTo(imgThresholded, imgThresholded);

          // create result window
          std::stringstream ss;
          ss << sResultWindow << " ";
          ss << itr->first;
          const std::string sWindowName = ss.str();
          // lookup window name in set, if it doesn't exist; create it
          const tSetOfNames::const_iterator foundName = setOfWindowNames.find(sWindowName);
          if (foundName != setOfWindowNames.end())
          {
            createWindow(sWindowName, NULL);
          }

          // show result
          cv::imshow(sWindowName, imgThresholded);
        }
      }

      // show object detection in tracking window
      cv::imshow(sTrackingResultWindow, imgTracking);

      // give imshow some time to show the result
      // so have a 1 ms delay
      // the pressed key is the value for switch
      switch (cv::waitKey(1))
      {
        case -1: // no key
          // do nothing
          break;
        case 27: // esc
          if (iDebug > 2)
          {
            std::cout << "key: ESC pressed" << std::endl;
          }
          return EXIT_SUCCESS;
          break;
        case 49: // '1'
          if (iDebug > 2)
          {
            std::cout << "key: 1 pressed" << std::endl;
          }
          iColorToUpdateIndex = 0;
          break;
        case 50: // '2'
          if (iDebug > 2)
          {
            std::cout << "key: 2 pressed" << std::endl;
          }
          iColorToUpdateIndex = 1;
          break;
        case 51: // '3'
          if (iDebug > 2)
          {
            std::cout << "key: 3 pressed" << std::endl;
          }
          iColorToUpdateIndex = 2;
          break;
        case 100: // 'd'
          iDebug++;
          std::cout << "debug level=" << iDebug << std::endl;
          break;
        case 68: // 'D'
          iDebug--;
          std::cout << "debug level=" << iDebug << std::endl;
          break;
        default:
          // do nothing
          break;
      }
    }
  }
  else
  {
    std::cerr << "Failed to initialize video capture device" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
