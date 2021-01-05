#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  //int id_;
  //void setID(int i);
  void Pid(int pid) {id_ = pid;}
  Process(int i);

  // TODO: Declare any necessary private members
 private:
 //vector<Process> processIDs_;
 int id_;
 float ram_;
 float proc_CPU;
};

#endif