/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  
*/
/*
Fermath Project: entrada.h
Version:0.1
*/
#include <iostream>
#include <string>

using namespace std;

const char *  mostrar_cambiar (){
	string a;
	cout<<"Escribe una formula: ";
	//cin>>a;
	getline (cin,a);
	cout<<"la formula es : "<<a<<endl;;
	const char * cadena;
	cadena=a.c_str();
	return cadena;
}

