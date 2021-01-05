#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;


// TODO: Return this process's ID

Process::Process(int i){id_ = i;}

int Process::Pid() { 
    
    return id_; }
    
    //return 0; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
   proc_CPU = LinuxParser::ActiveJiffies(id_)/sysconf(_SC_CLK_TCK)/float(UpTime());
   
   return 1*proc_CPU;}

// TODO: Return the command that generated this process
string Process::Command() { 
   // 
    string s = LinuxParser::Command(id_); 
    int l = s.size();
    s.resize(40);
    if (l>40) {s.append("...");}
    return s;}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    ram_ = stof(LinuxParser::Ram(id_));
    return LinuxParser::Ram(id_); }

// TODO: Return the user (name) that generated this process
string Process::User() { 
    //LinuxParser::User(id_);
    return LinuxParser::User(id_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(id_);}
    //return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    //return (this->ram_ > a.ram_ ? true: false);}
   return this->proc_CPU > a.proc_CPU;}
    

  