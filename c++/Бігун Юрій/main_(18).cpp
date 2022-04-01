#include <iostream>
#include "LogCon.h"

using namespace std;

int main()
{
    bool a,b,c;

    cout<<"| a | b | NOT(a) | AND(a,b) | OR(a,b) | IMP(a,b) | EQU(a,b) | XOR(a,b) |"<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;

    a=true;
    b=true;
    cout << "| "<<a<<" | " << b <<
    " |   "<< NOT(a)<<"    | "<<
    "    "<< AND(a,b)<<"    | "<<
    "   "<< OR(a,b)<<"    | "<<
    "    "<< IMP(a,b)<<"    | "<<
    "    "<< EQU(a,b)<<"    | "<<
    "    "<< XOR(a,b)<<"    | "<<
    endl;

    a=true;
    b=false;
    cout << "| "<<a<<" | " << b <<
    " |   "<< NOT(a)<<"    | "<<
    "    "<< AND(a,b)<<"    | "<<
    "   "<< OR(a,b)<<"    | "<<
    "    "<< IMP(a,b)<<"    | "<<
    "    "<< EQU(a,b)<<"    | "<<
    "    "<< XOR(a,b)<<"    | "<<
    endl;

     a=false;
    b=true;
    cout << "| "<<a<<" | " << b <<
    " |   "<< NOT(a)<<"    | "<<
    "    "<< AND(a,b)<<"    | "<<
    "   "<< OR(a,b)<<"    | "<<
    "    "<< IMP(a,b)<<"    | "<<
    "    "<< EQU(a,b)<<"    | "<<
    "    "<< XOR(a,b)<<"    | "<<
    endl;

     a=false;
    b=false;
    cout << "| "<<a<<" | " << b <<
    " |   "<< NOT(a)<<"    | "<<
    "    "<< AND(a,b)<<"    | "<<
    "   "<<  OR(a,b)<<"    | "<<
    "    "<< IMP(a,b)<<"    | "<<
    "    "<< EQU(a,b)<<"    | "<<
    "    "<< XOR(a,b)<<"    | "<<
    endl;

    cout<<"------------------------------------------------------------------------"<<endl;

    cout<<"--------------------SECOND PART----------------------"<<endl;


    a=true;
    b=true;
    c=true;

    cout<<"| a | b |  c |  F3|"<<endl;
    cout<<"------------------"<<endl;
    cout<<"| "<<a<<" | "<<b<<" |  "<<c<<" |  "<<F3(a,b,c)<<" |"<<endl;


    a=true;
    b=true;
    c=false;

    cout<<"| "<<a<<" | "<<b<<" |  "<<c<<" |  "<<F3(a,b,c)<<" |"<<endl;


    a=true;
    b=false;
    c=true;

   cout<<"| "<<a<<" | "<<b<<" |  "<<c<<" |  "<<F3(a,b,c)<<" |"<<endl;



    a=true;
    b=false;
    c=false;

     cout<<"| "<<a<<" | "<<b<<" |  "<<c<<" |  "<<F3(a,b,c)<<" |"<<endl;

    a=false;
    b=true;
    c=true;

     cout<<"| "<<a<<" | "<<b<<" |  "<<c<<" |  "<<F3(a,b,c)<<" |"<<endl;

    a=false ;
    b=true;
    c=false;

    cout<<"| "<<a<<" | "<<b<<" |  "<<c<<" |  "<<F3(a,b,c)<<" |"<<endl;

    a=false;
    b=false;
    c=false;

     cout<<"| "<<a<<" | "<<b<<" |  "<<c<<" |  "<<F3(a,b,c)<<" |"<<endl;
 cout<<"------------------"<<endl;
    return 0;
}
