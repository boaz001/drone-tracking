/**
 * sample.h
 */
#ifndef SAMPLE_H
#define SAMPLE_H

/**
 * @brief Sample class
 * @details [long description]
 */
class CSample
{
public:
  CSample();
  virtual ~CSample();

  // @brief
  void setIsReference(const bool bIsReference);
  // @brief
  bool getIsReference() const;
  // @brief

private:
  // a sample contains at least the amount of data to construct a drone
  // and possibly more... (data format specific settings (e.g. frame rate))
  bool bIsReference_;
};

#endif
