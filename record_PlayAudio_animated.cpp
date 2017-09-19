#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alaudiorecorderproxy.h>
#include <alproxies/alaudioplayerproxy.h>

using namespace std;

string robotIP = "192.168.1.80";

int main(){

	   AL::ALAudioRecorderProxy audioproxy(robotIP, 9559);
	      AL::ALAudioPlayerProxy playerProxy(robotIP, 9559);
	      AL::ALValue channels ;
	      channels.arrayPush(0); //Left
	      channels.arrayPush(0); //Right
	      channels.arrayPush(1); //Front microphone
	      channels.arrayPush(0); //Rear

	     //****Start Recording****///
	     //audioproxy.startMicrophonesRecording("/home/nao/test.wav","wav",16000,channels);
	     //qi::os::sleep(120);

	     // Stops the recording and close the file after 120 seconds.
	     // audioproxy.stopMicrophonesRecording();

	     //  cout << "I am done recording" << endl;

	   //   playerProxy.stopAll(); //for stop any recording procedure

	     //****Start Playing the recorded eith animation sound****///
	     // animtts.post.say("^start(animations/Stand/Emotions/Neutral/Hello_1) ^wait(animations/Stand/Emotions/Neutral/Hello_1) ^start(animations/Stand/Gestures/You_1)  ^wait(animations/Stand/Gestures/You_1)");
	   //   playerProxy.post.playFile("/home/nao/test.wav");
	//	 qi::os::sleep(10);
		//  cout << "I am done playing" << endl;

}
