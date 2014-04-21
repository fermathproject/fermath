/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca
*/
/*
Fermath Project:Posfix
Version:0.9.4
*/

#include<stdio.h>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <stack>
#include <fstream>
#include "expression.h"



using namespace std;

//devuelve true si el operador, dado a partir del string, esta en el conjunto
bool operador(const string &a,const op_list &b) {
    return b.find_operator(a);
}

//comprueba si en el string a se encuentra un operador o un parentesis. Devuelve la posicion en la que empieza.
int comprobaroperador(const string &a,const op_list &b) {
    int pos;
    set<op>::iterator it;
    for(it=b.begin(); it!=b.end(); ++it) {//recorre el conjunto de operadores comprobandolo.
        if((pos=a.find((*it).get_text()))!=-1) return pos;
    }
    if((pos=a.find(")"))!=-1) return pos;
    if((pos=a.find("("))!=-1) return pos;
    return -1;
}

//devuelve true si el char es un parentesis,
bool parentesis(const char &a) {
    return  a==')' || a=='(' ;
}

//muestra un vector de string.
void mostrar(const vector<string> &a) {
    for(int i=0; i<a.size(); ++i) {
        cout<<a[i]<<"  ";
    }
    cout<<endl;
}

//crea el conjunto de operadores a partir de un archivo binario.
op_list cargarop_list(ifstream &input) {
    op_list v;
    v.read_setoperator(input);
    return v;
}

//Tiene de entrada el conjunto de operandos y un string con la operacion completa. Devuelve un vector de string.
//Donde cada string sera una variable, un operador o un string aux(#)
vector<string> convertir(const string &infijo,const op_list &vop) {  //convierte en un vector de string
    int tama=infijo.size();
    string aux("#");//Es un string auxliaiar que se coloca delante de los operadores para distinguirlos
    vector< string > salida;
    string b,aux2;//string auxiliares
    int i=0,pos,inicio;//i es el indice.
    while(i<tama) {
        inicio=i;
        if(parentesis(infijo[i])) { //si es un parentesis lo mete.
            b=infijo[i];
            ++i;
            salida.push_back(b);
        }
        else {//sin o es un parentesis
            b.push_back(infijo[i]);
            i++;
            while((pos=comprobaroperador(b,vop))==-1 && i<tama) {//mientras no sea un operador, va rellenando el string b.
                b.push_back(infijo[i]);
                ++i;
            }
            if(operador(b,vop)) { //si es un operador, que metar # y luego el operador
                salida.push_back(aux);
                salida.push_back(b);
            }
            else { //es una variable
                if(pos!=-1) {
                    aux2.assign(b,0,pos);//creamos la variable
                    i=inicio+pos;//calculamos el nuevo valor de i
                    salida.push_back(aux2);//mete el numero
                }
                else {//no es una variable.
                    salida.push_back(b);//mete el numero
                }
            }
        }
        b.clear();
    }
    return salida;
}

//calcula la priodioriadad. compara el valor del tope de la pila y el valor del string del infijo actual.
//devuelve 0 si pila tiene mas prioridad que infijo y devuevle 1 si al pila tiene menos prioridad que infijo
//la prioridad va de unary */ -+
int fprioridad(const string &pila,const string &infijo,const op_list &vop) {    //tener en cuenta ^
    int p=1;
    int idPilatope=vop.get_ide(pila);//calculamso el identificador del operador de pila[tope]
    int idinfijoci=vop.get_ide(infijo);//calculamso el identificador del operador deinfijo[ci]
    if(idPilatope==-1) {//si en al pila encontramos un operador unario este tiene siempre preferencia.
        p=0;
    }
    else {
        if(idPilatope!=-1 && idinfijoci!=-1) { //si ambos operadores son binarios
            if(idPilatope==5 && idinfijoci<=5) 	p=0;//id=5 -> ^
            else {
                if((idPilatope==4 || idPilatope==3) && (idinfijoci<=4 || idinfijoci<=3)) p=0; //id=4 -> /. id=3 -> *
                else {
                    if((idPilatope==1 || idPilatope==2) && (idinfijoci==1 || idinfijoci==2)) p=0;//id=1 -> +. id=2 -> -
                }
            }
        }
    }
    return p;
}

