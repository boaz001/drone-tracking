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

  // @brief
  CDroneCollection merge(const std::vector<CSample>& samples);

  // @brief
  void bind(const std::string& str, const int id);

private:
  // how are reference and OptiTrack ID's bound?
  typedef tReferenceID std::string;
  typedef std::mat<tReferenceID, int> tDroneBindings
  tDroneBindings droneBindings_;
};

#endif
