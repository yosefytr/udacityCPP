#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include<iterator>

#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include "linux_parser.h"

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
//float c1, c2, c3, c4;
//float c5, c6, c7, c8;
//float c9, c10;
string c0;
string line;
float value_;

//FROM processor& System::Cpu()
std::ifstream stream (kProcDirectory + kStatFilename);
if (stream.is_open()){

std::getline(stream, line);
std::istringstream linestream(line);


//linestream>>c0>>c1>>c2>>c3>>c4>>c5>>c6>>c7>>c8>>c9>>c10;
linestream>>c0;

for (int i = 0; i<10; i++){
    linestream>>value_;
    if (i==0){cpu_.setUser(value_);}
    if (i==1){cpu_.setNice(value_);}
    if (i==2){cpu_.setSystem(value_);}
    if (i==3){cpu_.setIdle(value_);}
    if (i==4){cpu_.setIowait(value_);}
    if (i==5){cpu_.setIrq(value_);}
    if (i==6){cpu_.setSoftirq(value_);}
    if (i==7){cpu_.setSteal(value_);}
    if (i==8){cpu_.setGuest(value_);}
    if(i==9){cpu_.setGuestNice(value_);}

}

/*cpu_.setUser(c1);
cpu_.setNice(c2);
cpu_.setSystem(c3);
cpu_.setIdle(c4);
cpu_.setIowait(c5);
cpu_.setIrq(c6);
cpu_.setSoftirq(c7);
cpu_.setSteal(c8);
cpu_.setGuest(c9);
cpu_.setGuestNice(c10); }*/

}
stream.close();
return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    const vector<int> ids_ = LinuxParser::Pids();
    //per reviewer comment: clear vector before pushing new processes into it
    processes_.clear();

    for (const int& pid: ids_){
        //Process process(pid);
        processes_.emplace_back(Process(pid));
       
    }
    
    std::sort(processes_.begin(), processes_.end()); //see process.cpp < operator
    return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    
    return LinuxParser::Kernel(); }
    

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    
    return LinuxParser::MemoryUtilization(); }
    

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    
    return LinuxParser::OperatingSystem();}

    

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    
       
    return LinuxParser::RunningProcesses();}
    
   

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); }
    
    

// TODO: Return the number of seconds since the system started running
long System::UpTime() { 
    
   return LinuxParser::UpTime(); }
    
  