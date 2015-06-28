/**
 * dataMerger.h
 */
#ifndef DATAMERGER_H
#define DATAMERGER_H

#include "sample.h"
#include "droneCollection.h"

/**
 * @brief data merger class
 * @details [long description]
 */
class CDataMerger
{
public:
  CDataMerger();
  virtual ~CDataMerger();

  CDroneCollection merge(const std::vector<CSample>& samples);
};

#endif
