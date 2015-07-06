/**
 * referenceDataCollector.cpp
 */

#include "referenceDataCollector.h"
#include <iostream>

/**
 * @brief Constructor
 */
CReferenceDataCollector::CReferenceDataCollector()
 : IDataCollector()
 , dSamplePeriod_(1000.0)
 , pFbxManager_(NULL)
 , pFbxScene_(NULL)
{
  std::cout << "CReferenceDataCollector::CReferenceDataCollector()" << std::endl;
  // Prepare the FBX SDK.
  InitializeSdkObjects(pFbxManager_, pFbxScene_);
}

/**
 * @brief Destructor
 */
CReferenceDataCollector::~CReferenceDataCollector()
{
  std::cout << "CReferenceDataCollector::~CReferenceDataCollector()" << std::endl;
  referenceFileHandle_.close();
}

/**
 * @brief getSample
 */
CSample
CReferenceDataCollector::getSample() const
{
  std::cout << "CReferenceDataCollector::getSample()" << std::endl;
  CSample sample;
  return sample;
}

/**
 * @brief getSamplePeriod
 */
double
CReferenceDataCollector::getSamplePeriod() const
{
  std::cout << "CReferenceDataCollector::getSamplePeriod()" << std::endl;
  return dSamplePeriod_;
}

/**
 * @brief setSamplePeriod
 */
void
CReferenceDataCollector::setSamplePeriod(const double dSamplePeriod)
{
  std::cout << "CReferenceDataCollector::setSamplePeriod( " << dSamplePeriod << " )" << std::endl;
  dSamplePeriod_ = dSamplePeriod;
}

/**
 * @brief loadReferenceFile
 */
bool
CReferenceDataCollector::loadReferenceFile(const std::string& sFilename)
{
  referenceFileHandle_.open(sFilename.c_str(), std::ios_base::in);
  // Load the scene.
  FbxString lFilePath("");
  lResult = LoadScene(pFbxManager_, pFbxScene_, lFilePath.Buffer());
  if (lResult == false)
  {
    std::cerr << "An error occurred while loading the scene..." << std::endl;
  }
  else
  {
    // Display the scene metadata
    FbxDocumentInfo* sceneInfo = pScene->GetSceneInfo();
    if (sceneInfo)
    {
      printf("\n\n--------------------\nMeta-Data\n--------------------\n\n");
      printf("    Title: %s\n", sceneInfo->mTitle.Buffer());
      printf("    Subject: %s\n", sceneInfo->mSubject.Buffer());
      printf("    Author: %s\n", sceneInfo->mAuthor.Buffer());
      printf("    Keywords: %s\n", sceneInfo->mKeywords.Buffer());
      printf("    Revision: %s\n", sceneInfo->mRevision.Buffer());
      printf("    Comment: %s\n", sceneInfo->mComment.Buffer());

      FbxThumbnail* thumbnail = sceneInfo->GetSceneThumbnail();
      if (thumbnail)
      {
        printf("    Thumbnail:\n");

        switch (thumbnail->GetDataFormat())
        {
        case FbxThumbnail::eRGB_24:
          printf("        Format: RGB\n");
          break;
        case FbxThumbnail::eRGBA_32:
          printf("        Format: RGBA\n");
          break;
        }

        switch (thumbnail->GetSize())
        {
        default:
          break;
        case FbxThumbnail::eNotSet:
          printf("        Size: no dimensions specified (%ld bytes)\n", thumbnail->GetSizeInBytes());
          break;
        case FbxThumbnail::e64x64:
          printf("        Size: 64 x 64 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
          break;
        case FbxThumbnail::e128x128:
          printf("        Size: 128 x 128 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
        }
      }
    }
  }
  return lResult;
}

/**
 * @brief jumpTo
 */
bool
CReferenceDataCollector::jumpTo(const long iPosition)
{
  bool bSuccess(false);
  try
  {
    referenceFileHandle_.seekg(iPosition);
    bSuccess = true;
  }
  catch (std::ios_base::failure& e)
  {
    std::cout << "CReferenceDataCollector::jumpTo() failed to jump to position " << iPosition << std::endl;
  }
  return bSuccess;
}
