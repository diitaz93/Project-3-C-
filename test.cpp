#include "Project3.hpp"
#include "Task1.cpp"
#include "Task3.cpp"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
  LeftCurve L1(0.0,3.0);
  RightCurve L2(0.0,3.0);
  LowerCurve L3(-10.0,5.0);
  //std::cout<<L1.LLL()<<std::endl;
  UpperCurve L4(-10.0,5.0);
  //std::cout<<L2.LLL()<<std::endl;
  //std::cout<<L3.LLL()<<std::endl;
  //std::cout<<L4.LLL()<<std::endl;
 
  Domain D(L1,L2,L3,L4);
  D.generate_grid(2,3);
  return 1;
}
