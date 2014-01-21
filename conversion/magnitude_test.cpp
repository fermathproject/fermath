/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Functions Test
Version:0.7

This program test the functions.h methods
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
#include "include/magnitude.h"

int main() {
    //int id=0;
    cout<<"Fermath Magnitude Test "<<version<<endl;
    cout<<"This program will create a file called magnitude.test and need the file unit.test"<<endl;
    ifstream input("unit.test");
    unit uni(input); //kg
    magnitude mass("mass","M",1,uni);
    uni.read_unit(input);//g
    mass.add_unit(uni);
    uni.read_unit(input);//tons
    mass.add_unit(uni);
    input.close();
    cout<<"Magnitude created from unit.test units:"<<endl;
    cout<<mass;
    cout<<"searching for gramillo"<<endl;
    unit x;
    x=mass.search_by_name("gramillo");
    cout<<x;
    ofstream out("magnitude.test");
    mass.write_magnitude(out);
    out.close();
    ifstream in("magnitude.test");
    magnitude mass2(in,1);
    in.close();
    cout<<endl<<"----------"<<endl;
    cout<<mass2;
    mass.add_unit(uni);
    cout<<"mass2==mass:"<<(mass2==mass)<<endl;
    cout<<"mass2!=mass:"<<(mass2!=mass)<<endl;
    cout<<"mass+mass2:"<<endl;
    mass=mass+mass2;
    cout<<mass<<endl;
    return 0;
}
