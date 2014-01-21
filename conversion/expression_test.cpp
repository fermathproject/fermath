/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Expression Test
Version:0.7

This program test the expresion.h methods
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
#include <stdlib.h>
using namespace std;
#include "include/magnitude.h"
#include "include/expression.h"


int main() {
    cout<<"Fermath Expression Test V0.7"<<endl;
    cout<<"this program needs the file magnitude.test"<<endl;
    ifstream in("magnitude.test");
    magnitude mass(in,1);
    in.close();
    unit uni;
    uni=mass.search_by_name("kg");
    variable var1(10,uni); //10 kilograms
    uni=mass.search_by_name("g");
    variable var2(2);
    variable var3(48,uni);//48 grams
    cout<<var1<<endl<<var2<<endl<<var3<<endl;
    cout<<"----------"<<endl;
    expression exp;
    exp.add_operation(1);
    exp.add_data(var3);
    exp.add_operation(3);
    exp.add_data(var2);
    exp.add_data(var1);
    cout<<exp<<endl;
    variable var4;
    var4=exp.solve_expression();
    //cout<<var1*var2<<endl;
    cout<<"(var1*var2)+var3="<<var4<<endl;
    //var1 var2 * var3 +
    return 0;
}
