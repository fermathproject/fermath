/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:initSET
Version:3
*/

#include<stdio.h>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include "operator_list.h"



using namespace std;
//crea el conjunto de operadores a partir de una lista determinada.
op_list crear_op_list(){
		//creamos el op_list

	op_list v;
    op a("+",1,binary_operator);
    v.add_operator(a);
    a.set("-",2,binary_operator);
    v.add_operator(a);
    a.set("*",3,binary_operator);
    v.add_operator(a);
    a.set("/",4,binary_operator);
    v.add_operator(a);
    a.set("^",5,binary_operator);
    v.add_operator(a);
	a.set("raiz",6,binary_operator);
    v.add_operator(a);
    a.set("sqrt",1,unary_operator);
    v.add_operator(a);
	a.set("^2",2,unary_operator);
    v.add_operator(a);
	a.set("sen",3,unary_operator);
    v.add_operator(a);
	a.set("arcosen",4,unary_operator);
    v.add_operator(a);
    a.set("cos",5,unary_operator);
    v.add_operator(a);
	a.set("arcocos",6,unary_operator);
    v.add_operator(a);
    a.set("tan",7,unary_operator);
    v.add_operator(a);
	a.set("arcotan",8,unary_operator);
    v.add_operator(a);
	a.set("e^",9,unary_operator);
    v.add_operator(a);
	a.set("log",9,unary_operator);
    v.add_operator(a);
	//creamos el op_list

	return v;


}
//escribe la base de datos en un archivo binario
void crear_basedatos_operadores(const op_list & v,ofstream &out) {//crea un op_list y lo escribe en un archivo
    v.write_setoperator(out);
}
//muestra todos los operadores (salida detallada)
void mostrar_operator(const op_list & v){
	cout<<"mostramos los operadores\n";
	set<op>::iterator it;
	for(it=v.begin();it!=v.end();++it){
		(*it).show_operator();
	}

}
//añade un operador del conjunto
void insert_operator(op_list & v){
	//unary_operator 0
	//binary_operator 1	
	cout<<"añadimos\n";
	string auxs;
	int auxid,unarybinary;
	cout<<"introduce string operador\n";
	cin>>auxs;
	cout<<"introduce id operador\n";
	cin>>auxid;
	cout<<"introduce 1=binary o 2=unary\n";
	cin>>unarybinary;
    op a(auxs,auxid,unarybinary);
    v.add_operator(a);
}
//elimina un operador del conjunto
void remove_operator(op_list & v){	
	//unary_operator 0
	//binary_operator 1	
	cout<<"eliminamos\n";
	string auxs;
	int auxid,unarybinary;
	cout<<"introduce string operador\n";
	cin>>auxs;
	cout<<"introduce id operador\n";
	cin>>auxid;
	cout<<"introduce 1=binary o 2=unary\n";
	cin>>unarybinary;
    op a(auxs,auxid,unarybinary);
    v.remove_operator(a);

}

//para administrar el set. Añade o elimina operadores del conjunto.
void menu(op_list & v){	
	bool seguir=true;
	string aux;
	while(seguir){
		cout<<"si quieres añadir un elemento escribe \"insert\".\nSi quieres eliminar un elemento escribe \"remove\".\n";
		cout<<"Si quieres salir escribe \"exit\".\n";
		cin>>aux;
			
		if(aux=="insert")
             insert_operator(v);
        else{
			if	(aux=="remove")
            	remove_operator(v);
            if(aux=="exit")
            	seguir=false;
        }
	}
}

main() {//creamos el conjunto, accedemos al menu, escribimos el conjunto en un archivo binario "op.fermath"
	op_list v;
	v=crear_op_list();
	menu(v);
	ofstream out("op.fermath");
	crear_basedatos_operadores(v,out);
	out.close();
	mostrar_operator(v);
	 
    return 0;
}
