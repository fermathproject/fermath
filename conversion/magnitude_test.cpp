/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Functions Test
Version:0.4

This program test the functions.h methods
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
#include "include/templates.h"
#include "include/operations.h"
#include "include/unit.h"
#include "include/magnitude.h"

int main() {
    cout<<"Fermath Function Test V0.4"<<endl;
    cout<<"This program will create a file called magnitude.test and need the file unit.test"<<endl;
    ifstream input("unit.test");
    int unitid=1;
    unit uni(input,1,unitid++); //kg
    magnitude mass("mass","M",1,uni);
    uni.read_unit(input,unitid++);//g
    mass.add_unit(uni);
    uni.read_unit(input,unitid++);//tons
    mass.add_unit(uni);
    input.close();
    cout<<"Magnitud Created from unit.test units:"<<endl;
    cout<<mass;
    cout<<"searching for gramillo"<<endl;
    unit x;
    x=mass.search_by_name("gramillo");
    cout<<x;
    ofstream out("magnitude.test");
    mass.write_magnitude(out);
    out.close();
    ifstream in("magnitude.test");
    magnitude mass2(in,2);
    in.close();
    cout<<endl<<"----------"<<endl;
    cout<<mass2;
    return 0;
}
