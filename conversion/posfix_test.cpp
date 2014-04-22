/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Posfix Test
Version:0.9.4

This program test units,magnitudes,operators and glossary
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <stack>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <map>
using namespace std;
#include "include/posfix.h"

int main() {
    cout<<"Fermath posfijo Test "<<endl;
    data_src database;
    //   const basic_unit_source *bsrc;
    //  bsrc=database.get_basic_source2();
    ifstream input("database.fermath");
    database.read(input);
    input.close();
    vector< string > Postfijo;
    string infijo("(1kg*(5)-(1T*5m))");
    Postfijo=convertirpostfijo(infijo,database);
    cout<<endl;
    return 0;
}
