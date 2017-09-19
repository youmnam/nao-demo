// http://doc.aldebaran.com/1-14/dev/python/making_nao_move.html
// http://doc.aldebaran.com/1-14/dev/naoqi/index.html#naoqi-blocking-non-blocking
#include <iostream>
#include <alerror/alerror.h>

using namespace std;

int main(int argc, char* argv[]) {

	string robotIP = "192.168.1.88";
	AL::ALMotionProxy motion(robotIP, 9559);
	AL::ALTextToSpeechProxy tts(robotIP, 9559);

	//------------Moving------------//
	motion.moveInit();
	int id;
	/*
	 * calling the function on the post attribute make the behavior executing in the background.
	 * Every proxy you create has an attribute named ‘post’ that you can use to call long methods in the background.
	 * making the calling unblocking (done in parallel)
	 */
	id = motion.post.move(0.5,0,0);
    if (motion.isRunning(id))
    	cout << " is running " <<endl;
    else
    	cout<< " stopped" << endl;

    //------------Talking------------//
    tts.say("I am walking right now please don't interrupt me");

}
