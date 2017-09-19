#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/alspeechrecognitionproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/alaudiorecorderproxy.h>
#include <alproxies/alaudioplayerproxy.h>

using namespace std;
using namespace AL;
/*
 * [Done-notTested] head movement nodes right/left(no) up/down (yes) -> shows that specific joint can be moved
 * [Done-notTested] hand movement waving as byebye behavior -> shows that specific joint can be moved
 * [Done-notTested] head+hand movement during conversation -> shows the concurrent tasks availability
 * [Done-notTested] speech recognition understand what are being said -> shows the speech recognition availability
 * [Done-notTested] saying  TextToSpeech engine -> shows the ability to say whatever give
 *
 * */

string robotIP = "192.168.1.80";
void moveHeadInBackground(int tag);
void moveHand();

int main(int argc, char* argv[]) {

	//moveHand();

	//ALTextToSpeechProxy tts(robotIP, 9559);
	//ALSpeechRecognitionProxy speechR(robotIP, 9559);
	//ALMemoryProxy memproxy(robotIP, 9559);
	/*speechR.unsubscribe("Test_ASR");

	speechR.setLanguage("English");
	std::vector<string> words;
	words.push_back("yes");
	words.push_back("no");
	words.push_back("bye");
	speechR.setVocabulary(words,false);
	*/
	//while(1){
		/*string user_str;
		speechR.subscribe("Test_ASR");

		sleep(50);

		speechR.unsubscribe("Test_ASR");

		AL::ALValue recWord=memproxy.getData("WordRecognized");
		user_str = recWord.toString();
		cout << user_str <<endl;
		*/
		//tts.say(user_str);

	//moveHeadInBackground(0);

/*
		if (user_str == "yes"){
			moveHeadInBackground(0); // 0: tag for head Pitch move right,left #Yes
			//tts.say("You said Yes");
			cout << "You said Yes" << endl;

		}else if (user_str == "no"){
			moveHeadInBackground(1); // 1: tag for head Yaw, move right,left #No
			//tts.say("You said No");
			cout << "You said NO" << endl;
		}else if (user_str == "no"){
			//moveHand();
			//tts.say("bye");
			cout << "bye" << endl;
		}else{
			//moveHeadInBackground(2); // 2: tag for head Yaw&Pitch top/down, right/left #confused
			//tts.say("Sorry I am confused");
			cout << "Sorry I am confused" << endl;
		}
	*/
	//}
		return 0;
}


void moveHeadInBackground(int tag){

	  const AL::ALValue jointName = "HeadYaw";
	  const AL::ALValue jointName2 = "HeadPitch";

	  try {
	    ALMotionProxy motion(robotIP, 9559);

	    AL::ALValue stiffness = 1.0f;
	    AL::ALValue time = 1.0f;
	    motion.stiffnessInterpolation(jointName, stiffness, time);
	    motion.stiffnessInterpolation(jointName2, stiffness, time);

	    AL::ALValue targetAngles = AL::ALValue::array(-1.5f, 1.5f, 0.0f);
	    AL::ALValue targetTimes = AL::ALValue::array(3.0f, 6.0f, 9.0f);

	    bool isAbsolute = true;
	    AL::ALValue changes    = 0.5f;
	     float fractionMaxSpeed = 0.05f;
	    if(tag ==0 ){ // no
	    	//motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
	         motion.changeAngles(jointName,changes,fractionMaxSpeed);
	         changes    = -0.5f;
	         qi::os::sleep(1.0f);
	         motion.changeAngles(jointName,changes,fractionMaxSpeed);
	         qi::os::sleep(1.0f);
	    }
	         else if (tag ==1) // yes
	    	motion.angleInterpolation(jointName2, targetAngles, targetTimes, isAbsolute);
	    else if (tag ==2){ //confused
	    //	AL::ALValue targetAngles1 = AL::ALValue::array(-1.5f, 1.5f, 0.0f);
	    //	motion.post.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
	    //	AL::ALValue targetAngles2 = AL::ALValue::array(-1.5f, 1.5f, 0.0f);
	    //	motion.post.angleInterpolation(jointName2, targetAngles2, targetTimes, isAbsolute);
	    }

	    // Remove the stiffness on the head.
	    stiffness = 0.0f;
	    time = 1.0f;
	    motion.stiffnessInterpolation(jointName, stiffness, time);
	    motion.stiffnessInterpolation(jointName2, stiffness, time);

	    cout <<"done with movement" <<endl;
	  }
	  catch (const AL::ALError& e) {
	    std::cerr << "Caught exception: " << e.what() << std::endl;
	    exit(1);
	  }

}


