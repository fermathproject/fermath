// *************************************************************************************** //
// VERSION 1. POSTFIJO.
// 
// Este porgrama se encarga de tomar un string con la fomurmula, la cual puede tener:
// numeros,variables,operadores y parentesis.
//
// Tenemos una pequeña base de datos con operadores la cual se ampliara en siguintes versiones.
// 
// El progrma se encarga de crear un vector de string y ordenarlos en formato postfijo,
// el cual es ma facil de trabajar en una pila.
//
//
// (C) Programmed by:
// Antonio Jimenez Martínez
// Andrés Ortiz Corrales
// Mariano Palomo Villafranca
// *************************************************************************************** //


#include<stdio.h>
#include <string>
#include <vector>
#include <iostream>
//cp contadorpostfijo
//ci contadorinfijo
using namespace std;
bool operadorlargo(const string & a)
{
    return a=="sqrt" ||  a=="sen" || a=="cos";
}

bool operador(const char & a)//comprobar si no es un operando
{
    return a=='/' ||  a=='*' || a=='+' || a=='-' || a==')' || a=='(' ;
}
bool operador(const char & a,bool & parentesis)//comprobar si es un operando tneiendo en cuenta si es un parentesis
{
    parentesis=(a==')' || a=='(');
    return a=='/' ||  a=='*' || a=='+' || a=='-' || parentesis ;
}
void mostrar(const vector<string> & a)
{
    for(int i=0; i<a.size(); ++i) {
        cout<<a[i]<<"  ";
    }
    cout<<endl;
}

vector<string> convertir(const string & infijo) {//convierte en un vector de string
    bool esoperadorlargo=false,parentesis=false;
    int tama;
    string aux("#");
    tama=infijo.size();
    vector< string > a;
    string b;
    b.clear();
    int i=0;
    while(i<tama) {
        if(operador(infijo[i],parentesis)) { //si es un operador
            b.push_back(infijo[i]);
            ++i;
            if(!parentesis)//si no es un parentesis mete una #
                a.push_back(aux);
            a.push_back(b);
            b.clear();
        }
        else { //si no es un operador
            while(!(operador(infijo[i])) && i<tama && !esoperadorlargo) {
                b.push_back(infijo[i]);
                ++i;
                esoperadorlargo=operadorlargo(b);
            }
            if(esoperadorlargo) {
                a.push_back(aux);
                esoperadorlargo=false;
            }
            a.push_back(b);
            b.clear();
        }
    }
    return a;
}

main() {

//aconsejable eliminar espacios
//modificar lso corchetes por ()
    string a ("(1kg+sen(Xm))*33-84/sqrt(5)");//funciona tanto si ponemos sen(5) como sen5
    vector< string > infijo;
    infijo=convertir(a);
    cout<<"mostramso en infijo"<<endl;
    mostrar(infijo);




    int ci,tope,cp,prioridad;
    cp=ci=tope=0;

    vector< string > Postfijo;
    Postfijo.resize(infijo.size()," ");//el doble ya que metemos espacio entre numeros.
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
    cout<<"mostramso en postfijo"<<endl;
    mostrar(Postfijo);
    return 0;
}
