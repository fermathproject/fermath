/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project: Unit test
Version:0.3
*/

//This program tests the class unit

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#include "math_functions.h"
#include "operations.h"
#include "unit.h"

main() {
    operations conv;
    int id=0;
    unit kg(string("kilogramos"),string("kg"),id++,conv); //standard unit of magnitude
    conv.add_operation(4,1000);
    unit g(string("gramos"),string("g"),id++,conv);
    conv.clear();
    conv.add_operation(3,1000);
    unit tonelada(string("tonelada"),string("T"),id++,conv);
    double x;
    cin>>x;
    x=tonelada.standard_unit_value(x); //turns T into kg;
    cout<<kg.get_name()<<":"<<x<<endl;
    x=g.value_from_standard_unit(x); //turns kg into g;
    cout<<g.get_name()<<":"<<x<<"  (";
    out_science(x);
    cout<<")"<<endl;
    x=tonelada.convert_from(x,g);   //turns g into T
    cout<<tonelada.get_name()<<":"<<x<<endl;
    return 0;
}
