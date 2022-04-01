#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
 ofstream fout("q.txt");
 double x, y;
 for (x = -4; x <= 4; x=x+0.1)
        {
       if (x <= -3)
        {
            y = 3;
        }
        else
            if (x >= -3 && x < 0)
            {
                y = x*(-1);
            }
            else
                if (x >= 0 && x<= 2)
                {
                    y = x;
                }
                else
                    if (x > 2)
                    {
                        y = 2;
                    }
            fout << x<<" ";
            fout << y<<" ";


        }
 fout.close();

 ifstream fin("q.txt");
 float *a,b;int n=0;
 a=new float [100];
 while (!fin.eof())
 {
     fin>>a[n];
     if(!fin.eof())
     {
         cout<<a[n]<<"  ";
         n++;
     }
 }
 for(int i=0;i<n-1;i++)
 for(int j=0;j<n-i-1;j++)
 if(a[j]>a[j+1])
 {
     b=a[j];
     a[j]=a[j+1];
     a[j+1]=b;
 }
 fin.close();
 ofstream f("sort.txt");
 f<<" ";
 for (int i=0;i<n;i++)
 {
     if(i<n-1)
     {
         f<<a[i]<<"  ";
     }
     else
     {
         f<<a[i];
     }
 }
 f.close();
 delete [] a;
}
