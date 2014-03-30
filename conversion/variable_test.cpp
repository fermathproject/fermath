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
    ifstream input("database.fermath");
    database.read(input);
    input.close();
    database.show();
    return 0;
}
