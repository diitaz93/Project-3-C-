#include "Project3.hpp"
#include <cmath>
class LowerCurve:public Curvebase
{
  double xp(double p)
  {
    return p;
  }
  double yp(double p)
  {
    if(p>-10 && p<-3)
      return 0.5/(1+exp(-3*(p+6)));
    else if(p>-3 && p<5)
      return 0.5/(1+exp(3*p));
    else
      return 0.0;
  }
  double dxp(double p)
  {
    return 1.0;
  }
  double dyp(double p)
  {
    if(p>-10 && p<-3)
      {
	double t=-3*(p+6);
	return 1.5*exp(t)/((1+exp(t))*(1+exp(t)));
      }
    else if(p>-3 && p<5)
      {
	double t=3*p;
	return -1.5*exp(t)/((1+exp(t))*(1+exp(t)));
      }
    else
      return 0.0;
  }
public:
  LowerCurve(double a,double b):Curvebase(a,b)
  {
    //   length=integrate(pmax);
  }
  ~LowerCurve(){};
};

class LeftCurve:public Curvebase
{
  double xp(double p)
  {
    return -10.0;
  }
  double yp(double p)
  {
    if(p<3 && p>0)
      return p;
    else
      return 0.0;
  }
  double dxp(double p)
  {
    return 0.0;
  }
  double dyp(double p)
  {
      return 1.0;
  }
public:
  LeftCurve(double a,double b):Curvebase(a,b){}
  ~LeftCurve(){};
};

class RightCurve:public Curvebase
{
  double xp(double p)
  {
    return 5.0;
  }
  double yp(double p)
  {
    if(p<3 && p>0)
      return p;
    else
      return 0.0;
  }
  double dxp(double p)
  {
    return 0.0;
  }
  double dyp(double p)
  {
      return 1;
  }
public:
  RightCurve(double a,double b):Curvebase(a,b){}
  ~RightCurve(){};
};

class UpperCurve:public Curvebase
{
  double xp(double p)
  {
    if(p<5 && p>10)
      return p;
    else
      return 0.0;
  }
  double yp(double p)
  {
    return 3.0;
  }
  double dxp(double p)
  {
      return 1.0;;
  }
  double dyp(double p)
  {
    return 0.0;
  }
public:
  UpperCurve(double a,double b):Curvebase(a,b){}
  ~UpperCurve(){};
};
