#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>
#include "../include/cyberpc.h"
#include "../include/cyberdns.h"
#include "../include/cyberexpert.h"
#include "../include/cyberworm.h"

using boost::property_tree::ptree;  
using namespace std;  

class CyberWorm;
class CyberPC;
class CyberDNS;
class CyberExpert;

 
//Method that reads the computers.xml / network.xml 
void getXmlData(string fileName, string param1, string param2,CyberDNS *cyberdns, string type){
  //Create an empty property tree object
  ptree pt;
  read_xml(fileName,pt);
    
  BOOST_FOREACH( ptree::value_type const&v, pt.get_child("") ) {  
  string field1 = v.second.get<string>(param1); 
  string  field2 = v.second.get<string>(param2);
    
  //Read the computers.xml
  if(type=="comp"){
    CyberPC *cyberpc = new CyberPC(field2,field1);
    CyberPC &comp = *cyberpc;
    cyberdns->AddPC(comp);
    cout<< "Adding to server: " << field1<< endl;
    cout<<field1<<" connected to server"<<endl;
  }

  //read the network.xml
  else if(type=="network"){
      CyberPC &pc1=cyberdns->GetCyberPC(field1);
      CyberPC &pc2=cyberdns->GetCyberPC(field2);
      
      //connecting the computers
      pc1.AddConnection(field2);
      pc2.AddConnection(field1);

      cout << "Connecting " << field1 << " to " << field2 << endl;
      cout << "\t" << field1 << " now connected to " << field2 << endl;
      cout << "\t" << field2 << " now connected to " << field1 << endl;
    }
  }
  
}  

//This method receives the vector of cyber experts, runs over all the experts and invokes clean on the computers list stored in the server (Cyberdns)
//Also after cleaning we update the status and counters of the cyber experts (to indicate that a day has passed)
void performDailyCyberExpertsActivities(CyberDNS *cyberdns,vector<CyberExpert*> expertList){
  vector<string> computerList = cyberdns->GetCyberPCList();
  unsigned int j=0;
  for(unsigned int i=0; i<expertList.size(); i++){
    CyberExpert *expert = expertList[i]; 
    while(expert->getEfficiencyCapacity()>0 && j<computerList.size() && expert->getExpertStatus()=="working"){ 
      CyberPC &pc = cyberdns->GetCyberPC(computerList[j]); 
      j++;
      cout<<"\t"<< expert->getName() << " examining " << pc.getName() <<endl;
      expert->Clean(pc);
      expert->setEfficiencyCapacity(expert->getEfficiencyCapacity()-1); //decrease efficiency of the expert
    }
  }

  //Go over the experts and update their status, update the counters to indicate that a day has passed
  for(unsigned int i=0; i<expertList.size(); i++){

    CyberExpert *expert = expertList[i];

    //Return efficiency to full
    expert->restoreEfficiencyCapacity(); 
    
    if(expert->getInitialRestTime()!=0){
        int daysUntilStatusChange=expert->getdaysLeftUntilStatusChange();
        if(daysUntilStatusChange>0){
        expert->setdaysLeftUntilStatusChange(daysUntilStatusChange-1);
         }
        else if(expert->getExpertStatus()=="working"){
          cout<<"\t"<< expert->getName() << " is taking a break " <<endl;
          expert->setStatus("resting");
          expert->setdaysLeftUntilStatusChange(expert->getCyberExpertRestTime()-1);
        }
        else if(expert->getExpertStatus()=="resting"){
          cout<<"\t"<< expert->getName() << " is back to work " <<endl;
          expert->setStatus("working");
          expert->setdaysLeftUntilStatusChange(expert->getCyberExpertWorkTime()-1);
        }
    }
    
  }
}

//Go over the computers list stored in the server (cyberdns) and invoke run on each one of them
void performDailyComputerActivities(CyberDNS *cyberdns){
  //We need to go over all the computers and check if they can infect other computers
  vector<string> computersList = cyberdns->GetCyberPCList();
  for(unsigned int i=0; i<computersList.size(); i++){
    CyberPC &pc = cyberdns->GetCyberPC(computersList[i]);
    pc.Run(*cyberdns);
  }
}


int main(){
  
   CyberDNS *cyberdns = new CyberDNS();

   getXmlData("computers.xml","name","os",cyberdns, "comp");
   getXmlData("network.xml","pointA","pointB",cyberdns,"network");

   ptree pt;
   read_xml("events.xml",pt);

   int daysToTermination=-1;

   //Get the value in the 'termination' field
   BOOST_FOREACH( ptree::value_type const&v, pt.get_child("") ) {  
    if(v.first=="termination"){
      daysToTermination = boost::lexical_cast<int>(v.second.get<string>("time"));
      daysToTermination++;
     }
   }

   //Go over the 
    vector<CyberExpert*> expertList;

    int day=0;

    BOOST_FOREACH( ptree::value_type const&v, pt.get_child("") ) { 
      
      if(day<daysToTermination){          

            cout << "Day : "<< day << endl;

              //Handle a 'clock in' event
              if(v.first=="clock-in"){
                string name = v.second.get<string>("name"); 
                int workTime = boost::lexical_cast<int>(v.second.get<string>("workTime")); 
                int restTime = boost::lexical_cast<int>(v.second.get<string>("restTime")); 
                int efficiency = boost::lexical_cast<int>(v.second.get<string>("efficiency")); 

                CyberExpert *cyberExpert = new CyberExpert(name, workTime, restTime, efficiency);

                cout<<"\t"<< "Clock-In: "<< name << " began working " <<endl;

                expertList.push_back(cyberExpert);
              }

              //Handle a 'Hack' event
              else if(v.first=="hack"){
                string computerName = v.second.get<string>("computer"); 
                string wormName = v.second.get<string>("wormName"); 
                int wormDormancy = boost::lexical_cast<int>(v.second.get<string>("wormDormancy")); 
                string wormOs = v.second.get<string>("wormOs"); 

                cout<< "\t"<<"Hack occured on "<< computerName <<endl;

                CyberPC &pc=cyberdns->GetCyberPC(computerName);

                CyberWorm *worm = new CyberWorm(wormOs,wormName,wormDormancy);


                pc.Infect(*worm);
                delete worm;
                worm=NULL;
              }

              performDailyCyberExpertsActivities(cyberdns,expertList);
              performDailyComputerActivities(cyberdns);
              

              day++;
      }
  }

  //Loop that continues to perform required activities after there are no new events
  while(day<daysToTermination){

      cout << "Day : "<< day << endl;

      performDailyCyberExpertsActivities(cyberdns,expertList);
      performDailyComputerActivities(cyberdns);

      day++;
  }


  //Delete pointers
  delete cyberdns;
  
  for(unsigned int i=0; i<expertList.size(); i++){
    delete expertList[i];
    expertList[i]=NULL;
  }

  return 0;
}


