/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Test
Version:0.8

This program test the magnitude.h methods
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <set>
using namespace std;
#include "include/magnitude.h"

int main() {
    cout<<"Fermath Magnitude Test "<<version<<endl;
    cout<<"This program will create a file called magnitude.test and need the file unit.test"<<endl;
    /*ifstream input("unit.test");
    unit uni(input); //m
    magnitude dist("distance","D",1,uni);
    uni.read_unit(input);//km
    dist.add_unit(uni);

    uni.read_unit(input);//s
    magnitude time("time","T",2,uni);
    uni.read_unit(input);//h
     time.add_unit(uni);
    input.close();

    cout<<"Magnitudes created from unit.test units:"<<endl;
    cout<<dist<<endl;
    cout<<time<<endl;
    cout<<"searching for testkm"<<endl;
    unit x;
    x=dist.search_by_name("m");
    x.show_unit();
    cout<<"is testkm in dis: "<<(dist.is_unit("testkm"))<<endl;

    ofstream out("magnitude.test");
    dist.write_magnitude(out);
    time.write_magnitude(out);
    out.close();

    /*
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
    cout<<mass<<endl;*/
    return 0;
}
