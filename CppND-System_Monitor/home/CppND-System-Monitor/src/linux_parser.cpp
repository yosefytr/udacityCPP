#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream> //i added this
#include <unordered_map> //i added this
#include "linux_parser.h"
#include <bits/stdc++.h>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

template <typename T>

T findValueByKey(std::string const &key_, std::string const &filename){

string line, key;
T value;
std::ifstream filestream(LinuxParser::kProcDirectory + filename);
if (filestream.is_open()){
  while (std::getline(filestream, line)){
    std::istringstream linestream(line);
    while (linestream>>key>>value){
        if (key == key_){return value;}

    }

  }

}

return value;
};

template <typename T>

T getValueofFile(std::string const &filename){
  
string line;
T value;

std:: ifstream fstream(LinuxParser::kProcDirectory+filename);
if (fstream.is_open()){
  while (std::getline(fstream, line)){
    std:: istringstream linestream(line);
    linestream>>value;
  }
}
fstream.close();
return value;
};

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  filestream.close();
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  //equivalent of cat /proc/version
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    //from linestream lop off firsttoken (linestream) then second token
    //os, then third version, then keep kernel which is 4.15.0-1080-gcp
    linestream >> os >> version >> kernel;
  }
  stream.close();
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 

  string memTotal = "MemTotal:";
  string memFree = "MemFree:";

  float total_ = findValueByKey<float>(memTotal, kMeminfoFilename);
  float free_ = findValueByKey<float>(memFree, kMeminfoFilename);

  return (total_ - free_)/total_;

  
}



// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  
  return long(getValueofFile<long>("uptime"));
}



  
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  vector<string> jiffies_ = LinuxParser::CpuUtilization();
  float sum = 0;
  string invalid_num = "";
  for (unsigned int i = 0; i<jiffies_.size(); i++){

    try {
      std::cout<<stof(invalid_num)<<"\n";
    }  catch (const std::invalid_argument){
      std::cerr<<"invalid argument"<<"\n";
    }
    if (jiffies_[i]!=invalid_num){
    sum = sum + stof(jiffies_[i]);}
    if (jiffies_[i] == invalid_num){
    jiffies_[i] = "0";sum = sum + stof(jiffies_[i]);}
  
  } return sum; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  
  string v14, v15, v16, v17, v22, v0;
  string line;
  //float val_;
  float time_;
  std::ifstream filestream(kProcDirectory+ std::to_string(pid)+kStatFilename);
  if (filestream.is_open()){
      while(std::getline(filestream, line)){
          std::istringstream linestream(line);
         

        for (int i = 0; i<13; i++){ //i<13 or 14? (13)
          
          linestream>>v0;
        }
        //by the time we leave the loop, the value 'pointed at' is the desired value
      
        linestream>>v14>>v15>>v16>>v17;
              
      
        //used https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
        //also referenced https://knowledge.udacity.com/questions/125362
        //and https://knowledge.udacity.com/questions/334877
       
      time_ = (std::stof(v14)+ std::stof(v15) + std::stof(v16) + std::stof(v17));
   
      

     
      }

  
  }
return time_; }
  

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  vector<string> jiffies_ = LinuxParser::CpuUtilization();
  float sum_ = 0;
  jiffies_.erase(jiffies_.begin()+3);

  for (unsigned int i = 0; i<jiffies_.size(); i++){

    sum_ = sum_+std::stof(jiffies_[i]);  
  }

  
  return sum_; }


// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  vector<string> jiffies_ = LinuxParser::CpuUtilization();
  return std::stof(jiffies_[3]);}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line;
  string value;
  vector<string> cpu_values;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream>>value;

    for (int i =0; i<10; i++){
      linestream>>value;
      if (i==0){cpu_values.emplace_back(value);}
      if (i>0){cpu_values.push_back(value);}
       std::cout<<value<<"\n";
    }

  }
  return cpu_values; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  
  
  string line;
  string key_a;
  
  int value = 0;
  bool k = 1;
 
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line) && k) {
     
      std::istringstream linestream(line);
      linestream>>key_a>>value;
      if (key_a == "processes"){
       
        k=0;}

    }
  }
  return value;
}
  

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  
  
  
  string line;
  string key_a;
  
  int value = 0;
  bool k = 1;
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line) && k) {
     
      std::istringstream linestream(line);
      linestream>>key_a>>value;
      if (key_a == "procs_running"){
       
        k=0;}

    }
  }
  return value;
}
  
  
  

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  

  return string(getValueofFile<string>(to_string(pid)+kCmdlineFilename));

}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  
  
  
  string code, ram_, line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid)+kStatusFilename);
  if (filestream.is_open()){

    do {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream>>code>>ram_;

/*  Because VmSize is the sum of all the virtual memory as you can see on the manpages also.
Search for VmSize and you will get the following line

*VmSize: Virtual memory size.

Whereas when you use VmData then it gives the exact physical memory being used as a part of Physical RAM. 
So it is recommended to replace the string VmSize with VmData as people who will be looking at your GitHub might 
not have any idea of Virtual memory and so they will think you have done something wrong! */

    } while(code.compare("VmData:")!=0);
    //std::cout<<"uid: "<<uid<<"\n";

    float ramMB_ = std::stof(ram_)/1024;
    //filestream.close();
    ram_ = to_string(ramMB_);
    ram_.resize(6);
    
    return ram_;
  }
  
return string();
  
  
}


// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string code, uid, line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid)+kStatusFilename);
  if (filestream.is_open()){

    do {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream>>code>>uid;

    } while(code.compare("Uid:")!=0);
  
    filestream.close();
    return uid;
  }
  
return string();
  
  
}
  

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function

string LinuxParser::User(int pid) { 

string line;
string s1, s2, s3;
string uid = LinuxParser::Uid(pid);
std::ifstream filestream(kPasswordPath);
if (filestream.is_open()){
  
do {  
  std::getline(filestream, line);
  std::replace(line.begin(), line.end(), ':', ' '); //splits the one line into different segments
  std::istringstream linestream(line);

  linestream>>s1>>s2>>s3;
 
} while (s3.compare(uid)!=0);

}

return s1; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  string value;

  std::ifstream filestream(kProcDirectory + std::to_string(pid)+ kStatFilename);
  if (filestream.is_open()){
      
        std::istringstream linestream(line);
       

        for (int i = 0; i<22; i++){
          filestream>>value;

        }
   
      
  }
   return LinuxParser::UpTime() - std::stol(value)/sysconf(_SC_CLK_TCK);;
}
  