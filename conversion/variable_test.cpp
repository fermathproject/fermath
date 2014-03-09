/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Variable Test
Version:0.7
*/

//this program tests the variable class in the file variable.h
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
using namespace std;
#include "include/magnitude.h"
#include "include/variable.h"

int main() {
    cout<<"Fermath Variable Test "<<version<<endl;
    conversion conv;
    op add("+",1,binary_operator);
    op sus("-",2,binary_operator);
    op mul("*",3,binary_operator);
    op div("/",4,binary_operator);
    op elev("^",1,unary_operator);
    int id=2;
    //DISTANCE
    conv.clear();
    unit m(string("meters"),string("m"),conv,id);
    conv.add_operation(mul,1000);
    unit km(string("kilometros"),string("km"),conv,id);
    id++;
    //TIME
    conv.clear();
    unit s(string("seconds"),string("s"),conv,id);
    conv.add_operation(mul,3600);
    unit h(string("hora"),string("h"),conv,id);
    variable var(10,km); //10 km
    variable var2(105,m); //105 m
    variable var3(12,s);  //12 s
    unit sp=km*s;
    sp.show();
    cout<<endl;
    var3.set_unit(sp);
    /*cout<<"--"<<(km.null_unit())<<"-"<<(m.null_unit())<<"-"<<(s.null_unit())<<endl;
    km.show();
    cout<<endl;
    m.show();
    cout<<endl;
    cout<<"**"<<m.mag_id()<<endl;*/
    variable varx(12,sp);
    var.show();
    cout<<endl;
    var2.show();
    cout<<endl;
    var3.show();
    cout<<endl;
    varx=var*var3;
    //  varx.show();
    cout<<endl;
    //cout<<km*s;
    cout<<endl;
    /*varx=var+var2;
    cout<<var<<"+"<<var2<<"="<<varx<<endl;
    cout<<var<<"-"<<var2<<"="<<(var-var2)<<endl;
    cout<<var<<"*"<<var2<<"="<<(var*var2)<<endl;
    // cout<<var<<"/"<<var2<<"="<<(var/var2)<<endl;
    /* cout<<"var1==var2:"<<(var==var2)<<endl;
    cout<<"var1!=var2:"<<(var!=var2)<<endl;
    cout<<"Checking variables with no unit"<<endl;
    variable var3(10);
    variable var4(42.54);
    cout<<var3<<endl<<var4<<endl;
    cout<<(var3+var4)<<" "<<(var3-var4)<<endl;
    cout<<(-var3)<<endl;
    cout<<(var3*var4)<<endl;
    cout<<varx<<"*"<<var3<<"="<<(varx*var3)<<endl;*/
    return 0;
}
