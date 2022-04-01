#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
typedef struct //9
{
  int A,N;
  float T,array_a[10],array_b[10];
}list;
float signal(float t,int A,float T)
{
  float s;
  if ((t>=0)&&(t<=3*T/8))
  {
    s=A*(t/(3*T/8));
  }
  if ((t>3*T/8)&&(t<=T))
  {
    s=A-A/(5*T/8)*(t-3*T/8);
  }
  return s;
}
int main()
{
  FILE *_f1,*_f2,*_f3;
  list parameters;

  parameters.A=5;
  parameters.N=200;
  parameters.T=0.16;
  float t=0;
  float array_t[parameters.N],array_s[parameters.N];
  _f1=fopen("Lab8.1.txt","wa");
  float h=parameters.T/parameters.N;
  int i;
  for (i=0;i<=parameters.N;i++)
  {
    fprintf(_f1,"%f %f\n",t,signal(t,parameters.A,parameters.T));
    array_t[i]=t;
    array_s[i]=signal(t,parameters.A,parameters.T);
    t+=h;
  }
  fclose(_f1);

  return 0;
}
