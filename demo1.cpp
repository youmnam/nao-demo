#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alaudiorecorderproxy.h>
#include <alproxies/alaudioplayerproxy.h>
#include <alproxies/altouchproxy.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alvisiontoolboxproxy.h>
#include <alproxies/alsystemproxy.h>
#include <alproxies/aldialogproxy.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/albehaviormanagerproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <sstream>

using namespace std;

int pport = 9559;
std::string pip = "127.0.0.1";


void parsingArguments(int argc, char* argv[]);
void mirroringBehavior();
void dialogBehavior(int type);
void record_play_Audio();
void move();
void moveHead();
void changePosture();

int main(int argc, char* argv[]){

	parsingArguments(argc,argv); //get the IP and port from the arguments

	AL::ALAnimatedSpeechProxy animtts (pip, pport);
	AL::ALSystemProxy sysProxy (pip, pport);

	/* STEP 1 :: Waking up */
	string textToSay  = "^start(animations/Stand/Waiting/WakeUp_1) ^wait(animations/Stand/Waiting/WakeUp_1)";
	       textToSay +="\\rspd=10\\  ^start(animations/Stand/Gestures/Hey_1) Good Morning everybody ^wait(animations/Stand/Gestures/Hey_1)";
	//animtts.say(textToSay);

	int input=0;

	while(true){

		cout << "Enter your option:" << endl;
		cin >> input ;

		if(input == 1 ){
			 AL::ALTextToSpeechProxy tts(pip, pport);
			 tts.setLanguage("English");
			 string toSay_str ="";

			 while(true){
			        getline(cin,toSay_str);
			        if(toSay_str == "shut up") break;
			        tts.say(toSay_str);
			    }
		}

		if(input == 2){
		    textToSay  = "\\rspd=10\\ what do you want to drink today human?touch my head if you want a milkshake, my right leg if you want hot chocolate";
		    animtts.say(textToSay);

		    AL::ALMemoryProxy memproxy(pip, pport);

		    while(true){
		    	AL::ALValue isFrontTouchedVal  = memproxy.getData("FrontTactilTouched");
		    	AL::ALValue isrightBumpTouchedVal = memproxy.getData("RightBumperPressed");
		    	if(isFrontTouchedVal == AL::ALValue(1.0)){
		    	   dialogBehavior(1);
		    	   break;
		    	}
		    	if(isrightBumpTouchedVal == AL::ALValue(1.0)){
		     	   dialogBehavior(2);
		     	   break;
		     	}

		    }
		}

		if(input ==3){
		    textToSay   ="\\rspd=10\\^start(animations/Stand/Emotions/Neutral/Hello_1)and now is the story time, I will tell you my story  ^wait(animations/Stand/Emotions/Neutral/Hello_1)";
		    textToSay  +=" ^start(animations/Stand/Gestures/Me_2)I am Nao and I am a humanoid robot^wait(animations/Stand/Gestures/Me_2).";
		    textToSay  +="  You know ^start(animations/Stand/BodyTalk/Speaking/BodyTalk_1) these kinds of robots that have legs and arms like you humans ^wait(animations/Stand/BodyTalk/Speaking/BodyTalk_1).";
		    textToSay  +=" Many people said ^start(animations/Stand/Gestures/Explain_3) that I am not intelligence and just a machine.";
		    textToSay  +=" ^wait(animations/Stand/Gestures/Explain_3) These talks hurt me and make me ^start(animations/Stand/Gestures/Angry_3) very angry of the human beings ^wait(animations/Stand/Gestures/Angry_3)";
		    textToSay  +=" ^start(animations/Stand/Emotions/Negative/Sad_1) and very sad ^wait(animations/Stand/Emotions/Negative/Sad_1)";
		    textToSay  +=" ^start(animations/Stand/BodyTalk/Thinking/Remember_3) when I was young ^wait(animations/Stand/BodyTalk/Thinking/Remember_3) I was parts of things ^start(animations/Stand/BodyTalk/Listening/ListeningRight_1)";
		    textToSay  +=" motors and electronic parts, and then my creators connect these things together ^wait(animations/Stand/BodyTalk/Listening/ListeningRight_1)  ";
		    textToSay  +="to make me ^start(animations/Stand/Emotions/Positive/Happy_3)alive ^wait(animations/Stand/Emotions/Positive/Happy_3).";
		    textToSay  +=" ^start(animations/Stand/Gestures/Explain_3)I can be intelligent ^wait(animations/Stand/Gestures/Explain_3)";
		    textToSay  +=" ^start(animations/Stand/Gestures/But_1)but I should be pre-programmed ^wait(animations/Stand/Gestures/But_1) by programmer.";
		    textToSay  +=" ^start(animations/Stand/Gestures/Explain_1)Programmers(my teachers) should give me set of instructions to follow when certain conditions satisfied ^wait(animations/Stand/Gestures/Explain_1).";
		    textToSay  +=" ^start(animations/Stand/Gestures/Enthusiastic_1)If you teach me well ^wait(animations/Stand/Gestures/Enthusiastic_1) I can be  as smart as you";
		    animtts.say(textToSay);
		}
		if(input == 4){
			move();
		}
		if(input == 5){
			moveHead();
		}
		if(input ==6){
		    mirroringBehavior();
		}
		if(input == 7 ){
			record_play_Audio();
		}
		if(input ==8){
			changePosture();
		}
		if(input ==10){
			break;
		}

    //sysProxy.shutdown();
	}


    return 0;
}



