#include "../include/cyberpc.h"
#include "../include/cyberworm.h"
#include <vector>

class CyberWorm;
class CyberDNS;
class CyberExpert;
class Run;


using namespace std;
    
   //Constructor
   CyberPC::CyberPC(string cyber_pc_os, string cyber_pc_name):
   cyber_pc_os_(cyber_pc_os),
   cyber_pc_name_(cyber_pc_name),
   cyber_pc_connections_(0), 
   cyber_pc_time_to_infect_(-1){}
  
  //Getter - returns the name of the CyberPC
   const string CyberPC::getName(){
     return cyber_pc_name_;
  }

  //Getter - returns the CyberPC object's time to infect
   int CyberPC::getTimeToInfect(){
      return cyber_pc_time_to_infect_;
   }

   //Setter - sets the provided param as the new time to infect of the current CyberPC 
   void CyberPC::setTimeToInfect(int time_to_infect){
      cyber_pc_time_to_infect_=time_to_infect;
   }

   //this method receives a computer name and adds it to the cyber_pc_connections vector representing a connection between the computers
   void CyberPC::AddConnection(string  second_pc){
      cyber_pc_connections_.push_back(second_pc);
   }
   
   //This method receives a worm and sets it as the worm of the current CyberPC
   void CyberPC::Infect(CyberWorm & worm){
    if(worm.getWormOs() == cyber_pc_os_){
      //delete previous worm
      delete cyber_worm_;
      cyber_worm_=NULL;  

      cyber_worm_= new CyberWorm(worm);

      cout <<"\t \t" <<cyber_pc_name_ << " infected by " << worm.getWormName() << endl;
      cyber_pc_time_to_infect_=worm.getTimeToInfect(); 
    }
    else{

         cout <<"\t \t" << "Worm " << worm.getWormName() << " is incompatible with " << cyber_pc_name_  << endl;
       

    }

  }

  //This method iterates over all the computers that are connected to the current computer and if possible infects them with it's worm
   void CyberPC::Run(const CyberDNS &server){

      if(cyber_pc_time_to_infect_==0 && isInfected()==1){   
        cout <<"\t"  <<cyber_pc_name_ << " infecting... " << endl;   

        for(unsigned int i=0; i<cyber_pc_connections_.size(); i++){
          CyberPC &cyberpc = server.GetCyberPC(cyber_pc_connections_[i]);
          string  wormos=cyber_worm_->getWormOs();
          string  wormname=cyber_worm_->getWormName();
          int wormtime=cyber_worm_->getTimeToInfect();

          //here we create a new worm from the worm that is currently in this computer
          CyberWorm *cyberWorm= new CyberWorm(wormos,wormname,wormtime);
          
          cyberpc.Infect(*cyberWorm);
          delete cyberWorm;
          cyberWorm=NULL;
        }
    }
    else if (cyber_pc_time_to_infect_!=-1){
      int timeToInfect=getTimeToInfect(); 
      setTimeToInfect(timeToInfect-1);
      cout << "\t"  <<getName() <<": Worm "<< cyber_worm_->getWormName() << " is dormant" << endl;
    }
    
  }


  //This method deletes the worm from the current CyberPC (if exists)
   void CyberPC::Disinfect(){
      if(isInfected()==1){
        cout << "\t \t" <<"Worm " << cyber_worm_->getWormName() << " successfully removed from " << cyber_pc_name_ << endl; 
        delete cyber_worm_;
        cyber_worm_=NULL;
        cyber_pc_time_to_infect_=-1;
      }
     
  }

	//This method returns 0 (False) if not infected and 1 (True) if infected 
  bool CyberPC::isInfected(){ 

    if(cyber_worm_== NULL || cyber_worm_==0)
      return 0; 
    else
      return 1; 
  }

  //This destructor deletes the cyber_worm that is set in the current CyberPC
  CyberPC::~CyberPC() {
    if(isInfected()==1){
      delete cyber_worm_;
      cyber_worm_= NULL;
    }
  }
