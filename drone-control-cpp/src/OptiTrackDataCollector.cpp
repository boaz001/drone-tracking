/**
 * OptiTrackDataCollector.cpp
 */

#include "OptiTrackDataCollector.h"
#include <NatNetTypes.h>
#include <iostream>

const int iConnectionType(ConnectionType_Multicast);
// const int iConnectionType(ConnectionType_Unicast);

/**
 * @brief Constructor
 */
COptiTrackDataCollector::COptiTrackDataCollector()
 : IDataCollector()
 , dSamplePeriod_(1000.0)
 , pNatNetClient_(NULL)
 , bIsConnected_(false)
{
  std::cout << "COptiTrackDataCollector::COptiTrackDataCollector()" << std::endl;
  connect();
  if (bIsConnected_ == true)
  {
    std::cout << "COptiTrackDataCollector::COptiTrackDataCollector() OptiTrack system is connected" << std::endl;
  }
  else
  {
    std::cerr << "COptiTrackDataCollector::COptiTrackDataCollector() Failed to connect to OptiTrack system" << std::endl;
  }
}

/**
 * @brief Destructor
 */
COptiTrackDataCollector::~COptiTrackDataCollector()
{
  std::cout << "COptiTrackDataCollector::~COptiTrackDataCollector()" << std::endl;
  disconnect();
}

/**
 * @brief connect
 */
void
COptiTrackDataCollector::connect()
{
  std::cout << "COptiTrackDataCollector::connect()" << std::endl;
  if (pNatNetClient_ == NULL)
  {
    std::cout << "COptiTrackDataCollector::connect() creating client..." << std::endl;
    pNatNetClient_ = new NatNetClient(iConnectionType);

    // created? try to connect
    if (pNatNetClient_ != NULL)
    {
      // unsigned char ver[4];
      // pNatNetClient_->NatNetVersion(ver);
      // std::cout << "NatNet version: " << ver[0] << "." << ver[1] << "." << ver[3] << "." << ver[0] << std::endl;

      std::cout << "COptiTrackDataCollector::connect() connecting..." << std::endl;
      char szMyIPAddress[128] = "127.0.0.1\0"; // or \n ?
      char szServerIPAddress[128] = "127.0.0.1\0"; // or \n ?
      const int retCode = pNatNetClient_->Initialize(szMyIPAddress, szServerIPAddress);
      if (retCode != ErrorCode_OK)
      {
        // connection initialization failed
        std::cout << "Unable to connect to server. Error code: " << retCode << std::endl;
      }
      else
      {
        // connection initialization succeed
        sServerDescription serverDescription;
        std::memset(&serverDescription, 0, sizeof(serverDescription));
        pNatNetClient_->GetServerDescription(&serverDescription);
        if (serverDescription.HostPresent == false)
        {
            std::cout << "Unable to connect to server. Host not present. Exiting." << std::endl;
        }
        std::cout << "Application: '" << serverDescription.szHostApp << "' version: " << serverDescription.HostAppVersion[0] << "." << serverDescription.HostAppVersion[1] << "." << serverDescription.HostAppVersion[2] << "." << serverDescription.HostAppVersion[3] << std::endl;
        std::cout << "NatNet version: " << serverDescription.NatNetVersion[0] << "." << serverDescription.NatNetVersion[1] << "." << serverDescription.NatNetVersion[2] << "." << serverDescription.NatNetVersion[3] << std::endl;
        std::cout << "Client IP: " << szMyIPAddress << std::endl;
        std::cout << "Server IP: " << szServerIPAddress << std::endl;
        std::cout << "Server Name: '" << serverDescription.szHostComputerName << "'" << std::endl;
        bIsConnected_ = true;
      }
    }
    else
    {
      std::cerr << "Failed to allocate NatNetClient" << std::endl;
    }
  }
  else
  {
    std::cout << "NatNetClient already created" << std::endl;
  }
}

/**
 * @brief disconnect
 */
void
COptiTrackDataCollector::disconnect()
{
  std::cout << "COptiTrackDataCollector::disconnect()" << std::endl;
  if (pNatNetClient_ != NULL)
  {
    std::cout << "COptiTrackDataCollector::disconnect() disconnecting..." << std::endl;
    pNatNetClient_->Uninitialize();
    delete pNatNetClient_;
    pNatNetClient_ = NULL;
    bIsConnected_ = false;
    std::cout << "COptiTrackDataCollector::disconnect() disconnected" << std::endl;
  }
}

/**
 * @brief isConnected
 */
bool
COptiTrackDataCollector::isConnected() const
{
  return bIsConnected_;
}

/**
 * @brief getSample
 */
CSample
COptiTrackDataCollector::getSample() const
{
  std::cout << "COptiTrackDataCollector::getSample()" << std::endl;
  CSample sample;
  return sample;
}

/**
 * @brief getSamplePeriod
 */
double
COptiTrackDataCollector::getSamplePeriod() const
{
  std::cout << "COptiTrackDataCollector::getSamplePeriod()" << std::endl;
  return dSamplePeriod_;
}

/**
 * @brief setSamplePeriod
 */
void
COptiTrackDataCollector::setSamplePeriod(const double dSamplePeriod)
{
  std::cout << "COptiTrackDataCollector::setSamplePeriod( " << dSamplePeriod << " )" << std::endl;
  dSamplePeriod_ = dSamplePeriod;
}
