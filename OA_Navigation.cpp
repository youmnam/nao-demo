#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/alautonomousmovesproxy.h>
#include <alproxies/alsonarproxy.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/almemoryproxy.h>

#include <alproxies/alledsproxy.h>
using namespace std;

string pip;
int pport;
void parsingArguments(int argc, char* argv[]);
void moveForward();
void rotateLeft();
void rotateRight();
void initMotors();
void stopMotors();
void moveBackward();

int main(int argc, char* argv[]){
	parsingArguments(argc,argv);

	AL::ALSonarProxy sonarproxy(pip,pport);
	AL::ALMemoryProxy memproxy(pip,pport);
	//AL::ALMotionProxy motion(pip,pport);

	//sonarproxy.subscribe("myApp");

	while(true){
		AL::ALValue isFrontTouchedVal  = memproxy.getData("FrontTactilTouched");
		AL::ALValue isMiddleTouchedVal = memproxy.getData("MiddleTactilTouched");

		char c;
		if(isFrontTouchedVal == AL::ALValue(1.0)){

			while(isMiddleTouchedVal != AL::ALValue(1.0)){
				AL::ALValue sonarLeftValue 		   = memproxy.getData("SonarLeftDetected");
				AL::ALValue sonarRightValue 	   = memproxy.getData("SonarRightDetected");

			//	isMiddleTouchedVal = memproxy.getData("MiddleTactilTouched");

				cout << "left ::" << memproxy.getData("SonarLeftDetected").toString() << endl;
				cout << "Right::" << memproxy.getData("SonarRightDetected").toString()<< endl;

				qi::os::sleep(1);

			/*	if( !(sonarLeftValue < AL::ALValue(0.2))  && !(sonarRightValue < AL::ALValue(0.2)) ){
				  if(c == 'l'){
						motion.moveToward(0,0.2,0);
						qi::os::sleep(5);
				  }
				  if(c == 'r'){
				  		motion.moveToward(0,-0.2,0);
				  		qi::os::sleep(5);
				  }
					motion.moveToward(0.2,0,0);
					c = '.';
				}
                if(sonarLeftValue  < AL::ALValue(0.2)  ){
                		std::cout << "obstacle*" <<endl;
    					motion.stopMove();
                		motion.moveToward(-0.2,0,0);
                		qi::os::sleep(5);
                		c= 'l';
                }
                if(sonarRightValue  < AL::ALValue(0.2)  ){
                    	std::cout << "obstacle**" <<endl;

                    	motion.stopMove();
                    	motion.moveToward(-0.2,0,0);
                    	qi::os::sleep(5);
                    	c='r';
                }*/

			}
		}

	}

	//sonarproxy.unsubscribe("myApp");
	return 0;
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
