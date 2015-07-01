/**
 * calculator.h
 */
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <opencv2/video/video.hpp>

/**
 * @brief Calculator class
 * @details [long description]
 */
class CCalculator
{
public:
  explicit CCalculator(const int id);
  virtual ~CCalculator();

private:
  cv::Mat getAxMatrix() const;
  cv::Mat getAyMatrix() const;
  cv::Mat getAzMatrix() const;
  cv::Mat getAMatrix() const;
  cv::Mat getBxMatrix() const;
  cv::Mat getByMatrix() const;
  cv::Mat getBzMatrix() const;
  cv::Mat getBMatrix() const;

  int id_;
  cv::KalmanFilter kf_;
};

#endif
