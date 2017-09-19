/**
 *
 * This example demonstrates how to get images from the robot remotely and how
 * to display them on your screen using opencv.
 *
 * Copyright Aldebaran Robotics
 */

// Aldebaran includes.
#include <alproxies/alvideodeviceproxy.h>
#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>
#include <alerror/alerror.h>

// Opencv includes.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <iostream>
#include <string>

using namespace AL;


/**
* \brief Shows images retrieved from the robot.
*
* \param robotIp the IP adress of the robot
*/
void showImages(const std::string& robotIp)
{

  ALVideoDeviceProxy camProxy(robotIp, 9559);

  const std::string clientName = camProxy.subscribe("test", kQVGA, kBGRColorSpace, 30);

  cv::Mat imgHeader = cv::Mat(cv::Size(320, 240), CV_8UC3);

  cv::namedWindow("images");

  while ((char) cv::waitKey(30) != 27)
  {
    ALValue img = camProxy.getImageRemote(clientName);
    imgHeader.data = (uchar*) img[6].GetBinary();
    camProxy.releaseImage(clientName);
    cv::imshow("images", imgHeader);
  }

  camProxy.unsubscribe(clientName);

}



int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage 'getimages robotIp'" << std::endl;
    return 1;
  }

  const std::string robotIp(argv[1]);

  try
  {
    showImages(robotIp);
  }
  catch (const AL::ALError& e)
  {
    std::cerr << "Caught exception " << e.what() << std::endl;
  }

  return 0;
}
