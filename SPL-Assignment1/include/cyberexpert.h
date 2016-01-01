#ifndef CYBER_EXPERT
#define CYBER_EXPERT
#include <iostream>
#include <string>
#include <vector>
#include "../include/cyberpc.h"


class CyberExpert
{
private:
	const string cyber_expert_name_;
    const int cyber_expert_work_time_;
    const int cyber_expert_rest_time_;
    const int cyber_expert_efficiency_;
    CyberExpert(); // Prevent the use of an empty constructor
	
    string expertStatus; 
    int efficiencyCapacity;
    int daysLeftUntilStatusChange;



public:
    CyberExpert(std::string cyber_expert_name_, int cyber_expert_work_time_, int cyber_expert_rest_time_, int cyber_expert_efficiency_);
 	void Clean(CyberPC & cyber_pc); 

    virtual ~CyberExpert();
    
 	void setEfficiencyCapacity(int newEfficiency);
 	void restoreEfficiencyCapacity();
 	void setStatus(string newStatus);

 	int getEfficiencyCapacity();
 	string getExpertStatus();
 	int getdaysLeftUntilStatusChange();
 	void setdaysLeftUntilStatusChange(int newDaysLeft);


 	int getCyberExpertRestTime();
 	int getCyberExpertWorkTime();

    string getName();
    int getInitialRestTime();
};


#endif