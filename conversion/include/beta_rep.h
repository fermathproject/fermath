/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Beta Version Reports
Version:0.9.4
*/

typedef unsigned short error_id;
const bool hide_assert=false;
const bool hide_write=true;
const bool hide_show=false; //true to hide errors

const bool force_assert=false;
const bool force_write=false;
const bool force_show=true; //true to force errors(indepent of hide value)



bool show_contact_message=false;
const string version="V0.9.4";
const error_id correct_check=0,warning_check=1,error_check=2,user_error=3,class_error=4,fatal_error=5;
#define error_file "fermath.error"


void error_report(error_id id,string error,bool write,bool show,bool assert=false) {
    string error_msg="Report:";
    if(id==1) error_msg="WARNING:";
    else if(id==2) error_msg="ERROR:";
    else if(id==3) error_msg="ERROR,bad use:";
    else if(id==4) error_msg="CLASS ERROR:";
    else if(id==5) error_msg="FATAL_ERROR:";
    else if(id==0) error_msg="Correct check,";
    if((write==true && hide_write==false) || force_write==true) { //Write
        ofstream out;
        out.open(error_file,ios::app);
        out<<version<<"::"<<error_msg<<error<<endl;
        out<<"---id:"<<id<<endl;
        out.close();
    }
    if((show==true && hide_show==false) || force_show==true) {//Show
        cout<<error_msg<<error<<endl;
        cout<<"id:"<<id<<endl;
        if(show_contact_message==true) cout<<"Please, contact support"<<endl;
    }
    if((assert==true && hide_assert==false) || force_assert==true) {//asert
        exit(1);
    }
}

/*void error_report(error_id id,bool write,bool show,bool assert=false) {
    string error_msg="Report:";
    string error="No message";
    if(id==1) error_msg="WARNING:";
    else if(id==2) error_msg="ERROR:";
    else if(id==3) error_msg="ERROR,bad use:";
    else if(id==4) error_msg="CLASS ERROR:";
    else if(id==5) error_msg="FATAL_ERROR:";
    else if(id==0) error_msg="Correct check,";
    if((write==true && hide_write==false) || force_write==true) {
        ofstream out;
        out.open(error_file, ios::app);
        out<<version<<"::"<<error_msg<<error<<endl;
        out<<"--ID:"<<id<<endl;
        out.close();
    }
    if((show==true && hide_show==false) || force_show==true) {
        cout<<error_msg<<"  id:"<<id<<endl;
        if(show_contact_message==true) cout<<"Please, contact support"<<endl;
    }
    if((assert==true && hide_assert==false) || force_assert==true) {
        exit(1);
    }
}*/

void error_report(string error,bool write,bool show,bool assert=false) {
    if((write==true && hide_write==false) || force_write==true) {
        ofstream out;
        out.open(error_file, ios::app);
        out<<version<<"::"<<"Report:"<<error<<endl;
        out.close();
    }
    if((show==true && hide_show==false) || force_show==true) {
        cout<<"Report:"<<error<<endl;
        if(show_contact_message==true) cout<<"Please, contact support"<<endl;
    }
    if((assert==true && hide_assert==false) || force_assert==true) {
        exit(1);
    }
}
