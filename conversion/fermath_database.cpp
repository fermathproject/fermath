/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Data Source Test
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
#include "include/data_source.h"


/*README:
 * The file database.dev needed has the next structure:
 * number of magnitudes (int)
 * principal name of  magnitude - number of seconddary names - vector<string> secondary names
 *  bool basic (1 if the units of magnitude are basic (g,kg,m..) 0 if complex (m/s,Newtons) - number of units in magnitude
 * (if the unit is basic:)
 * principal name of unit  - number of secondary names - vector<string> secondary names
 *  operation id - data id (0,0 if there is no conversion) (op_id: 1+,2-,3*,4/)
 * (if the unit is complex:)
 *principal name of unit - number of secondary names - vector<string> secondary name
 * number of basic units in numerator - vector<string>  (name of unit (doesnt matter if principal name or secondary name or complex/basic, but it has to be previously declared))
 * number of basic units in denominator - vector<string>
 */

unit_id input_basic_unit(ifstream &input,magnitude_id mid,data_src &database);
magnitude_id input_magnitude(ifstream &input,data_src &database);
unit_id input_unit(ifstream &input,magnitude_id mid,data_src &database);

int main() {
    cout<<"Fermath Database Test "<<version<<endl;
    cout<<"This program will create a file called database.fermath and need the file database.dev"<<endl;
    op add(1,binary_operator);
    op sub(2,binary_operator);
    op mul(3,binary_operator);
    op div(4,binary_operator); //operators
    data_src database;
    ifstream input("database.dev");
    int n_mag=0;
    input>>n_mag; //number of magnitudes
    for(int i=0; i<n_mag; i++) {
        magnitude_id mid;
        bool basic; //if units are basic
        int n_units; //number of units in magnitude
        mid=input_magnitude(input,database); //read one magnitude
        input>>basic>>n_units;
        for(int j=0; j<n_units; j++) {
            if(basic==false) {
                input_unit(input,mid,database);
            }
            else {
                input_basic_unit(input,mid,database);
            }
        }
    }
    input.close();
    cout<<endl<<"DATABASE:"<<endl;
    database.show();
    ofstream out("database.fermath");
    database.write(out);
    out.close();
    return 0;
}


unit_id input_unit(ifstream &input,magnitude_id mid,data_src &database) {
    string s;
    vector<string> v;
    int n_names;
    input>>s;
    unit u(s); //unit with name s
    input>>n_names;
    for(int i=0; i<n_names; i++) {
        input>>s;
        v.push_back(s);
    }
    int n_bunit;
    input>>n_bunit;
    for(int i=0; i<n_bunit; i++) { //numerators
        input>>s; //name of basic_unit
        unit u2= database.get_unit(s) ;
        u.add_unit(u2); //adds us to u
    }
    input>>n_bunit;
    for(int i=0; i<n_bunit; i++) { //denominators
        input>>s; //name of basic_unit
        unit u2= database.get_unit(s) ;
        u.add_inverse_unit(u2); //adds us to u
    }
    return  database.add_unit(u,mid,v);
}



unit_id input_basic_unit(ifstream &input,magnitude_id mid,data_src &database) {
    string s;
    vector<string> v;
    string s2;
    int n_names;
    input>>s; //name of unit
    input>>n_names; //number of names
    for(int i=0; i<n_names; i++) {
        input>>s2;
        v.push_back(s2);
    }
    basic_unit bunit(s);
    int opid,data;
    input>>opid>>data; //conversion of basic unit
    if(opid!=0 && data!=0) {
        op oper(opid,binary_operator);
        bunit.add_operation(oper,data);
    }
    return  database.add_unit(bunit,mid,v);
}


magnitude_id input_magnitude(ifstream &input,data_src &database) {
    string n;
    string s2;
    vector<string> s;
    int number;
    input>>n;
    input>>number;
    for(int i=0; i<number; i++) {
        input>>s2;
        s.push_back(s2);
    }
    return database.add_magnitude(n,s);
}



