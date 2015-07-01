/**
 * calculator.cpp
 */

#include "calculator.h"
#include <iostream>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>

static const int dynamParams_x = 3;
static const int dynamParams_y = 3;
static const int dynamParams_z = 3;
static const int dynamParams = dynamParams_x + dynamParams_y + dynamParams_z; // Dimensionality of the state.
static const int measureParams = 3; // Dimensionality of the measurement.
static const int controlParams = 3; // Dimensionality of the control vector.
static const float h = 0.1;
static const float tau_x = 0.2, tau_y = 0.2, tau_z = 0.2;
static const float gain_x = 2.0, gain_y = 2.0, gain_z = 2.0;

/**
 * @brief Constructor
 */
CCalculator::CCalculator(const int id)
 : id_(id)
 , kf_(dynamParams, measureParams, controlParams, CV_32F)
{
  std::cout << "CCalculator::CCalculator( " << id_ << " )" << std::endl;

  const cv::Mat A_x = (cv::Mat_<float>(dynamParams_x, dynamParams_x) <<
    0,1,0,
    0,0,1,
    0,0,-tau_x);

  const cv::Mat A_y = (cv::Mat_<float>(dynamParams_y, dynamParams_y) <<
    0,1,0,
    0,0,1,
    0,0,-tau_y);

  const cv::Mat A_z = (cv::Mat_<float>(dynamParams_z, dynamParams_z) <<
    0,1,0,
    0,0,1,
    0,0,-tau_z);

  const cv::Mat A = cv::Mat::zeros(dynamParams, dynamParams, CV_32F);
  A_x.copyTo(A(cv::Rect(0, 0, 3, 3)));
  A_y.copyTo(A(cv::Rect(3, 3, 3, 3)));
  A_z.copyTo(A(cv::Rect(6, 6, 3, 3)));

  std::cout << "A:\n" << A << std::endl;

  const cv::Mat B_x = (cv::Mat_<float>(dynamParams_x, 1) <<
    0,
    0,
    gain_x);

  const cv::Mat B_y = (cv::Mat_<float>(dynamParams_y, 1) <<
    0,
    0,
    gain_y);

  const cv::Mat B_z = (cv::Mat_<float>(dynamParams_z, 1) <<
    0,
    0,
    gain_z);

  const cv::Mat B = cv::Mat::zeros(dynamParams, 3, CV_32F);
  B_x.copyTo(B(cv::Rect(0, 0, 1, 3)));
  B_y.copyTo(B(cv::Rect(1, 3, 1, 3)));
  B_z.copyTo(B(cv::Rect(2, 6, 1, 3)));

  std::cout << "B:\n" << B << std::endl;

  const cv::Mat identity = cv::Mat::eye(A_x.size(), A_x.type());
  const cv::Mat psi = identity * h + (A_x * h * h) / 2 + (A_x * A_x * h * h * h) / 6;
  const cv::Mat phi = identity + A_x * psi;
  const cv::Mat mat_gamma = psi * B_x;

  std::cout << "phi:\n" << phi << std::endl;
  std::cout << "mat_gamma:\n" << mat_gamma << std::endl;

  // init Kalman filter
  // A
  kf_.transitionMatrix = A;

  // B
  kf_.controlMatrix = B;

  // C
  kf_.measurementMatrix = *(cv::Mat_<float>(dynamParams, measureParams) <<
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0);

  // wat anders...
  // float omega1, omega2, zeta;
  // float a = omega2 * zeta + omega2;
  // float b = omega1 * omega2 + omega1;
  // float c = omega1 * omega1 * omega2;

  // cv::Mat coeffs = (cv::Mat_<float>(1, 4) << 1,a,b,c);
  // cv::Mat roots;
  // float p1 = cv::solvePoly(coeffs, roots);
  // std::cout << "roots:\n" << roots << std::endl;

  // discrete pole creation
  float tau = 30, omega = 10, zeta = 0.7;

  float omega_ster = omega * std::sqrt(1 - std::pow(zeta, 2.0));
  float beta = std::cos(omega_ster * h);
  float gamma = std::exp(-tau * h);
  float alpha = std::exp(-zeta * omega * h);

  float a1 = -2 * alpha * beta;
  float a2 = std::pow(alpha, 2.0);
  float a = 1;
  float b = (a1 - gamma);
  float c = (a2 - a1 * gamma);
  float d = (-a2 * gamma);

  std::cout << "a: " << a << " b: " << b << " c: " << c << " d: " << d << std::endl;

  cv::Mat coeffs = (cv::Mat_<float>(1, 4) << d,c,b,a);
  cv::Mat roots;
  std::cout << "coeffs:\n" << coeffs << std::endl;
  float p1 = cv::solvePoly(coeffs, roots);
  std::cout << "p1: " << p1 << "\nroots:\n" << roots << std::endl;

  // init...
  // setIdentity(kf1.measurementMatrix);
  // setIdentity(kf1.processNoiseCov, cv::Scalar::all(1e-4));
  // setIdentity(kf1.measurementNoiseCov, cv::Scalar::all(1e-1));
  // setIdentity(kf1.errorCovPost, cv::Scalar::all(.1));
  // setIdentity(kf2.measurementMatrix);
  // setIdentity(kf2.processNoiseCov, cv::Scalar::all(1e-4));
  // setIdentity(kf2.measurementNoiseCov, cv::Scalar::all(1e-1));
  // setIdentity(kf2.errorCovPost, cv::Scalar::all(.1));
}

/**
 * @brief Destructor
 */
CCalculator::~CCalculator()
{
  std::cout << "CCalculator::~CCalculator()" << std::endl;
}
