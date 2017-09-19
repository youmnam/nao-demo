#include <alproxies/albehaviormanagerproxy.h>
#include <iostream>
using namespace std;

int pport = 9559;
std::string pip = "192.168.1.65";


int main(){

	AL::ALBehaviorManagerProxy manager(pip,pport);
    AL::ALValue names=manager.getRunningBehaviors();

   for(int i = 0; i<names.getSize() ; i++){
    cout << "stop behavior :"<< names[i].toString() << endl;
    manager.stopBehavior(names[i]);

   }

   qi::os::sleep(5);
   for(int i = 0; i<names.getSize() ; i++){
       cout << "run behavior :"<< names[i].toString() << endl;
       manager.runBehavior(names[i]);

      }
	return 0;
}
