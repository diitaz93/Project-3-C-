#ifndef Project3_HPP
#define Project3_HPP
//
const double TOL=1e-5;
//
class Curvebase
{
protected:
  double pmin;
  double pmax;
  bool rev;
  double length;
  virtual double xp(double)=0;
  virtual double yp(double)=0;
  virtual double dxp(double)=0;
  virtual double dyp(double)=0;
  double integrate(double);
  double I1(double,double);
  double asi(double, double, double=TOL);
  double unitlength(double);
  double newton(double);
public:
  Curvebase(double, double, bool = true);
  double x(double);
  double y(double);
  virtual ~Curvebase(){};
};
class Domain
{
  Curvebase *sides[4];
  double *x,*y; //Array of coordinates of each inner node
  int m,n; //Number of internal nodes
public:
  //Domain(LeftCurve&, RightCurve&, LowerCurve&, UpperCurve&);
  Domain(Curvebase&,Curvebase&,Curvebase&,Curvebase&); //Constructor
  Domain(const Domain&); //Copy constructor
  Domain& operator=(const Domain&); //Copy assignment
  ~Domain(); // Destructor
  void generate_grid(int,int);//number of internal nodes in each direction
  void Output(); // Writting internal nodes to file
};

#endif

