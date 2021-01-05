#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  double Utilization();  // TODO: See src/processor.cpp

  void setUser(float u) {user = u;}
  void setNice(float n) {nice = n;}
  void setSystem(float s) {system = s;}
  void setIdle(float i) {idle = i;}
  void setIowait(float iow) {iowait = iow;}
  void setIrq(float irq) {irq = irq;}
  void setSoftirq(float soft) {softirq = soft;}
  void setSteal(float st) {steal = st;}
  void setGuest(float guest) {guest = guest;}
  void setGuestNice(float guestn) {guest_nice = guestn;}

  // TODO: Declare any necessary private members
 private:

 // user nice system idle iowait irq softirq steal guest guest_nice
  float user;
  float nice;
  float system;
  float idle;
  float iowait;
  float irq;
  float softirq;
  float steal;
  float guest;
  float guest_nice;
  float calculation_;
  


};



#endif