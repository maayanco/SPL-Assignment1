#ifndef CYBER_WORM
#define CYBER_WORM
#include <iostream>
#include <string>
#include <vector>

using namespace std; 

class CyberWorm
{
private:
    const string 	cyber_worm_os_;
    const string 	cyber_worm_name_;
    const int 	cyber_worm_dormancy_time_;
    CyberWorm(); // Prevent the use of an empty constructor
 
public:
    CyberWorm(string cyber_worm_os, string cyber_worm_name, int cyber_worm_dormancy_time);
	CyberWorm(const CyberWorm& other); //copy constructor;
	/*CyberWorm& operator=(const CyberWorm &other);*/
	// Add your own functions here

	string getWormName(); ///I Added this

	string getWormOs();

	int getTimeToInfect();

	virtual ~CyberWorm();
};


#endif