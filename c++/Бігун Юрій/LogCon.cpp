bool AND(bool a, bool b) {
	if (a==true && b==true) return true;
	else return false;
}
bool NOT(bool a) {
	if (a==false) return true;
	else return false;
}
bool OR(bool a, bool b) {
	if (a==false && b==false) return false;
	else return true;
}
bool XOR(bool a, bool b){
	if ((a==true && b==true) || (a==false && b==false)) return false;
	else return true;
	}
bool IMP(bool a, bool b) {
	if (a==true && b==false) return false;
	else return true;
}
bool EQU(bool a, bool b) {
	if ((a==true && b==true) || (a==false && b==false)) return true;
	else return false;
}

bool F3(bool a, bool b, bool c )
{


    bool x1 ,x2, x3, x4, x5;

    x1=AND(a,NOT(c));
    x2=AND(x1,b);
    x3=IMP(x2,b);
    x4=IMP(x3,c);
    x5=OR(x4,a);

 return x5;
}
