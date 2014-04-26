/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Expression Test
Version:0.9.4

This program test expressions
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include <set>
#include <stack>
using namespace std;
#include "include/expression.h"


int main() {
    cout<<"Fermath Expression Test "<<version<<endl;
    data_src database;
    const basic_unit_source *bsrc;
    bsrc=database.get_basic_source2();
    ifstream input("database.fermath");
    database.read(input);
    input.close();
    expression expr;
    string s="kg";
    variable var;
    //5*(6+4)=50 --> 5 6 4 + *
    var.set_value(5);
    var.set_unit(database.get_unit(s));
    expr.add_variable(var);
    var.set_value(6);
    expr.add_variable(var);
    var.set_value(4);
    expr.add_variable(var);
    op oper;
    oper=database.get_operator("+");
    expr.add_operation(oper);
    oper=database.get_operator("*");
    expr.add_operation(oper);
    var=expr.evaluate(database);
    var.show(*bsrc);
    cout<<endl;
    return 0;
}