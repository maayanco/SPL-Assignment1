#include "../include/cyberdns.h"

using namespace std;
class CyberWorm;
class CyberPC;
class CyberExpert;
class Run;

//Empty Constructor
CyberDNS::CyberDNS():cyber_DNS_(){}

//Constructor
void CyberDNS::AddPC(CyberPC &cyber_pc_){ //This receives a reference of type CyberPC
  cyber_DNS_.insert(pair<const string, CyberPC&>(cyber_pc_.getName(), cyber_pc_));
}

//This method receives a computer name and returns the CyberPC object with that key
CyberPC& CyberDNS::GetCyberPC(const string & cyber_pc_name) const{
	map<const string, CyberPC&>::const_iterator it;
	
	for(it = cyber_DNS_.begin(); it != cyber_DNS_.end(); it++) 
	{
		if((it->first)==cyber_pc_name){
			return (it->second);
		}	
	}

	CyberPC *emptypc=NULL;
	return *(emptypc);
	
}

//This method returns a list of all the names of the CyberPc objects in the map 
vector<string> CyberDNS::GetCyberPCList(){
	vector<string> pcList;

	map<const string, CyberPC&>::reverse_iterator it;

	for (it = cyber_DNS_.rbegin(); it != cyber_DNS_.rend(); it++)
	{
		pcList.push_back((it->second).getName());
	}

	return pcList;
} 

//This Destructor iterates over the map and deletes every CyberPC object in it
CyberDNS::~CyberDNS() {
	map<const string, CyberPC&>::iterator it;
	for (it = cyber_DNS_.begin(); it != cyber_DNS_.end(); it++)
	{
		CyberPC &pc=(it->second);
		delete &pc;
	}
}
