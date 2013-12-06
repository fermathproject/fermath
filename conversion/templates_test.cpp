/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */

/*
Fermath Project:Conversion Templates test
Version:0.5
*/

//This Program tests the templates of templates.h writing and reading vectors from a file

#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
#include"include/templates.h"


int main() {
    cout<<"Fermath Templates Test V0.5"<<endl;
    cout<<"this program will create a file called template.test"<<endl;
    vector<char> v;
    vector<int> v2;
    vector<string> v3;
    v.push_back('a');
    v.push_back('b');
    v.push_back('f');//v={a,b,f}
    v2.push_back(1);
    v2.push_back(19);
    v2.push_back(29);
    v2.push_back(-8);//v={1,19,29,-8}
    v3.push_back("Glados");
    v3.push_back("is");
    v3.push_back("testing");//v={Glados,is,testing}
    cout<<"Vectors to write:"<<endl;
    write_vector(v);
    cout<<endl;
    write_vector(v2);
    cout<<endl;
    write_vector(v3);//show vector on standard output
    cout<<endl;
    ofstream out("template.test");
    binary_write_vector(v,out);
    binary_write_vector(v2,out);
    binary_write_vector(v3,out); //writes vectors
    out.close();
    vector<char> vout;
    vector<int> vout2;
    vector<string> vout3;
    ifstream input("template.test");
    binary_read_vector(vout,input);
    binary_read_vector(vout2,input);
    binary_read_vector(vout3,input); //reads vectors
    input.close();
    v.clear();
    v2.clear();
    v3.clear(); //clears original vectors (if the copied vectors are just pointers, they will fail)
    cout<<"Readed vectors:"<<endl;
    write_vector(vout);
    cout<<endl;
    write_vector(vout2);
    cout<<endl;
    write_vector(vout3);//show vectors
    cout<<endl;
    vector<int> v4;
    v4.push_back(4);
    v4.push_back(29); //v4={4,29}
    add_vector(v4,vout2);
    cout<<"v4+v2"<<endl;
    write_vector(v4);
    cout<<endl;
    return 0;
}
