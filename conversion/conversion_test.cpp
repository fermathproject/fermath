/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project: Conversion test
Version:0.8
*/

//This program tests the class operations

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;
#include "include/conversion.h"

int main() {
    cout<<"Fermath Operations Test "<<version<<endl;
    cout<<"This test will create a file called operations.test"<<endl;
    double x,y;
    op add("+",1,binary_operator),div("/",4,binary_operator),duplicate("^2",2,unary_operator);
    conversion conv(add,100); //add 100
    conv.add_operation(div,10); //divide for 10
    conv.add_operation(duplicate); //^2
    cout<<"Write a number:";
    cin>>x;
    y=conv.operate(x);
    cout<<conv<<endl<<y<<endl;
    //cout<<"Result((x+100)/10)^2:"<<y<<endl; //((x+100)/10)^2
    cout<<"Inverse result(sqrt(x)*10)-100:"<<conv.inverse_operate(x)<<endl; //(sqrt(x)*10)-100
    cout<<"Inverse result of operation (it should be your number):"<<conv.inverse_operate(y)<<endl; //x
    /* cout<<endl<<"op:"<<op<<endl; //show operations
     ofstream out("operation.test");
     op.write_operations(out); //writes operations in binary file
     out.close();
     op.remove_operation(2);//remove the last operation
     op.remove_operation(1);//remove the second operation
     cout<<"op(after remove):"<<op<<endl; //show operations (only the first operation)
     ifstream input("operation.test");
     operations op2(input); //read operation from binary file (3 operations)
     input.close();
     cout<<"op2(readed):"<<op2<<endl;//show operations
     cout<<endl<<"operator test"<<endl;
     cout<<"op==op2 and op!=op2: ";
     cout<<(op==op2)<<" "<<(op!=op2)<<endl;
     op=op2;
     cout<<"op(after op=op2)"<<op<<endl;
     cout<<"op==op2 and op!=op2: "<<(op==op2)<<" "<<(op!=op2)<<endl;*/
    return 0;
}
