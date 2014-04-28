/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Conversion
Version:0.9.6
*/
#include "posfix.h"

string calculate_expression(const string &s,const data_src &database) {
    expression expr=convertirpostfijo(s,database);
    variable var=expr.evaluate(database);
    ostringstream stream; //ostream to string
    var.show(database,stream);
    string str=stream.str();
    return str;
}
