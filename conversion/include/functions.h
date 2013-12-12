/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Functions
Version:0.6

This provides functions that may be used in some classes or programs of Fermath
*/

void to_science(double n,double &r1,double &r2) {
    r1=0;
    r2=0;
    while(n>10) {
        n=n/10;
        r2++;
    }
    while(n<1) {
        n=n*10;
        r2--;
    }
    r1=n;
}
//wite a number with scientific notation
void out_science(double r,ostream &out=cout) {
    double r1=0,r2=0;
    to_science(r,r1,r2);
    if(r2==0 && r1!=0) {
        out<<r1;
    }
    if(r1==0) {
        out<<r1;
    }
    if(r1!=0 && r2!=0) {
        out<<r1<<"x10^"<<r2;
    }
}
//*#*#*#*#*#*# --LOW COST GAP-- #*#*#*#*#*#*//
double mcm(double a,double b) {
    double x, z, y=1, i=2;
    if(a<b) {
        x=a;
        z=b;
    }
    else {
        x=b;
        z=a;
    }
    do {
        if(fmod(x,i)==0) {
            if(fmod(z,i)==0) {
                y=y*i;
                x=x/i;
                z=z/i;
                i=2;
            }
            else i++;
        }
        else i++;
    }
    while(i<=x);
    y=y*z*x;
    return y;
}
//*#*#*#*#*#*# --LOW COST GAP-- #*#*#*#*#*#*//
double mcd(double num1,double num2) {
    double t,i=2,mcd=1;
    if(num1>num2) {
        t=num1;
        num1=num2;
        num2=t;
    }
    do {
        if(fmod(num1,i)==0 && fmod(num2,i)==0) {
            mcd=mcd*i;
            num1=num1/i;
            num2=num2/i;
            i=2;
        }
        else {
            i++;
        }
    }
    while(i<=num1);
    return(mcd);
}
//*#*#*#*#*#*# --LOW COST GAP-- #*#*#*#*#*#*//


bool is_prime(unsigned x) {
    bool b=true;
    if(x%2==0 && x!=2) b=false; //if x is pair, it is not prime
    for(unsigned c=3; c<x; c+=2) { //we try each odd number
        if(x%c==0) b=false;
    }
    return b;
}

unsigned next_prime(unsigned x) { //given a number x, it calcules the next prime (not including x)
    unsigned c=x+1;
    while(!(is_prime(c))) { //while c is no a prime number
        c++;
    }
    return c;
}

unsigned prime(unsigned x) { //calcules the prime number x  (first is 1, second is 2, fourth is 5....)
    unsigned p=0;
    for(int i=0; i<x; i++) {
        p=next_prime(p);
    }
    return p;
}

//*#*#*#*#*#*# --LOW COST GAP-- #*#*#*#*#*#*//

vector<int> prime_descomposition(unsigned n) {
    vector<int> descomposition;
    int prime=2;
    while(n>1) {
        if(n%prime==0) {
            n=n/prime;
            descomposition.push_back(prime);
        }
        else {
            prime=next_prime(prime);
        }
    }
    if(descomposition.empty()) descomposition.push_back(1);
    return descomposition;
}

//*#*#*#*#*#*# --LOW COST GAP-- #*#*#*#*#*#*//

string fix_parenthesis(const string &exp) {
    int size=exp.size();
    int count=0;
    string res;
    for(int i=0; i<size; i++) {
        if(exp[i]=='(') count++;
        else if(exp[i]==')') count--;
    }
    if(count>=0) {
        res=exp;
        for(; count>0; count--) res.push_back(')');
    }
    else if(count<0) {
        for(; count<0; count++) res.push_back('(');
        res+=exp;
    }
    return res;
}

//*#*#*#*#*#*# --LOW COST GAP-- #*#*#*#*#*#*//
