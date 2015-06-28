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
  bool bIsReference_;
};

#endif
