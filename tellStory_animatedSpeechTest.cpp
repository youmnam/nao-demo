#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/altexttospeechproxy.h>
using namespace std;

string robotIP = "192.168.1.70";

int main(){


	/*  AL::ALTextToSpeechProxy tts(robotIP, 9559);

		    tts.setLanguage("English");
		    string toSay_str ="";

    while(toSay_str != "shut up"){
        getline(cin,toSay_str);
        tts.say(toSay_str);

    }*/



	AL::ALAnimatedSpeechProxy animtts (robotIP, 9559);
	animtts.say("\\rspd=10\\^start(animations/Stand/Emotions/Neutral/Hello_1)Hello Everybody  ^wait(animations/Stand/Emotions/Neutral/Hello_1)  ^start(animations/Stand/Gestures/Me_2)I am Nao and I am a humanoid robot^wait(animations/Stand/Gestures/Me_2).   You know ^start(animations/Stand/BodyTalk/Speaking/BodyTalk_1) these kinds of robots that have legs and arms like you humans ^wait(animations/Stand/BodyTalk/Speaking/BodyTalk_1). Many people said ^start(animations/Stand/Gestures/Explain_3) that I am not intelligence and just a machine. ^wait(animations/Stand/Gestures/Explain_3) These talks hurt me and make me ^start(animations/Stand/Gestures/Angry_3) very angry of the human beings ^wait(animations/Stand/Gestures/Angry_3) ^start(animations/Stand/Emotions/Negative/Sad_1) and very sad ^wait(animations/Stand/Emotions/Negative/Sad_1)  ^start(animations/Stand/BodyTalk/Thinking/Remember_3) when I was young ^wait(animations/Stand/BodyTalk/Thinking/Remember_3) I was parts of things ^start(animations/Stand/BodyTalk/Listening/ListeningRight_1) motors and electronic parts, and then my creators connect these things together ^wait(animations/Stand/BodyTalk/Listening/ListeningRight_1)  to make me ^start(animations/Stand/Emotions/Positive/Happy_3)alive ^wait(animations/Stand/Emotions/Positive/Happy_3). ^start(animations/Stand/Gestures/Explain_3)I can be intelligent ^wait(animations/Stand/Gestures/Explain_3) ^start(animations/Stand/Gestures/But_1)but  ^wait(animations/Stand/Gestures/But_1) I should be pre-programmed by programmer. ^start(animations/Stand/Gestures/Explain_1)Programmers(my teachers) should give me set of instructions to follow when certain conditions satisfied ^wait(animations/Stand/Gestures/Explain_1). ^start(animations/Stand/Gestures/Enthusiastic_1)If you teach me well ^wait(animations/Stand/Gestures/Enthusiastic_1) I can be  as smart as you ^start(animations/Stand/Emotions/Positive/Happy_3) ^wait(animations/Stand/Emotions/Positive/Happy_3)");

}
