#include "processor.h"

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
// I see you have used float here. It is correctly implemented but i would like to just inform you that 
// when you will be solving competitive questions on sites like Codeforces, CodeChef then you have to 
//take care that double has more precision than the float and so even though your algorithm is correct 
//but you are not getting the correct answer because of the precision issue.

double Processor::Utilization() { 
    

    float Idle = idle +iowait;
    float NonIdle = user+nice+system+irq+softirq+steal;
    float Total = Idle+NonIdle;
    calculation_ = (Total - Idle)/Total;
 
    
  return calculation_;} 

     