#include "../include/cyberexpert.h"

class CyberWorm;
class CyberPC;
class CyberDNS;
class Run;

using namespace std;
	
	//Constructor
	CyberExpert::CyberExpert(string cyber_expert_name_, int cyber_expert_work_time_, int cyber_expert_rest_time_, int cyber_expert_efficiency_): 
	cyber_expert_name_(cyber_expert_name_),
	cyber_expert_work_time_(cyber_expert_work_time_),
	cyber_expert_rest_time_(cyber_expert_rest_time_),
	cyber_expert_efficiency_(cyber_expert_efficiency_),
	expertStatus("working"),
	efficiencyCapacity(cyber_expert_efficiency_),
	daysLeftUntilStatusChange(cyber_expert_work_time_-1){}
    
	//This method invokes the disinfect method on the computer in order to delete the worm from it 
 	void CyberExpert::Clean(CyberPC & cyber_pc){ 
 		if(&cyber_pc!=NULL ){
 			cyber_pc.Disinfect();
 		}	
 	} 

 	//Getter - returns the rest time of the cyber expert
 	int CyberExpert::getCyberExpertRestTime(){
 		return cyber_expert_rest_time_;
 	}

 	//Getter - returns the work time of the cyber expert
 	int CyberExpert::getCyberExpertWorkTime(){
 		return cyber_expert_work_time_;
 	}

 	int CyberExpert::getInitialRestTime(){
 		return cyber_expert_rest_time_;
 	}
 	//Setter - -  sets  newEfficiency as the efficiency of the cyber expert
 	void CyberExpert::setEfficiencyCapacity(int newEfficiency){
 		efficiencyCapacity=newEfficiency;
 	}

 	//This method restores the efficiency of the cyber expert to it's initial efficiency
 	void CyberExpert::restoreEfficiencyCapacity(){
 		efficiencyCapacity=cyber_expert_efficiency_;
 	}

 	//Setter - sets a new status to the cyber expert
 	void CyberExpert::setStatus(string newStatus){
 		expertStatus=newStatus;
 	}

 	//Getter - returns the efficiency capacity;
 	int CyberExpert::getEfficiencyCapacity(){
 		return efficiencyCapacity;
 	}

 	//Getter - returns the cyber expert's status
 	string CyberExpert::getExpertStatus(){
 		return expertStatus;
 	}

 	//Getter - returns the days left until the status of the cyber expert is to be changed
 	int CyberExpert::getdaysLeftUntilStatusChange(){
 		return daysLeftUntilStatusChange;
 	}

 	//Setter - sets the new amount of days left until the status of the cyber expert is to be changed
 	void CyberExpert::setdaysLeftUntilStatusChange(int newDaysLeft){
 		daysLeftUntilStatusChange=newDaysLeft;
 	}

 	//Getter - returns the name of the cyber expert
 	string CyberExpert::getName(){
 		return cyber_expert_name_;
 	}

 	//Destructor
 	CyberExpert::~CyberExpert() {}