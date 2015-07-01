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

static const float tau = 30, omega = 10, zeta = 0.7;

/**
 * @brief Constructor
 */
CCalculator::CCalculator(const int id)
 : id_(id)
 , kf_(dynamParams, measureParams, controlParams, CV_32F)
{
  std::cout << "CCalculator::CCalculator( " << id_ << " )" << std::endl;

  const cv::Mat A = getAMatrix();
  std::cout << "A:\n " << A << std::endl;

  const cv::Mat B = getBMatrix();
  std::cout << "B:\n " << B << std::endl;

  const cv::Mat Ax = getAxMatrix();
  const cv::Mat Bx = getBxMatrix();

  const cv::Mat identity = cv::Mat::eye(Ax.size(), Ax.type());
  const cv::Mat psi = identity * h + (Ax * h * h) / 2 + (Ax * Ax * h * h * h) / 6;
  const cv::Mat phi = identity + Ax * psi;
  const cv::Mat mat_gamma = psi * Bx;

  std::cout << "phi:\n " << phi << std::endl;
  std::cout << "mat_gamma:\n " << mat_gamma << std::endl;

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

  // discrete pole creation
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

  // coeffs are in reverse order
  cv::Mat coeffs = (cv::Mat_<float>(1, 4) << d,c,b,a);
  std::cout << "coeffs:\n " << coeffs << std::endl;
  cv::Mat roots;
  float p1 = cv::solvePoly(coeffs, roots);
  std::cout << "p1: " << p1 << "\nroots:\n " << roots << std::endl;

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

/**
 * @brief getAMatrix
 */
cv::Mat
CCalculator::getAMatrix() const
{
  const cv::Mat Ax = getAxMatrix();
  const cv::Mat Ay = getAyMatrix();
  const cv::Mat Az = getAzMatrix();

  const cv::Mat A = cv::Mat::zeros(dynamParams, dynamParams, CV_32F);
  Ax.copyTo(A(cv::Rect(dynamParams / 3 * 0, dynamParams / 3 * 0, Ax.cols, Ax.rows)));
  Ay.copyTo(A(cv::Rect(dynamParams / 3 * 1, dynamParams / 3 * 1, Ay.cols, Ay.rows)));
  Az.copyTo(A(cv::Rect(dynamParams / 3 * 2, dynamParams / 3 * 2, Az.cols, Ay.rows)));

  return A;
}

/**
 * @brief getAxMatrix
 */
cv::Mat
CCalculator::getAxMatrix() const
{
  return (cv::Mat_<float>(dynamParams_x, dynamParams_x) <<
    0,1,0,
    0,0,1,
    0,0,-tau_x);
}

/**
 * @brief getAyMatrix
 */
cv::Mat
CCalculator::getAyMatrix() const
{
  return (cv::Mat_<float>(dynamParams_y, dynamParams_y) <<
    0,1,0,
    0,0,1,
    0,0,-tau_y);
}

/**
 * @brief getAzMatrix
 */
cv::Mat
CCalculator::getAzMatrix() const
{
  return (cv::Mat_<float>(dynamParams_z, dynamParams_z) <<
    0,1,0,
    0,0,1,
    0,0,-tau_z);
}

/**
 * @brief getBMatrix
 */
cv::Mat
CCalculator::getBMatrix() const
{
  const cv::Mat Bx = getBxMatrix();
  const cv::Mat By = getByMatrix();
  const cv::Mat Bz = getBzMatrix();

  const cv::Mat B = cv::Mat::zeros(dynamParams, 3, CV_32F);
  Bx.copyTo(B(cv::Rect(0, dynamParams / 3 * 0, Bx.cols, Bx.rows)));
  By.copyTo(B(cv::Rect(1, dynamParams / 3 * 1, By.cols, By.rows)));
  Bz.copyTo(B(cv::Rect(2, dynamParams / 3 * 2, Bz.cols, Bz.rows)));

  return B;
}

/**
 * @brief getBxMatrix
 */
cv::Mat
CCalculator::getBxMatrix() const
{
  return (cv::Mat_<float>(dynamParams_x, 1) <<
    0,
    0,
    gain_x);
}

/**
 * @brief getByMatrix
 */
cv::Mat
CCalculator::getByMatrix() const
{
  return (cv::Mat_<float>(dynamParams_y, 1) <<
    0,
    0,
    gain_y);
}

/**
 * @brief getBzMatrix
 */
cv::Mat
CCalculator::getBzMatrix() const
{
  return (cv::Mat_<float>(dynamParams_z, 1) <<
    0,
    0,
    gain_z);
}
