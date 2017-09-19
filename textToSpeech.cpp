// http://doc.aldebaran.com/2-1/naoqi/audio/altexttospeech-tuto.html
#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
using namespace std;

int main(int argc, char* argv[]) {

	 try {
	    // Create a ALTextToSpeechProxy to call the methods to make NAO talk.
	    // Arguments for the constructor are:
	    // - IP adress of the robot
	    // - port on which NAOqi is listening, by default 9559

	    AL::ALTextToSpeechProxy tts("192.168.1.88", 9559);

	    tts.setLanguage("English");
	    string toSay_str ="";
	    float speed = 10 ;
	    float pitchRise = 2 ; //correct range (1.0 ~ 4)

	    tts.setParameter("doubleVoice", 1);
	    tts.setParameter("doubleVoiceLevel", 0.5);
	   	tts.say("Hello my friends I am trying to talk with you in different manner");

	    //tts.setParameter("speed", speed);
	    //tts.setParameter("pitchShift", pitchRise);
	    //tts.setParameter("doubleVoice", 3);
	    //tts.setParameter("doubleVoiceLevel", 0.5);
	    //tts.say("Hello my friends I am trying to talk with you in different manner");

	   	tts.say("Hello my friends \\pau=1000\\ \\rspd=50\\ \\vol=50\\ how are you ?");


	    /*
	    while(toSay_str != "shut up"){
	        getline(cin,toSay_str);
	        tts.say(toSay_str);

	    }*/


	 }  catch (const AL::ALError& e) {
		    std::cerr << "Caught exception: " << e.what() << std::endl;
		    exit(1);
		  }

}
