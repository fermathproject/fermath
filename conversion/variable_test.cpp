/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Variable Test
Version:0.9.2

This program test units,magnitudes,operators and glossary
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
#include "include/variable.h"

int main() {
    cout<<"Fermath Variable Test "<<version<<endl;
    data_src database;
    const basic_unit_source *bsrc;
    bsrc=database.get_basic_source2();
    ifstream input("database.fermath");
    database.read(input);
    input.close();
    data_type n1,n2;
    string s1,s2;
    variable x,y;
    variable res;
    cout<<"variable x:";
    cin>>n1>>s1;
    cout<<"variable y:";
    cin>>n2>>s2;
    x.set_unit(database.get_unit(s1));
    x.set_value(n1);
    y.set_unit(database.get_unit(s2));
    y.set_value(n2);
    x.show(*bsrc);
    cout<<"+";
    y.show(*bsrc);
    cout<<"=";
    (x.add(y,database)).show(*bsrc);
    cout<<endl;
    x.show(*bsrc);
    cout<<"-";
    y.show(*bsrc);
    cout<<"=";
    (x.deduct(y,database)).show(*bsrc);
    cout<<endl;
    x.show(*bsrc);
    cout<<"*";
    y.show(*bsrc);
    cout<<"=";
    (x.multiply(y,database)).show(*bsrc);
    cout<<endl;
    x.show(*bsrc);
    cout<<"/";
    y.show(*bsrc);
    cout<<"=";
    res=x.divide(y,database);
    res.show(*bsrc);
    cout<<endl;
    res.set_variable_to_standard(database);
    cout<<"standard unit:";
    res.show(*bsrc);
    cout<<endl;
    return 0;
}
