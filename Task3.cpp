#include <iostream>
#include "Project3.hpp"
#include <cstdio>


class Domain
{
  Curvebase *sides[4];
  double *x,*y; //Array of coordinates of each inner node
  int m,n; //Number of internal nodes
public:
  //Domain(LeftCurve&, RightCurve&, LowerCurve&, UpperCurve&);
  Domain(Curvebase&,Curvebase&,Curvebase&,Curvebase&); //Constructor
  //Domain(const Domain&); //Copy constructor
  //Domain(Domain&&); // Move constructor
  Domain& operator=(const Domain&); //Copy assignment
  ~Domain(); // Destructor
  void generate_grid(int,int);//number of internal nodes in each direction
  void Output(); // Writting internal nodes to file
  int indicator()
  {
    return m;
  }//Test function (temporary)
};

// Constructor
Domain::Domain(Curvebase& s1,Curvebase& s2,Curvebase& s3,Curvebase& s4)
//Domain::Domain(LeftCurve& s1, RightCurve& s2, LowerCurve& s3, UpperCurve& s4)
{
  sides[0]=&s1;//Left
  sides[1]=&s2;//Right
  sides[2]=&s3;//Lower
  sides[3]=&s4;//Upper
  m=n=0;
  x=y=nullptr;
}
//Copy constructor
/*
Domain::Domain(const Domain& d):m(d.m),n(d.n),x(nullptr),y(nullptr)
{
  if(m>0)
    {
      x=new double[m*n];
      y=new double[m*n];
      for(int i=0;i<m*n;i++)
	{
	  x[i]=d.x[i];
	  y[i]=d.y[i];
	}
    }
}
*/
// Move constructor
/*
Domain::Domain(Domain&& d) noexcept:m(d.m),n(d.n),x(d.x),y(d.y)
{
  d.m=0;
  d.n=0;
  d.x=nullptr;
  d.y=nullptr;
}
*/
// Copy assignment
Domain& Domain::operator=(const Domain& d)
{
  if(this!=&d)
    {//dont copy to itself
      if(m==d.m && n==d.n)
	for(int i=0;i<m*n;i++)
	  {
	    x[i]=d.x[i];
	    y[i]=d.y[i];
	  }
      else
	{
	  if(m>0)
	    {
	      delete [] x;
	      delete [] y;
	      x=y=nullptr;
	    }
	  if(m>0)
	    {
	      x=new double[m*n];
	      y=new double[m*n];
	      for(int i=0;i<m*n;i++)
		{
		  x[i]=d.x[i];
		  y[i]=d.y[i];
		}
	    }
	}
    }
}
// Destructor
Domain::~Domain()
{
  if(m>0)
    {
      delete [] x;
      delete [] y;
    }
}
void Domain::generate_grid(int m_,int n_)
{
  //m on x;n on y
  if(m_<=0 || n_<=0)
    {
      std::cerr<<"meaningless number!";
      exit(EXIT_FAILURE);
    }
  else
    {
      if(m>0)
	{
	  delete [] x;
	  delete [] y;
	}
      m=m_;n=n_;
      x=new double[m*n];
      y=new double[m*n];
      double ksi,eta,sigma;
      double Corner_x[4]={-10.0,5.0,-10.0,5.0};
      //Specialized here, only works in this problem
      double Corner_y[4]={0.0,0.0,3.0,3.0};
      int k;
      const double delta=3.0;
      for(int i=0;i<n;i++)//x direction 
	for(int j=0;j<m;j++)//y direction
	  {
	    ksi=i/m;
	    sigma=1.0+((std::tanh(delta(ksi-1))))/(std::tanh(ksi));
	    //non-uniform distribution
	    eta=j/n;
	    k=i*m+j;//Lexicograghical rule
	    x[k]=ksi * (*sides[0]).x(eta) + (1-ksi) * (*sides[1]).x(eta)
	      + eta * (*sides[2]).x(sigma) + (1-eta) * (*sides[3]).x(ksi)
	      - sigma*eta * Corner_x[0] - (1-sigma)*eta * Corner_x[1]
	      - ksi*(1-eta) * Corner_x[2] - (1-ksi)*(1-eta) * Corner_x[4];
	    y[k]=ksi * (*sides[0]).y(eta) + (1-ksi) * (*sides[1]).y(eta)
	      + eta * (*sides[2]).y(sigma) + (1-eta) * (*sides[3]).y(ksi)
	      - sigma*eta * Corner_y[0] - (1-sigma)*eta * Corner_y[1]
	      - ksi*(1-eta) * Corner_y[2] - (1-ksi)*(1-eta) * Corner_y[4];
	  }
    }
}
void Domain::Output()
{
  FILE *fp;
  fp=fopen("outfile.bin","wb");
  fwrite(x,sizeof(double),m*n,fp);
  fwrite(y,sizeof(double),m*n,fp);
  fclose(fp);
}
