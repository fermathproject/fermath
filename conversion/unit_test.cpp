/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project: Unit test
Version:0.8
*/

//This program tests the class unit

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "include/unit.h"
#include "include/functions.h"

main() {
    cout<<"Fermath Unit Test "<<version<<endl;
    cout<<"this program will create a file called unit.test"<<endl;
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
    double x,y;
    cout<<"km:";
    cin>>x;
    cout<<"seconds:";
    cin>>y;
    cout<<endl<<"DISTANCE:"<<endl;
    cout<<km.get_name()<<":"<<x<<endl;
    x=km.standard_unit_value(x);
    cout<<m.get_name()<<":"<<x<<"   (";
    out_science(x);
    cout<<")"<<endl;
    cout<<endl<<"TIME:"<<endl;
    cout<<s.get_name()<<":"<<y<<endl;
    y=h.value_from_standard_unit(y);
    cout<<h.get_name()<<":"<<y<<"   (";
    out_science(y);
    cout<<")"<<endl;
    cout<<endl<<"SPEED:"<<endl;
    unit speed;
    speed=km/h;
    x=km.value_from_standard_unit(x);
    x=x/y; //km/h
    cout<<"speed"<<":"<<x<<" "<<speed<<endl;
    x=speed.standard_unit_value(x);
    cout<<"standard speed(m/s):"<<x<<endl;
    ofstream out("unit.test");
    km.write_unit(out);
    m.write_unit(out);
    s.write_unit(out);
    h.write_unit(out); //writes the units
    out.close();
    /* cout<<"Units from file:"<<endl;
     ifstream input("unit.test");
     unit km2(input,2);
     unit m2(input,2);
     input.close(); //read the 2 first
     cout<<km2<<endl;
     cout<<m2;
     cout<<endl<<"km2==km: "<<(km==km2)<<endl;
     cout<<endl<<"km2==m2: "<<(km2==m2)<<endl;
     cout<<"is standard unit:"<<endl;
     cout<<"km:"<<(km.standard_unit())<<endl;
     cout<<"m:"<<(m.standard_unit())<<endl;
     cout<<"km/h:"<<(speed.standard_unit())<<endl;
     cout<<"m/s:"<<((m/s).standard_unit())<<endl;*/
    return 0;
}
