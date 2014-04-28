/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Data Source Test
Version:0.9.3

Interface for creating and modifiying the database (operators,unts and magnitudes)
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

void merge_database(string name,data_src &database); //merge another database from a document
vector<string> get_names(); //feedback with user to get names
//Each of the next functions has his own feedback with user to create/remove elements
unit_id add_basic_unit(magnitude_id mid,data_src &database);
unit_id add_unit(magnitude_id mid,data_src &database);
magnitude_id add_magnitude(data_src &database);
void add_operation(data_src &database);

bool add_name(const string &name,magnitude_id mid,data_src &database); //adds a name for a magnitude
bool add_name(const string &name,unit_id uid,data_src &database); //add a name for a unit

void remove_unit(unit_id uid,data_src &database);
//void remove_basic_unit(unit_id uid ,data_src &database);
void remove_magnitude(magnitude_id mid,data_src &database);
void remove_operation(const op &oper,data_src &database);


void remove_name(const string &name,magnitude_id mid,data_src &database);
void remove_name(const string &name,unit_id id,data_src &database);

void cls() { //clear_screen
    cout<<endl<<"-------------------------------"<<endl;
    // cout<<string(50,'\n');
}
void show_database(data_src dtbs) {
    cout<<endl<<"DATABASE:"<<endl;
    dtbs.show2();
}
unsigned int menu(vector<string> opt); //shows menu and returns selection

int main() {
    data_src database;
    ifstream input("database.fermath"); //reads database (if exists)
    if(input) database.read(input);
    input.close();
    cout<<"Fermath Database Creator "<<version<<endl;
    cout<<"Working with database.fermath"<<endl;
    cin.get();
    vector<string> opt; //options of menu
    opt.push_back("Add Operation");
    opt.push_back("Add Magnitude");
    opt.push_back("Add Basic Unit");
    opt.push_back("Add Unit");
    opt.push_back("Remove operation");
    opt.push_back("Remove unit");
    opt.push_back("Remove magnitude");
    opt.push_back("Show Database");
    opt.push_back("Save and Exit");
    cls();
    unsigned int cmd=0; //command selected
    while(cmd!=9) {
        string nam;
        magnitude_id current_mag;
        op oper;
        unit_id uid;
        magnitude_id mid;
        cout<<"Fermath Database Creator "<<version<<endl;
        cmd=menu(opt);
        switch(cmd) {
        case 1: //Add operation
            add_operation(database);
            break;
        case 2: //Add magnitude
            add_magnitude(database);
            break;
        case 3: //Add basic_unit
            cout<<"Enter Name of magnitude:";
            cin>>nam;
            current_mag=database.get_magnitude_id(nam);
            if(current_mag!=0) add_basic_unit(current_mag,database);
            break;
        case 4: //Add unit
            cout<<"Enter Name of magnitude:";
            cin>>nam;
            current_mag=database.get_magnitude_id(nam);
            if(current_mag!=0) add_unit(current_mag,database);
            break;
        case 5: //remove operator
            cout<<"Enter operator:";
            cin>>nam;
            oper=database.get_operator(nam);
            remove_operation(oper,database);
            break;
        case 6: //remove unit
            cout<<"Enter name of unit:";
            cin>>nam;
            uid=database.get_unit_id(nam);
            if(uid!=null_id) remove_unit(uid,database);
            break;
        case 7: //remove magnitude
            cout<<"Enter name of magnitude:";
            cin>>nam;
            mid=database.get_magnitude_id(nam);
            if(mid!=0) remove_magnitude(mid,database);
            break;
        case 8: //show database
            show_database(database);
            break;
        case 9: //exit
            break;
        }
        cls();
    }
    //Writes database into file
    ofstream out("database.fermath");
    database.write(out);
    out.close();
    return 0;
}

unsigned int menu(vector<string> opt) {
    unsigned int cmd;
    for(unsigned int i=0; i<opt.size(); i++) {
        cout<<i+1<<"-"<<opt[i]<<endl;
    }
    cin>>cmd;
    if(cmd>opt.size()) cmd=0;
    return cmd;
}






void merge_database(string name,data_src &database) {
    ifstream input(name.c_str()); //transform name into a c_string (char)
    if(!input) error_report(class_error," cant read file",1,1);
    else {
        data_src database2(input);
        input.close();
        database.merge(database2);
    }
}

vector<string> get_names() {
    unsigned int n_names;
    vector<string> v;
    string name2;
    cout<<"Number of extra names:";
    cin>>n_names;
    for(unsigned int i=0; i<n_names; i++) {
        cin>>name2;
        v.push_back(name2);
    }
    return v;
}

unit_id add_basic_unit(magnitude_id mid,data_src &database) {
    unit_id uid=null_id;
    string name;
    vector<string> v;
    unsigned int n_op;
    cout<<"Basic Unit Name (short):";
    cin>>name;
    cout<<"Number of operations for conversion:";
    cin>>n_op;
    basic_unit bunit(name);
    for(unsigned int i=0; i<n_op; i++) {
        op oper;
        string name_op;
        cout<<"Operation:";
        cin>>name_op;
        oper=database.get_operator(name_op);
        if(oper.is_unary()==true) bunit.add_operation(oper);
        else {
            conversion_data dataop;
            cout<<"Data of operation:";
            cin>>dataop;
            bunit.add_operation(oper,dataop);
        }
    }
    v=get_names();
    uid=database.add_unit(bunit,mid,v);
    return uid;
}

unit_id add_unit(magnitude_id mid,data_src &database) {
    unit result;
    unit_id id=null_id;
    int has_name;
    unsigned int a,b;
    string name;
    vector<string> v;
    cout<<"1-Add name\n2-Dont add name\n";
    cin>>has_name;
    if(has_name==1) {
        cout<<"Name of unit:";
        cin>>name;
        result.set_name(name);
    }
    cout<<"Number of units (a/b) (two numbers):";
    cin>>a>>b;
    for(unsigned int i=0; i<a; i++) {
        string name2;
        unit unit2;
        cout<<i<<"-";
        cin>>name2;
        unit2=database.get_unit(name2);
        result.add_unit(unit2);
    }
    for(unsigned int i=0; i<b; i++) {
        string name2;
        unit unit2;
        cout<<i<<"-";
        cin>>name2;
        unit2=database.get_unit(name2);
        result.add_inverse_unit(unit2);
    }
    v=get_names();
    id=database.add_unit(result,mid,v);
    return id;
}
magnitude_id add_magnitude(data_src &database) {
    magnitude_id mid;
    string n;
    vector<string> names;
    cout<<"Name of magnitude:";
    cin>>n;
    names=get_names();
    mid=database.add_magnitude(n,names);
    return mid;
}

void add_operation(data_src &database) {
    operation_id id;
    string name;
    bool bin;
    cout<<"Operation id:";
    cin>>id;
    cout<<"1-Binary operator\n2-Unary operator\n";
    cin>>bin;
    if(bin==1 && (id>binary_max || id<=0)) cout<<"ID out of range"<<endl;
    else if(bin==2 && (id>unary_max || id<=0)) cout<<"ID out of range"<<endl;
    else {
        cout<<"Name of operator:";
        cin>>name;
        database.add_operator(name,id,bin);
    }
}


void remove_unit(unit_id uid,data_src &database) {
    database.remove_unit(uid);
}
void remove_magnitude(magnitude_id mid,data_src &database) {
    database.remove_magnitude(mid);
}
void remove_operation(const op &oper,data_src &database) {
    database.remove_operator(oper);
}