void moveHand(){

	//move the RShoulderPitch to front RShoulderRoll to right RElbowRoll to left RHand open
	//RElbowRoll movement right and left to make byebye movement but after adjust the location of the arm
	//Sequence:
	// 	(1) RShoulderPitch --> (-ve)  * decrease from the standInit (-0.5)
	//  (2) RShoulderRoll  --> (-ve)  * decrease from the standInit (-65.0)
	//	(3) RHand		   --> (+ve)  * increase from the standInit (+1)
	//	(4) RElbowRoll 	   --> (+ve)  * increase from the standInit (+88.4) ** will then moves

	  ALValue jointNames = ALValue::array("RShoulderPitch","RShoulderRoll","RElbowRoll", "RHand");

	  try {
	    ALMotionProxy motion(robotIP, 9559);


		motion.stiffnessInterpolation(jointNames, 0.0f, 1.0f);

		//set Stiffness true  to allow movement
	    ALValue stiffness = 1.0f;
		ALValue time = 1.0f;

		motion.stiffnessInterpolation(jointNames, stiffness, time);

		//parameters of movement
	    ALValue targetAngles ;
	    ALValue targetTimes ;
	    bool isAbsolute = true;

	    //RShoulderPitch Movement
	    targetAngles = ALValue::array(-1.5f);
	    targetTimes = ALValue::array(3.0f);
	    motion.angleInterpolation(jointNames[0],targetAngles,targetTimes,isAbsolute);
		for(int i=0; i<4;i++)
			motion.stiffnessInterpolation(jointNames[i], stiffness, time);


	    //RShoulderRoll Movement
	   	targetAngles = ALValue::array(-1.5f);
	   	targetTimes = ALValue::array(3.0f);
	   	motion.angleInterpolation(jointNames[1],targetAngles,targetTimes,isAbsolute);

		motion.stiffnessInterpolation(jointNames, stiffness, time);

		//RHand Movement
		targetAngles = ALValue::array(0.0f, 1.0f, 0.0f);
		targetTimes = ALValue::array(3.0f, 6.0f, 9.0f);
		motion.angleInterpolation(jointNames[3],targetAngles,targetTimes,isAbsolute);

		motion.stiffnessInterpolation(jointNames, stiffness, time);


		//RElbowRoll Movement
		targetAngles = ALValue::array(0.0f, 1.5f, 0.0f);
		targetTimes = ALValue::array(3.0f, 6.0f, 9.0f);
		motion.angleInterpolation(jointNames[2],targetAngles,targetTimes,isAbsolute);

		motion.stiffnessInterpolation(jointNames, stiffness, time);


		//waving behavior
		targetAngles = ALValue::array(-1.5f, 1.5f, 0.0f);
		targetTimes = ALValue::array(3.0f, 6.0f, 9.0f);
		for(int i = 0 ; i<5 ; i++)
			motion.angleInterpolation(jointNames[2],targetAngles,targetTimes,isAbsolute);


	    //********undo ---> RShoulderPitch Movement
	    targetAngles = ALValue::array(+1.5f);
	    targetTimes = ALValue::array(3.0f);
	    motion.angleInterpolation(jointNames[0],targetAngles,targetTimes,isAbsolute);

		motion.stiffnessInterpolation(jointNames, stiffness, time);


	    //********undo ----> RShoulderRoll Movement
	   	targetAngles = ALValue::array(+1.5f);
	   	targetTimes = ALValue::array(3.0f);
	   	motion.angleInterpolation(jointNames[1],targetAngles,targetTimes,isAbsolute);


		motion.stiffnessInterpolation(jointNames, stiffness, time);


		//********undo ---->RHand Movement
		targetAngles = ALValue::array(0.0f, -1.0f, 0.0f);
		targetTimes = ALValue::array(3.0f, 6.0f, 9.0f);
		motion.angleInterpolation(jointNames[3],targetAngles,targetTimes,isAbsolute);

		motion.stiffnessInterpolation(jointNames, stiffness, time);


		//********undo ---->RElbowRoll Movement
		targetAngles = ALValue::array(0.0f, -1.5f, 0.0f);
		targetTimes = ALValue::array(3.0f, 6.0f, 9.0f);
		motion.angleInterpolation(jointNames[2],targetAngles,targetTimes,isAbsolute);

		motion.stiffnessInterpolation(jointNames, stiffness, time);




	/*

		for(int i=0; i<4;i++)
			motion.stiffnessInterpolation(jointNames[i], stiffness, time);

	   	//RElbowRoll Movement
		targetAngles = ALValue::array(0.0f, 1.5f, 0.0f);
		targetTimes = ALValue::array(3.0f, 6.0f, 9.0f);
		motion.angleInterpolation(jointNames[2],targetAngles,targetTimes,isAbsolute);

		for(int i=0; i<4;i++)
			motion.stiffnessInterpolation(jointNames[i], stiffness, time);

		//waving behavior
		targetAngles = ALValue::array(-1.5f, 1.5f, 0.0f);
		targetTimes = ALValue::array(3.0f, 6.0f, 9.0f);
		for(int i = 0 ; i<5 ; i++)
			motion.angleInterpolation(jointNames[2],targetAngles,targetTimes,isAbsolute);


		//set Stiffness false to allow movement
		stiffness = 0.0f;
		time = 1.0f;
		for(int i=0; i<4;i++)
			motion.stiffnessInterpolation(jointNames[i], stiffness, time);
*/

	  }catch (const AL::ALError& e) {
		    std::cerr << "Caught exception: " << e.what() << std::endl;
		    exit(1);
		  }

}
