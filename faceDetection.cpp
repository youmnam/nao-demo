//after detect face --> detect small

// Aldebaran includes.
#include <alproxies/alvideodeviceproxy.h>
#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>
#include <alerror/alerror.h>
#include <alproxies/alanimatedspeechproxy.h>

// Opencv includes.
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace AL;
using namespace cv;


/*
void fixHead(){

	  const AL::ALValue jointName = "HeadYaw";
	  const AL::ALValue jointName2 = "HeadPitch";


	  try {

	    AL::ALMotionProxy motion(pip, pport);

	    AL::ALValue stiffness = 1.0f;

	    		AL::ALValue time = 1.0f;
	    motion.stiffnessInterpolation(jointName, stiffness, time);
	    motion.stiffnessInterpolation(jointName2, stiffness, time);

	    AL::ALValue targetAngles = AL::ALValue::array(-1.5f, 1.5f, 0.0f);

	    AL::ALValue targetTimes = AL::ALValue::array(3.0f, 6.0f, 9.0f);

	    bool isAbsolute = true;


	    int x;
	    while(true){
	     if(x ==1 )
	        motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
	     if(x== 2)
	    	motion.angleInterpolation(jointName2, targetAngles, targetTimes, isAbsolute);
	     if(x==3) break;
	    }
	    stiffness = 0.0f;
	    time = 1.0f;
	    motion.stiffnessInterpolation(jointName, stiffness, time);
	    motion.stiffnessInterpolation(jointName2, stiffness, time);

	  }
	  catch (const AL::ALError& e) {
	    std::cerr << "Caught exception: " << e.what() << std::endl;
	    exit(1);
	  }

}
*/

void detectFace(const std::string& robotIp)
{

  ALVideoDeviceProxy camProxy("192.168.1.104", 9559);
  AL::ALAnimatedSpeechProxy animtts ("192.168.1.104", 9559);

  const std::string clientName = camProxy.subscribe("test", kQVGA, kBGRColorSpace, 30);
  const std::string fn_haar = "/home/youmna/devTools/opencv-3.0.0-rc1/data/haarcascades/haarcascade_frontalface_alt2.xml";
  const std::string sm_haar = "/home/youmna/devTools/opencv-3.0.0-rc1/data/haarcascades/haarcascade_smile.xml";

  cv::Mat imgHeader = cv::Mat(cv::Size(320, 240), CV_8UC3);

  cv::CascadeClassifier haar_cascade;
  haar_cascade.load(fn_haar);

  cv::CascadeClassifier haar_cascade2;
  haar_cascade2.load(sm_haar);


  cv::namedWindow("images");

  while ((char) cv::waitKey(30) != 27)
  {
    ALValue img = camProxy.getImageRemote(clientName);
    imgHeader.data = (uchar*) img[6].GetBinary();

    Mat gray;
    cvtColor(imgHeader, gray, CV_BGR2GRAY);


    std::vector< Rect_<int> > faces;
    haar_cascade.detectMultiScale(gray, faces);



    for(int i = 0; i < faces.size(); i++) {

    	Rect face_i = faces[i];

        Mat face = gray(face_i); // crop the image with smile

        std::vector< Rect_<int> > smiles;
        haar_cascade2.detectMultiScale(face, smiles);

        if(smiles.size() > 0){
  //      std::string textToSay  = "\\rspd=10\\  ^start(animations/Stand/Gestures/Hey_1)Hello Human ^wait(animations/Stand/Gestures/Hey_1)";
	//	animtts.say(textToSay);
      	std::cout <<" yes smile yes hello" <<std::endl;
        }
        else{
        	std::cout <<" no smile no hello" <<std::endl;

        }
        rectangle(imgHeader, face_i, CV_RGB(0, 255,0), 1); //draw rectangle around the smile area
    }


    cv::imshow("images", imgHeader);

    camProxy.releaseImage(clientName);
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
    detectFace(robotIp);
  }
  catch (const AL::ALError& e)
  {
    std::cerr << "Caught exception " << e.what() << std::endl;
  }

  return 0;
}
