/**
 * dataMerger.h
 */
#ifndef DATAMERGER_H
#define DATAMERGER_H

#include "sample.h"
#include "droneCollection.h"
#include <map>

/**
 * @brief data merger class
 * @details [long description]
 */
class CDataMerger
{
public:
  typedef int tReferenceID;
  typedef int tActualID;

  CDataMerger();
  virtual ~CDataMerger();

  // @brief
  CDroneCollection merge(const std::vector<CSample>& samples);

  // @brief
  void bind(const tReferenceID& refID, const tActualID& actID);

private:
  // how are reference and OptiTrack ID's bound?
  typedef std::map<tReferenceID, tActualID> tDroneBindings;
  tDroneBindings droneBindings_;
};

#endif
