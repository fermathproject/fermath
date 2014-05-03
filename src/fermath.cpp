/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca
*/
/*
Fermath Project: main
Version:1.1
*/

#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <stack>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <sstream>
using namespace std;
#include "include/expression.h"
#include "include/conversion.h"



int main(int argc, char **argv) {
    data_src database;
    ifstream input("database.fermath");
    database.read(input);
    input.close();
    if(argc>1) { //with arguments
        string in;
        for(int i=1; i<argc; i++) {
            string s(argv[i]);
            in=in+s;
        }
        cout<<calculate_expression(in,database)<<endl;
    }
    else { //interpreter mode
        cout<<"Fermath "<<version<<endl;
        string s;
        cout<<"Write your operation"<<endl;
        cout<<"Type exit to close Fermath"<<endl;
        cout<<">";
        cin>>s;
        while(s!="exit") {
            cout<<calculate_expression(s,database)<<endl;
            cout<<">";
            cin>>s;
        }
    }
    return 0;
}
