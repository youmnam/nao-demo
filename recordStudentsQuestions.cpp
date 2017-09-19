#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alaudiorecorderproxy.h>
#include <alproxies/alaudioplayerproxy.h>
#include <alproxies/altouchproxy.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/alanimatedspeechproxy.h>

#include <sstream>
using namespace std;

string robotIP = "192.168.1.95";
int portNo  = 9559;
string intToString(int val);
// when touch the front head sensor start recording, touch again stop recording
// when touch the back head sensors play all questions recorded.

int main(int argc, char* argv[]){

	 // We will try to connect our broker to a running NAOqi
	  int pport = 9559;
	  std::string pip = "127.0.0.1";

	 // command line parse option
	  // check the number of arguments
	  if (argc != 1 && argc != 3 && argc != 5)
	  {
	    std::cerr << "Wrong number of arguments!" << std::endl;
	    std::cerr << "Usage: mymodule [--pip robot_ip] [--pport port]" << std::endl;
	    exit(2);
	  }

	  // if there is only one argument it should be IP or PORT
	  if (argc == 3)
	  {
	    if (std::string(argv[1]) == "--pip")
	      pip = argv[2];
	    else if (std::string(argv[1]) == "--pport")
	      pport = atoi(argv[2]);
	    else
	    {
	      std::cerr << "Wrong number of arguments!" << std::endl;
	      std::cerr << "Usage: mymodule [--pip robot_ip] [--pport port]" << std::endl;
	      exit(2);
	    }
	  }

	  // Sepcified IP or PORT for the connection
	  if (argc == 5)
	  {
	    if (std::string(argv[1]) == "--pport"
	        && std::string(argv[3]) == "--pip")
	    {
	      pport = atoi(argv[2]);
	      pip = argv[4];
	    }
	    else if (std::string(argv[3]) == "--pport"
	             && std::string(argv[1]) == "--pip")
	    {
	      pport = atoi(argv[4]);
	      pip = argv[2];
	    }
	    else
	    {
	      std::cerr << "Wrong number of arguments!" << std::endl;
	      std::cerr << "Usage: mymodule [--pip robot_ip] [--pport port]" << std::endl;
	      exit(2);
	    }
	  }

	  robotIP = pip;
	  portNo = pport;
	//(1) Configure the Recorder
	     AL::ALAudioRecorderProxy audioproxy(robotIP, portNo);
	      AL::ALValue channels ;
	      channels.arrayPush(0); //Left
	      channels.arrayPush(0); //Right
	      channels.arrayPush(1); //Front microphone
	      channels.arrayPush(0); //Rear

	 //(2) Get the player proxy
	      AL::ALAudioPlayerProxy playerProxy(robotIP, portNo);

	 //(3) Get Memory to check the head tactile changed
	      AL::ALMemoryProxy memproxy(robotIP,portNo);

	 //(4) Get TextToSpeech Animated Module
	      AL::ALAnimatedSpeechProxy animtts (robotIP, portNo);

	 //(5) Explain the interactive Senario
	      string explain_txt ="Hey, Please touch my front tactile head sensor to start record your question ";
	      explain_txt+="and touch it again to save your question \\pau=1000\\ to play all questions said touch the middle tactile head sensor";
	      explain_txt+="to stop this behavior touch the near touch tactile sensor" ;

	      animtts.say(explain_txt);


	int count =0; 		       // for handling the twice clicks on front touch sensor
	int audio_no = 0;          // for handling the name of file "to allow multiple recordings"
	string audioFileName = ""; // hold the name of recorded sound

	while(true){

		AL::ALValue isFrontTouchedVal  = memproxy.getData("FrontTactilTouched");
		AL::ALValue isMiddleTouchedVal = memproxy.getData("MiddleTactilTouched");
		AL::ALValue isRearTouchedVal   = memproxy.getData("RearTactilTouched");

		 if(isFrontTouchedVal == AL::ALValue(1.0)){
			 if(count == 0 ){

				 animtts.say("Please, Tell Me your question:"); //ask

				 audioFileName = "/home/nao/test" + intToString(audio_no) + ".wav";

				 audioproxy.startMicrophonesRecording(audioFileName,"wav",16000,channels);

				 memproxy.insertData("FrontTactilTouched",AL::ALValue(0.0));
				 count++;

				 cout << "to record " << audioFileName <<endl;
			 }
			 else if( count == 1 ){
				 count =0;

				 audioproxy.stopMicrophonesRecording();

				 animtts.say("Please wait I am saving your question"); //shy
				 qi::os::sleep(1);
				 animtts.say("your question is in my database now"); //ohoooooo

				 cout << "to stop record" <<endl;
				 audio_no ++;
				 memproxy.insertData("FrontTactilTouched",AL::ALValue(0.0));
			 }
		 }
		 if(isMiddleTouchedVal == AL::ALValue(1.0)){
			 cout << "playing...." <<endl;
			 animtts.say("I will tell you all questions I have in my database"); //shy
			 for(int i = 0; i<audio_no ; i++){
                 audioFileName = "/home/nao/test" + intToString(i) + ".wav";
				 animtts.say("Question number " + intToString(i)) ;
				 qi::os::sleep(1);
				 playerProxy.playFile(audioFileName);
			 }
			 memproxy.insertData("MiddleTactilTouched",AL::ALValue(0.0));
		 }
		 if(isRearTouchedVal == AL::ALValue(1.0)){
			 animtts.say("good by , see you later"); //smilly
			 cout << "goodbye...." <<endl;
			 memproxy.insertData("RearTactilTouched",AL::ALValue(0.0));
			 break;
		 }

	 }
}


string intToString(int val){

	 stringstream ss;
     string res ="";
     ss <<val;
     ss >> res;

     return res;
}
