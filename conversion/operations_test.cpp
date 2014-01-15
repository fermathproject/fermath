/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project: Operations test
Version:0.6
*/

//This program tests the class operations

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
#include "include/templates.h"
#include "include/operations.h"

int main() {
    cout<<"Fermath Operations Test V0.6"<<endl;
    cout<<"This test will create a file called operations.test"<<endl;
    double x,y;
    operations op(1,100); //add 100
    op.add_operation(4,10); //divide for 10
    op.add_operation(2); //^2
    cout<<"Write a number:";
    cin>>x;
    y=op.operate(x);
    cout<<"Result:"<<y<<endl; //((x+100)/10)^2
    cout<<"Inverse result:"<<op.inverse_operate(x)<<endl; //(sqrt(x)*10)-100
    cout<<"Inverse result of operation (it hould be your number):"<<op.inverse_operate(y)<<endl; //x
    cout<<"op:"<<op<<endl; //show operations
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
    cout<<"operator test"<<endl;
    cout<<"op==op2 and op!=op2: ";
    cout<<(op==op2)<<" "<<(op!=op2)<<endl;
    op=op2;
    cout<<"op(after op=op2)"<<op<<endl;
    cout<<"op==op2 and op!=op2: "<<(op==op2)<<" "<<(op!=op2)<<endl;
    return 0;
}
