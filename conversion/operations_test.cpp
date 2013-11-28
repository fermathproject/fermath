/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project: Operations test
Version:0.3
*/

//This program tests the class operations

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#include "math_functions.h"
#include "operations.h"

int main() {
    double x,y;
    operations op(1,100); //add 100
    op.add_operation(4,10); //divide for 10
    op.add_operation(2); //^2
    cin>>x;
    y=op.operate(x);
    cout<<"resultado:"<<y<<endl; //((x+100)/10)^2
    cout<<"resultado inverso:"<<op.inverse_operate(x)<<endl; //(sqrt(x)*10)-100
    cout<<"invirtiendo primera operacion:"<<op.inverse_operate(y)<<endl; //x
    cout<<op; //show operations
    op.remove_operation(2);//remove the last operation
    op.remove_operation(1);//remove the second operation
    cout<<op; //show operations (only the first operation)
    return 0;
}
