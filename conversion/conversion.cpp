/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
This Program test some of the different classes oriented to convert between units, which will be included in the Fermath Project
Version:0.3
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;
#include "math_functions.h"
#include "operations.h"
#include "unit.h"
#include "magnitude.h"
#include "variable.h"

float version=0.2;
main() {
    int id=0;
    operations conv;
    unit kg(string("kilogramos"),string("g"),id++,conv);
    conv.add_operation(4,1000);
    unit g(string("gramos"),string("g"),id++,conv);
    conv.clear();
    conv.add_operation(3,1000);
    unit tonelada(string("tonelada"),string("T"),id++,conv);
    double n;
    cout<<"Fermath Conversion Test\n";
    cout<<"Version:"<<version<<endl;
    cout<<"Number of Tons:";
    cin>>n;
    n=tonelada.standard_unit_value(n);
    cout<<n<<" Kg"<<endl;
    n=g.value_from_standard_unit(n);
    out_science(n);
    cout<<" g"<<endl;
    return 0;
}

