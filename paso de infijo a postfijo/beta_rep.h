/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:check_rep
Version:3
*/
#include <stdlib.h> 
using namespace std;
typedef unsigned short error_id;
const bool hide_assert=false;
const bool hide_write=false;
const bool hide_show=false; //true to hide errors

const bool force_assert=false;
const bool force_write=false;
const bool force_show=true; //true to force errors(indepent of hide value)



bool show_contact_message=false;
const string version="V0.7";
const error_id correct_check=0,warning_check=1,error_check=2,user_error=3,class_error=4,fatal_error=5;
#define error_file "fermath.error"


void error_report(error_id id,string error,bool write,bool show,bool assert=false) {
    if((write==true && hide_write==false) || force_write==true) {
        ofstream out;
        out.open(error_file,ios::app);
        out<<version<<"::"<<"ERROR:"<<error<<endl;
        out<<"---id:"<<id<<"     "<<version<<endl;
        out.close();
    }
    if((show==true && hide_show==false) || force_show==true) {
        cout<<"ERROR:"<<error<<endl;
        cout<<"id:"<<id<<endl;
        if(show_contact_message==true) cout<<"Please, contact support"<<endl;
    }
    if((assert==true && hide_assert==false) || force_assert==true) {
        exit(1);
    }
}

void error_report(error_id id,bool write,bool show,bool assert=false) {
    if((write==true && hide_write==false) || force_write==true) {
        ofstream out;
        out.open(error_file, ios::app);
        out<<version<<"::"<<"Error id:"<<endl;
        out.close();
    }
    if((show==true && hide_show==false) || force_show==true) {
        cout<<"Error id:"<<id<<endl;
        if(show_contact_message==true) cout<<"Please, contact support"<<endl;
    }
    if((assert==true && hide_assert==false) || force_assert==true) {
        exit(1);
    }
}

void error_report(string error,bool write,bool show,bool assert=false) {
    if((write==true && hide_write==false) || force_write==true) {
        ofstream out;
        out.open(error_file, ios::app);
        out<<version<<"::"<<"Error:"<<error<<endl;
        out.close();
    }
    if((show==true && hide_show==false) || force_show==true) {
        cout<<"Error:"<<error<<endl;
        if(show_contact_message==true) cout<<"Please, contact support"<<endl;
    }
    if((assert==true && hide_assert==false) || force_assert==true) {
        exit(1);
    }
}