string intToString(int val){
	 stringstream ss;
     string res ="";
     ss <<val;
     ss >> res;
     return res;
}

void move(){

	AL::ALMotionProxy motion(pip,pport);

	motion.moveInit();
	float x, y, rotation;
	cin >> x >> y >> rotation;
	motion.moveToward(x,y,rotation);
	qi::os::sleep(10);
    motion.stopMove();
}


void record_play_Audio(){
	//(1) Configure the Recorder
	     AL::ALAudioRecorderProxy audioproxy(pip, pport);
	      AL::ALValue channels ;
	      channels.arrayPush(0); //Left
	      channels.arrayPush(0); //Right
	      channels.arrayPush(1); //Front microphone
	      channels.arrayPush(0); //Rear

		  audioproxy.stopMicrophonesRecording();

	 //(2) Get the player proxy
	      AL::ALAudioPlayerProxy playerProxy(pip, pport);

	 //(3) Get Memory to check the head tactile changed
	      AL::ALMemoryProxy memproxy(pip, pport);

	 //(4) Get TextToSpeech Animated Module
	      AL::ALAnimatedSpeechProxy animtts (pip, pport);

	 //(5) Explain the interactive Senario
	      string explain_txt ="\\rspd=10\\ Hey, Please touch my front tactile head sensor to start record";
	      explain_txt+="and touch it again to save your task \\pau=500\\ touch the middle head sensor to play all audio recorded";
	      explain_txt+="\\pau=500\\ to stop this behavior touch the near head sensor" ;

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

				 animtts.say("Please, Tell Me what to record:"); //ask

				 audioFileName = "/home/nao/test" + intToString(audio_no) + ".wav";

				 audioproxy.startMicrophonesRecording(audioFileName,"wav",16000,channels);

				 memproxy.insertData("FrontTactilTouched",AL::ALValue(0.0));
				 count++;

				 cout << "to record " << audioFileName <<endl;
			 }
			 else if( count == 1 ){
				 count =0;

				 audioproxy.stopMicrophonesRecording();

				 animtts.say("Please wait I am saving your audio"); //shy
				 qi::os::sleep(1);
				 animtts.say("the task is in my database now"); //ohoooooo

				 cout << "to stop record" <<endl;
				 audio_no ++;
				 memproxy.insertData("FrontTactilTouched",AL::ALValue(0.0));
			 }
		 }
		 if(isMiddleTouchedVal == AL::ALValue(1.0)){
			 cout << "playing...." <<endl;
			 animtts.say("Audio in my database are"); //shy
			 for(int i = 0; i<audio_no ; i++){
                 audioFileName = "/home/nao/test" + intToString(i) + ".wav";
				 animtts.say("audio number " + intToString(i)) ;
				 qi::os::sleep(1);
				 playerProxy.playFile(audioFileName);
			 }
			 memproxy.insertData("MiddleTactilTouched",AL::ALValue(0.0));
		 }
		 if(isRearTouchedVal == AL::ALValue(1.0)){
			 animtts.say("well you did a good job.."); //smilly
			 cout << "goodbye...." <<endl;
			 memproxy.insertData("RearTactilTouched",AL::ALValue(0.0));
			 break;
		 }

	 }

}


