/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project: Operators test
Version:0.8
*/

//This program tests the class operations

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;
#include "include/operator.h"

int main() {
    cout<<"Fermath Operations Test "<<version<<endl;
    cout<<"This test will create a file called operator.test"<<endl;
    op operator1("+",1,binary_operator);
    op operator2("-",2,binary_operator);
    op operator3("sen",1,unary_operator);
    cout<<operator1<<endl<<operator2<<endl<<operator3<<endl;
    cout<<operator1.get_id()<<"-->"<<operator1.get_inverse_id()<<endl;
    op operator4;
    operator4=operator1;
    cout<<"op1==op2  "<<(operator1==operator4)<<endl;
    cout<<"op1==+   "<<(operator1=="+")<<endl;
    ofstream out("operator.test");
    operator1.write_operator(out);
    operator2.write_operator(out);
    out.close();
    ifstream input("operator.test");
    op aux1(input);
    op aux2(input);
    input.close();
    cout<<endl<<"readed from file:"<<endl<<aux1<<endl<<aux2<<endl;
    return 0;
}
