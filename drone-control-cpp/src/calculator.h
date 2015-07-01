/**
 * calculator.h
 */
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <opencv2/video/video.hpp>

/**
 * @brief Drone class
 * @details [long description]
 */
class CCalculator
{
public:
  explicit CCalculator(const int id);
  virtual ~CCalculator();

private:
  int id_;
  cv::KalmanFilter kf_;
};

#endif
