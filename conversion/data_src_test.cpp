/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Data Source Test
Version:0.9

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
using namespace std;
#include "include/data_source.h"

int main() {
    cout<<"Fermath Database Test "<<version<<endl;
    cout<<"This program will create a file called magnitude.test and need the file unit.test"<<endl;
    op add(1,binary_operator);
    op sub(2,binary_operator);
    op mul(3,binary_operator);
    op div(4,binary_operator); //operators
    data_src database;
    int selec=0;
    while(selec<4) {
        cout<<"Selec an option\n";
        cout<<"1-Add basic unit\n";
        cout<<"2-Add Magnitude\n";
        cout<<"3-Add Complex Unit\n";
        cin>>selec;
        if(selec==1) {
            magnitude_id mid=0;
            operation_id opid;
            string n;
            cout<<"Write the name of magnitude:";
            cin>>n;
            mid=database.get_magnitude_id(n);
            if(mid==0) cout<<"magnitude not found\n";
            else {
                cout<<"name of unit:";
                cin>>s;
                cout<<"selec operation (0null,1+,2-,3*,4/):";
                cin>>opid;
                basic_unit bunit(s);
                if(opid<=0) {
                    op oper(opid,binary_operator);
                    conversion_data dc;
                    cout<<"conversion data:";
                    cin>>dc;
                    bunit.add_operation(opid,dc);
                }
            }
        }
        if(selec==2) {
            string n;
            unsigned int nn;
            vector<string> magnames;
            cout<<"Name of magnitude:";
            cin>>n;
            cout<<"Number of names:";
            cin>>nn;
            for(int i=0; i<nn; i++) {
                string s;
                cout<<"name "<<i<<":";
                cin>>s;
                magnames.push_back(s);
            }
            database.add_magnitude(n,nn);
        }
        if(selec==3) {
            magnitude_id mid=0;
            string n;
            cout<<"Write the name of magnitude:";
            cin>>n;
            mid=database.get_magnitude_id(n);
            if(mid==0) cout<<"magnitude not found\n";
            else {
                string s;
                cout<<"name of unit(not necessary):";
                cin>>s;
                complex_unit cu(s);
                unit_id uid;
                clear(uid);
                unsigned int densize,numsize;
                cout<<"Write numer of units in den and num:";
                cin>>densize>>numsize;
                for(int i=0; i<numsize; i++) {
                    cout<<"enter unit "<<i<<" of numerator:";
                    cin>>n;
                    uid=database.get_unit_id(n);
                    if(is_null(uid)==false) {
                        i--;
                        cout<<"Error,unit not found\n";
                    }
                    else {
                        cu.add_unit(database.get_unit(uid));
                    }
                }
                for(int i=0; i<densize; i++) {
                    cout<<"enter unit "<<i<<" of denominator:";
                    cin>>n;
                    uid=database.get_unit_id(n);
                    if(is_null(uid)==false) {
                        i--;
                        cout<<"Error,unit not found\n";
                    }
                    else {
                        cu.add_inverse_unit(database.get_unit(uid);
                    }
                }
                unsigned int nn;
                cout<<"number of names of magnitude:";
                cin<<nn;
                vector<string> unames;
                for(int i=0; i<nn; i++) {
                    cin>>s;
                    unames.push_back(s);
                }
                uid=database.add_unit(cu,magid,unames);
            }
        }
    }
    ofstream out("database.test");
    database.write(out);
    out.close();
    return 0;
}
