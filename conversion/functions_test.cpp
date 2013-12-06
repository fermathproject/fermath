/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Functions Test
Version:0.5

This program test the functions.h methods
*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#include "include/functions.h"


int main() {
    cout<<"Fermath Function Test V0.4";
    float x=80,y=34;
    for(int i=0; i<4; i++) {
        x=x*x; //x is a big number
    }
    cout<<endl<<x<<endl; //ugly output
    out_science(x); //nice science output
    x=18;
    cout<<endl<<"mcm(18,34):"<<mcm(x,y)<<endl;
    cout<<"mcd(18,34):"<<mcd(x,y)<<endl;
    cout<<"First 10 prime numbers:";
    int p=0;
    for(int i=0; i<10; i++) {
        p=next_prime(p);
        cout<<p<<" ";
    }
    cout<<endl<<"Prime number 1000:"<<prime(1000)<<endl;
    int z=48;
    cout<<"prime descomposition of "<<z<<":";
    vector<int> v;
    v=prime_descomposition(z);
    for(int i=0; i<v.size(); i++) cout<<v[i]<<" ";
    cout<<endl;
    return 0;
}
