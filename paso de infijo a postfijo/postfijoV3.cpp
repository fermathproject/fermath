// *************************************************************************************** //
// VERSION 2. POSTFIJO.
// 
// Este porgrama se encarga de tomar un string con la fomurmula, la cual puede tener:
// numeros,variables,operadores y parentesis.
//
// Tenemos una pequeña base de datos con operadores, la cual es una nueva clase.
// 
//La clase operador esta formada por un string, un bool y un idnetificador
//
// El progrma se encarga de crear un vector de string y ordenarlos en formato postfijo,
// el cual es ma facil de trabajar en una pila.
//
//Fermath Project: Operator (op)
// (C) Programmed by:
// Antonio Jimenez Martínez
// Andrés Ortiz Corrales
// Mariano Palomo Villafranca
// *************************************************************************************** //

#include<stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
//#include <sstream>//para el castg
#include "operator.h"
//cp contadorpostfijo
//ci contadorinfijo
using namespace std;

bool operador(const string & a,const vector<op> & b)
{
    for(int i=0; i<b.size(); i++) {
        if((b.at(i))==a) return true;
    }
    return false;
}

int comprobaroperador(const string & a,const vector<op> & b)
{
    int pos;
    for(int i=0; i<b.size(); i++) {
        if((pos=a.find((b.at(i)).get_text()))!=-1) return pos;
    }
    if((pos=a.find(")"))!=-1) return pos;
    if((pos=a.find("("))!=-1) return pos;
    return -1;
}
bool parentesis(const char & a)//comprobar si no es un operando
{
    return  a==')' || a=='(' ;
}
void mostrar(const vector<string> & a)
{
    for(int i=0; i<a.size(); ++i) {
        cout<<a[i]<<"  ";
    }
    cout<<endl;
}
vector<op> cargarvector() {
    vector<op> v;
    op a("/",1,binary_operator);
    v.push_back(a);
    a.set("*",2,binary_operator);
    v.push_back(a);
    a.set("+",3,binary_operator);
    v.push_back(a);
    a.set("-",4,binary_operator);
    v.push_back(a);
    a.set("sqrt",5,unary_operator);
    v.push_back(a);
    a.set("sen",6,unary_operator);
    v.push_back(a);
    a.set("cos",7,unary_operator);
    v.push_back(a);
    a.set("sqrt",8,unary_operator);
    v.push_back(a);
    return v;
}

vector<string> convertir(const string & infijo) {//convierte en un vector de string
    vector<op>vop=cargarvector();
    int tama=infijo.size();
    string aux("#");//este string se coloca delante de los operadores
    vector< string > a;
    string b,aux2;
    int i=0,pos,inicio;
    while(i<tama) {
        inicio=i;
        if(parentesis(infijo[i])) { //si es un parentesis lo mete.
            b=infijo[i];
            ++i;
            a.push_back(b);
        }
        else {
            b.push_back(infijo[i]);
            i++;
            while((pos=comprobaroperador(b,vop))==-1 && i<tama) {
                b.push_back(infijo[i]);
                ++i;
            } 
            if(operador(b,vop)) { //si es un operador, que metar # y luego el operador
                a.push_back(aux);
                a.push_back(b);
            }
            else { //es una variable
                if(pos!=-1) {
                    aux2.assign(b,0,pos);
                    i=inicio+pos;
                    a.push_back(aux2);//mete el numero
                }
                else {
                    a.push_back(b);//mete el numero
                }
            }
        }
        b.clear();
    }
    return a;
}
vector<string> pasarpostfijo(const vector<string> &infijo) {

    int ci,tope,cp,prioridad;
    cp=ci=tope=0;

    vector< string > Postfijo;
    Postfijo.resize(infijo.size()," ");
    vector< string > Pila;
    Pila.resize(infijo.size());
    cout<<"Pasar de infijo a postfijo"<<endl;
    for(ci=0; ci<infijo.size(); ci++) {
        if("("==infijo[ci]) {//para marcar el inicio de una formula secundaria.
            tope++;
            Pila[tope]=infijo[ci];
        } else {
            if(")"==infijo[ci]) {//si encuentra un parentesis cerrado.
                while(Pila[tope]!="(") {
                    Postfijo[cp]=Pila[tope];//saca de la pila los operadores necesarios; y los mete en posfijo.
                    cp++;
                    tope--;
                }
                Pila[tope]="\0";//sobreescribe en el parentesis abierto.
                tope--;
            }
            else {//si no es ni un parentesis abierto ni cerrado.
                if(infijo[ci]!="#") {// si es un operando
                    Postfijo[cp]=infijo[ci];//escribimos el operando en Postfijo
                    cp++;
                }
                else {//si es un operador
                    ci++;//ya que nos encontramos en # y los siguiente es un operador
                    prioridad=1;//si prioridad=1 introduce en el Postfijo el valor actual de infijo. Si prioridad=0 introduce el valor que habia en la Pila.
                    //comprueba la prioridad

                    if(Pila[tope]=="/") {
                        if(infijo[ci]=="+"||infijo[ci]=="-"||infijo[ci]=="*"||infijo[ci]=="/")
                            prioridad=0;
                    }
                    else {
                        if(Pila[tope]=="*") {
                            if(infijo[ci]=="+"||infijo[ci]=="-"||infijo[ci]=="*")
                                prioridad=0;
                        }
                        else {
                            if(Pila[tope]=="+") {
                                if(infijo[ci]=="+"||infijo[ci]=="-")
                                    prioridad=0;
                            }
                            else {
                                if(Pila[tope]=="-") {
                                    if(infijo[ci]=="-")
                                        prioridad=0;
                                }
                            }
                        }
                    }
                    if(prioridad==0) {
                        while(tope>0) {
                            Postfijo[cp]=Pila[tope];//escribimos en el Postfijo el operador de la Pila
                            cp++;
                            tope--;
                        }
                    }
                    tope++;
                    Pila[tope]=infijo[ci];//metemos el operador del infijo en la Pila
                }
            }
        }
    }
    while(tope>0) {//para meter los operadores que quedan.
        Postfijo[cp]=Pila[tope];
        cp++;
        tope--;
    }
    return Postfijo;

}

main() {

//aconsejable eliminar espacios
//modificar los corchetes por ()
    string a ("(1kg+sen(Xm))*33-84/sqrt(5)");//funciona tanto si ponemos sen(5) como sen5
    vector< string > infijo,Postfijo;
    infijo=convertir(a);
    cout<<"mostramos en infijo"<<endl;
    mostrar(infijo);

    Postfijo=pasarpostfijo(infijo);
    cout<<"mostramso en postfijo"<<endl;
    mostrar(Postfijo);
    return 0;
}
