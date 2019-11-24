#include "Project3.hpp"
#include "Task1.cpp"
#include "Task2.cpp"
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
  UpperCurve L4(-10.0,5.0);
  std::cout<<L3.x(0.5)<<std::endl;
  Domain D(L1,L2,L3,L4);
  D.generate_grid(15,3);
  std::cout<<D.indicator()<<"\n";
  return 1;
}
