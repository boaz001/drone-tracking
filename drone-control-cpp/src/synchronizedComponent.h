/**
 * synchronizedComponent.h
 */
#ifndef SYNCHRONIZEDCOMPONENT_H
#define SYNCHRONIZEDCOMPONENT_H

/**
 * @brief Synchronized Component Interface
 * @details [long description]
 */
class ISynchronizedComponent
{
public:
  ISynchronizedComponent() {};
  virtual ~ISynchronizedComponent() {};

  // @brief
  virtual void tick() = 0;
  // @brief
  // virtual double getSamplePeriod() const = 0;
  // @brief
  virtual void setSamplePeriod(const double dSamplePeriod) = 0;
};

#endif
