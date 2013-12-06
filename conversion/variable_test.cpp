/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Variable Test
Version:0.5
*/

//this program tests the variable class in the file variable.h
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
#include "include/variable.h"

int main() {
    cout<<"Fermath Variable Test V0.5"<<endl;
    cout<<"this program needs the file magnitude.test"<<endl;
    ifstream in("magnitude.test");
    magnitude mass(in,1);
    in.close();
    unit *uni;
    uni=mass.search_by_name("kg");
    variable var(10,uni); //10 kilograms
    uni=mass.search_by_name("g");
    variable var2(105,uni);
    cout<<var<<"+"<<var2<<"="<<(var+var2)<<endl;
    cout<<var<<"-"<<var2<<"="<<(var-var2)<<endl;
    cout<<"var1==var2:"<<(var==var2)<<endl;
    cout<<"var1!=var2:"<<(var!=var2)<<endl;
    return 0;
}