//pasa de formato infijo a formato postfijo
//salida:
//-un vector de string en formato postfijo
//-una pila de string con las variables
//-una pila de operator con los operadores
//-una pila de int para determinar si va 0=variable y 1=operador
//entrada:
//-Las diferentes pilas
//-un vector de string en infijo
//-El conjunto de operadores.
vector<string> pasarpostfijo(const vector<string> &infijo,const op_list &vop,stack<int> &posiciones01,stack<string> &variables,stack<op> &operadores) {
    int ci,tope,cp;
    cp=ci=tope=0;
    //cp contadorpostfijo
    //ci contadorinfijo
    vector< string > Postfijo;//vectro donde se cargará el formato postfijo
    Postfijo.resize(infijo.size()," ");
    vector< string > Pila;//vector auxiliar, donde ser cargaran los operadores
    Pila.resize(infijo.size());
    cout<<"Pasar de infijo a postfijo"<<endl;
    for(ci=0; ci<infijo.size(); ci++) {//recorre el vector de infijo
        if("("==infijo[ci]) {//si es un parentesis abierto lo metemos en la pila.
            tope++;
            Pila[tope]=infijo[ci];
        }
        else {
            if(")"==infijo[ci]) {//si es un parentesis cerrado.
                while(Pila[tope]!="(") {//mientras no aparezca un parentesis abierto metemos los operadores en la pila de operadores y en el vector de postfijo
                    operadores.push(vop.get_op(Pila[tope]));//cargamos en la pila de operadores
                    posiciones01.push(1);//metemos un 1 para determinar que es operador
                    Postfijo[cp]=Pila[tope];//saca de la pila los operadores necesarios; y los mete en posfijo.
                    cp++;
                    tope--;
                }
                Pila[tope]="\0";//sobreescribe en el parentesis abierto.
                tope--;
            }
            else {//si no es ni un parentesis abierto ni cerrado.
                if(infijo[ci]!="#") {// si no es un "#", sabemos que es un operando (variable)
                    variables.push(infijo[ci]);//cargamos la variable en la pila de variables
                    posiciones01.push(0);//metemos un 0 para determinar que es una variable
                    Postfijo[cp]=infijo[ci];//escribimos la variable en el Postfijo
                    cp++;
                }
                else {//es un operador
                    ci++;
                    if(Pila[tope]!="(") {//si en la en el tope de la pila no hay un parentesis abierto comprobamos la propiedad
                        // prioridad=1;//si prioridad=1 introduce en el Postfijo el valor actual de infijo. Si prioridad=0 introduce el valor que habia en la Pila.
                        //comprueba la prioridad
                        if(!fprioridad(Pila[tope],infijo[ci],vop)) {
                            while(tope>0 && Pila[tope]!="(") {//cargamos los operadores
                                operadores.push(vop.get_op(Pila[tope]));//en la pila de operadores
                                posiciones01.push(1);//metemos un 1 para determinar que es operador
                                Postfijo[cp]=Pila[tope];//escribimos en el Postfijo el operador de la Pila
                                cp++;
                                tope--;
                            }
                        }
                    }
                    tope++;
                    Pila[tope]=infijo[ci];//metemos el operador del infijo en la Pila
                }
            }
        }
    }
    while(tope>0) {//si quedan operadores en la pila, los metemos en:
        operadores.push(vop.get_op(Pila[tope]));//la pila de operadores
        posiciones01.push(1);//metemos un 1 para determinar que es operador
        Postfijo[cp]=Pila[tope];//el vector de postfijo
        cp++;
        tope--;
    }
    return Postfijo;//devolvemos el vector de postfijo
    //devolvemos en los argumentos por referencia:
    //-una pila de string con las variables
    //-una pila de operator con los operadores
    //-una pila de int para determinar si va 0=variable y 1=operador
}



/*main() {
//creamos la base de datos de operadores
    ifstream input("op.fermath");
    op_list vop=cargarop_list(input);
//aconsejable eliminar espacios y comprobar parentesis
//modificar los corchetes por ()
    string a ("((cos(b)-1kg)*sen(5)-(1T*5m))");//funciona tanto si ponemos sen(5) como sen5
    vector< string > infijo,Postfijo;
    infijo=convertir(a,vop);
    cout<<"mostramos en infijo"<<endl;
    mostrar(infijo);


    //creamos 3 pilas:
    //-una pila de string con las variables
    //-una pila de operator con los operadores
    //-una pila de int para determinar si va 0=variable y 1=operador
    stack<int> posiciones01;
    stack<string> variables;
    stack<op> operadores;
    Postfijo=pasarpostfijo(infijo,vop,posiciones01,variables,operadores);
    cout<<"mostramos el vector de string en postfijo"<<endl;
    mostrar(Postfijo);
    cout<<"mostramos la pila de las variables"<<endl;
    show_stack(variables);
    cout<<"mostramos la pila de los operadores"<<endl;
    show_stack(operadores);
    cout<<"mostramos la pila de las posiciones01 0=variable y 1=operador "<<endl;
    show_stack(posiciones01);
    cout<<endl<<endl;
    return 0;
}*/