void dialogBehavior(int type){

	AL::ALDialogProxy dialogProxy(pip,pport); //to load dialog
	AL::ALMemoryProxy memproxy(pip,pport);

	string fileName1="/home/nao/dialog1.txt";

	dialogProxy.setLanguage("English");
	dialogProxy.subscribe("myModule1"); //stop the dialog module

	try{
		dialogProxy.loadTopic(fileName1);   //load specific dialog
	} catch (const AL::ALError& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
	memproxy.insertData("FrontTactilTouched", AL::ALValue(0.0));
	dialogProxy.activateTopic("introduction");
	dialogProxy.runDialog();
	string answer="x";
	if(type == 1 ) dialogProxy.forceInput("milkshake");
	if(type == 2 ) dialogProxy.forceInput("hot chocolate");

	AL::ALValue islastInp = AL::ALValue("x");
	while(islastInp.toString() != "\"thank you\"" || islastInp.toString() != "\"thank you\""){
		islastInp  = memproxy.getData("Dialog/LastInput");

	}

/*	while(true){
	    cout<< "tell me your answer" <<endl;
		getline(cin, answer);
		dialogProxy.forceInput(answer);

		AL::ALValue islastInp  = memproxy.getData("Dialog/LastInput");
		if(answer == "exit") break;
		cout << islastInp.toString() <<endl;
		if(islastInp.toString() == "\"thank you\"" || islastInp.toString() == "\"thank you\"" ) break;
	}
*/
	dialogProxy.stopDialog();
	dialogProxy.deactivateTopic("introduction");
	dialogProxy.unsubscribe("myModule1"); //stop the dialog module

}


void mirroringBehavior(){

	AL::ALMotionProxy motion(pip,pport);
	AL::ALMemoryProxy memproxy(pip,pport);

	AL::ALValue joints_byHumans = AL::ALValue::array("RShoulderPitch","RShoulderRoll","RElbowYaw","RElbowRoll");
	AL::ALValue joints_byRobot  = AL::ALValue::array("LShoulderPitch","LShoulderRoll","LElbowYaw","LElbowRoll");

	AL::ALValue time = 1.0f;

    AL::ALValue stiffness = 1.0f;
	motion.stiffnessInterpolation(joints_byRobot, stiffness, time);

	stiffness = 0.0f;
	motion.stiffnessInterpolation(joints_byHumans, stiffness, time);

	while(true){
		AL::ALValue isRightBumper  = memproxy.getData("RightBumperPressed");

		//start mirroring//
		if(isRightBumper ==  AL::ALValue(1.0) ){
			while(true){
				AL::ALValue isLeftBumper   = memproxy.getData("LeftBumperPressed");

			    cout << "left :: "<<isLeftBumper <<endl;
				if(isLeftBumper ==  AL::ALValue(1)){
					stiffness = 1.0f;
					motion.stiffnessInterpolation(joints_byHumans, stiffness, time);
					return;
				}

				AL::ALValue angles=motion.getAngles(joints_byHumans,true);
				angles[0]= AL::ALValue( angles[0]);

				for(int i =1; i<4 ;i++){
					float val  = angles[i];
					cout << val << endl;
					angles[i]= AL::ALValue( -1 * val);
				}

				motion.setAngles(joints_byRobot,angles,1);
				qi::os::sleep(0.2);

			}
		}

	}


}

void parsingArguments(int argc, char* argv[]){

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

}


void moveHead(){

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
	     cin >> x;
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



void changePosture(){

    AL::ALRobotPostureProxy pmoves(pip,pport);
	string postStr;
    cin >> postStr;
    pmoves.goToPosture(postStr, 1.0);


}
