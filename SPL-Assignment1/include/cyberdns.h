#ifndef CYBERDNS_H
#define CYBERDNS_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/cyberpc.h"

using namespace std;

class CyberPC; //Forward deceleration

class CyberDNS
{
private:
    map<const string, CyberPC&> cyber_DNS_;	//Hash map to hold PC names and pointers

 
public:
    CyberDNS();
    void AddPC(CyberPC & cyber_pc_);
    CyberPC & GetCyberPC(const string & cyber_pc_name) const;	
	vector<string> GetCyberPCList(); 		// Return list of PC's as a vector of strings.
													// All access to PC objects should use this function
													// Do not store pointers elsewhere!
	virtual ~CyberDNS();
};

#endif
