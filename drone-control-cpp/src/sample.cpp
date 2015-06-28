/**
 * sample.cpp
 */

#include "sample.h"

/**
 * @brief Constructor
 */
CSample::CSample()
{}

/**
 * @brief Destructor
 */
CSample::~CSample()
{}

/**
 * @brief Destructor
 */
void
CSample::setIsReference(const bool bIsReference)
{
  bIsReference_ = bIsReference;
}

/**
 * @brief Destructor
 */
bool
CSample::getIsReference() const
{
  return bIsReference_;
}
