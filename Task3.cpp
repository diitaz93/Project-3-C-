#include <iostream>
#include "Project3.hpp"
#include <cstdio>
class Domain
{
  Curvebase *sides[4];
  double *x,*y;
  int m,n;
public:
  Domain(Curvebase&,Curvebase&,Curvebase&,Curvebase&);
  Domain(const Domain&);
  Domain(Domain&&);
  Domain& operator=(Domain&);
  ~Domain();
  void generate_grid(int,int);//number of internal nodes in each direction
  void Output();
};
Domain::Domain(Curvebase& s1,Curvebase& s2,Curvebase& s3,Curvebase& s4)
{
  sides[0]=&s1;//Left
  sides[1]=&s2;//Right
  sides[2]=&s3;//Lower
  sides[3]=&s4;
  m=n=0;
  x=y=nullptr;
}
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
Domain::Domain(Domain&& d) noexcept:m(d.m),n(d.n),x(d.x),y(d.y)
{
  d.m=0;
  d.n=0;
  d.x=nullptr;
  d.y=nullptr;
}
Domain& Domain::operator=(const DOmain& d)
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
Domain::~Domain()
{
  if(m>0)
    {
      delete [] x;
      delete [] y;
    }
}
Domain::grid_generation(int m_,int n_)
{
  //m on x;n on y
  if(m_<=0 || n_<=0)
    {
      cerr<<"meaningless number!";
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
      double Corner_x={-10.0,5.0,-10.0,5.0};
      //Specialized here, only works in this problem
      double Corner_y[4]={0.0,0.0,3.0,3.0};
      for(int i=0;i<n;i++)//x direction 
	for(int j=0;j<m;j++)//y direction
	  {
	    ksi=i/m;
	    eta=j/n;
	    k=i*m+j;//Lexicograghical rule
	    x[k]=ksi * sides[0].x(eta) + (1-ksi) * sides[1].x(eta)
	      + eta * sides[2].x(ksi) + (1-eta) * sides[3].x(ksi)
	      - ksi*eta * Corner_x[0] - (1-ksi)*eta * Corner_x[1]
	      - ksi*(1-eta) * Corner_x[2] - (1-ksi)*(1-eta) * Corner_x[4];
	    y[k]=ksi * sides[0].y(eta) + (1-ksi) * sides[1].y(eta)
	      + eta * sides[2].y(ksi) + (1-eta) * sides[3].y(ksi)
	      - ksi*eta * Corner_y[0] - (1-ksi)*eta * Corner_y[1]
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
