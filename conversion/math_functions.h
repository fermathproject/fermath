/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Math Functions
Version:0.1

This provides the needed methods to make the conversions between units (needed by the conversion class)
*/

const double pi=3.14159265358979323846; //number pi
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
//*#*#*#*#*#*# --LOW COST SEPARATION-- #*#*#*#*#*#*//
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

//*#*#*#*#*#*# --LOW COST SEPARATION-- #*#*#*#*#*#*//
//Do binary operations
double calc(int cal,double n1,double n2) {
    double r=0;
    switch(cal) {
    case 1:
        r=n1+n2;
        break;
    case 2:
        r=n1-n2;
        break;
    case 3:
        r=n1*n2;
        break;
    case 4:
        r=n1/n2;
        break;
    case 5:
        r=pow(n1,n2);
        break;
    case 6:
        r=pow(n1,1/n2);
        break;
    case 7:
        r=log(n1)/log(n2);
        break;
    case 8:
        r=fmod(n1,n2);
        break;
    case 9:
        r=mcm(n1,n2);
        break;
    case 10:
        r=mcd(n1,n2);
        break;
    }
    return r;
}
//*#*#*#*#*#*# --LOW COST SEPARATION-- #*#*#*#*#*#*//
//do unary operations
double calc(int cal, double n) {
    double r=0;
    switch(cal) {
    case 1:
        r=sqrt(n);
        break;
    case 2:
        r=n*n;
        break;
    case 3:
        r=sin(n);
        break;
    case 4:
        r=cos(n);
        break;
    case 5:
        r=tan(n);
        break;
    case 6:
        r=asin(n);
        break;
    case 7:
        r=acos(n);
        break;
    case 8:
        r=atan(n);
        break;
    case 9:
        r=(pi*n)/180;
        break;
    case 10:
        r=(180*n)/pi;
        break;
    case 11:
        r=exp(n);
        break;
    case 12:
        r=sinh(n);
        break;
    case 13:
        r=cosh(n);
        break;
    case 14:
        r=tanh(n);
        break;
    case 15:
        r=fabs(n);
        break;
    case 16:
        r=log(n);
        break;
    }
    return r;
}
//*#*#*#*#*#*# --LOW COST SEPARATION-- #*#*#*#*#*#*//
//return two values to write in a natural way large numbers
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
//*#*#*#*#*#*# --LOW COST SEPARATION-- #*#*#*#*#*#*//
//wite a number with scientific notation
void out_science(double r) {
    double r1=0,r2=0;
    to_science(r,r1,r2);
    if(r2==0 && r1!=0) {
        cout<<r1;
    }
    if(r1==0) {
        cout<<r1;
    }
    if(r1!=0 && r2!=0) {
        cout<<r1<<"x10^"<<r2;
    }
}
