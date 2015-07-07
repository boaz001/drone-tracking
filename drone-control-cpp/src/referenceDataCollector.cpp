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
  // Create the FBX SDK manager
  pFbxManager_ = FbxManager::Create();
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
  // Based on:
  // http://docs.autodesk.com/FBX/2014/ENU/FBX-SDK-Documentation/index.html
  referenceFileHandle_.open(sFilename.c_str(), std::ios_base::in);
  // Create an IOSettings object. IOSROOT is defined in Fbxiosettingspath.h.
  FbxIOSettings* pIOSettings = FbxIOSettings::Create(lSdkManager, IOSROOT);
  pFbxManager_->SetIOSettings(pIOSettings);

  // ... Configure the FbxIOSettings object ...
  // Import options determine what kind of data is to be imported.
  // True is the default, but here we’ll set some to true explicitly, and others to false.
  // (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_MATERIAL,        true);
  // (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_TEXTURE,         true);
  // (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_LINK,            false);
  // (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_SHAPE,           false);
  // (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_GOBO,            false);
  // (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_ANIMATION,       true);
  // (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);

  // Create an importer.
  FbxImporter* pFbxImporter = FbxImporter::Create(pFbxManager_, "");

  // Declare the path and filename of the file containing the scene.
  // In this case, we are assuming the file is in the same directory as the executable.
  const char* lFilename = "file.fbx";

  // Initialize the importer.
  bool lImportStatus = pFbxImporter->Initialize(lFilename, -1, pFbxManager_->GetIOSettings());

  if (!lImportStatus) {
    printf("Call to FbxImporter::Initialize() failed.\n");
    printf("Error returned: %s\n\n", pFbxImporter->GetStatus().GetErrorString());
    exit(-1);
  }

  // Create a new scene so it can be populated by the imported file.
  FbxScene* pScene = FbxScene::Create(pFbxManager_,"myScene");

  // Import the contents of the file into the scene.
  pFbxImporter->Import(pScene);

  // The file has been imported; we can get rid of the importer.
  pFbxImporter->Destroy();

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
