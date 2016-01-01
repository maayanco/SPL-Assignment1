#include "../include/cyberworm.h"

class CyberPC;
class CyberDNS;
class CyberExpert;
class Run;

using namespace std; 
	
	//Constructor
    CyberWorm::CyberWorm(string cyber_worm_os, string cyber_worm_name, int cyber_worm_dormancy_time):cyber_worm_os_(cyber_worm_os),cyber_worm_name_(cyber_worm_name),cyber_worm_dormancy_time_(cyber_worm_dormancy_time){}
	
	//Copy Constructor
	CyberWorm::CyberWorm(const CyberWorm& other):cyber_worm_os_(other.cyber_worm_os_),cyber_worm_name_(other.cyber_worm_name_),cyber_worm_dormancy_time_(other.cyber_worm_dormancy_time_){} 


	//Getter - returns the name of the worm
	string CyberWorm::getWormName(){
		return cyber_worm_name_;
	}

	//Getter - returns the os of the worm
	string CyberWorm::getWormOs(){
		return cyber_worm_os_;
	}

	//Getter - returns the time to infect of the worm
	int CyberWorm::getTimeToInfect(){
		return cyber_worm_dormancy_time_;
	}

	//Destructor
 	CyberWorm::~CyberWorm() {}
