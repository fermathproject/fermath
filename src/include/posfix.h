/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca
*/
/*
Fermath Project:Posfix
Version:0.9.5
*/

#include "expression.h"


using namespace std;

//devuelve true si el operador, dado a partir del string, esta en el conjunto
bool operador(const string &a,const data_src &datasrc) {
    return datasrc.is_operator(a);
}

//comprueba si en el string a se encuentra un operador o un parentesis. Devuelve la posicion en la que empieza.
int comprobaroperador(const string &a,const data_src &datasrc) {
    int pos;
    set<op>::iterator it;
    for(it=datasrc.op_begin(); it!=datasrc.op_end(); ++it) {//recorre el conjunto de operadores comprobandolo.
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

//Tiene de entrada el conjunto de operandos y un string con la operacion completa. Devuelve un vector de string.
//Donde cada string sera una variable, un operador o un string aux(#)
vector<string> convertir(const string &infijo,const data_src &datasrc) {   //convierte en un vector de string
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
            while((pos=comprobaroperador(b,datasrc))==-1 && i<tama) {//mientras no sea un operador, va rellenando el string b.
                b.push_back(infijo[i]);
                ++i;
            }
            if(operador(b,datasrc)) { //si es un operador, que metar # y luego el operador
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
bool fprioridad(const string &pila,const string &infijo,const data_src &datasrc) {     //tener en cuenta ^
    bool p=true;
    if(pila.empty()==false || infijo.empty()==false) return true; //FIXME
    op oppila=datasrc.get_operator(pila);
    op opinfijo=datasrc.get_operator(infijo);
    if(oppila.is_unary()) { //si en al pila encontramos un operador unario este tiene siempre preferencia.
        p=false;
    }
    else {
        if(oppila.is_binary() && opinfijo.is_binary()) { //si ambos operadores son binarios
            int idPilatope=oppila.get_id();//calculamso el identificador del operador de pila[tope]
            int idinfijoci=opinfijo.get_id();//calculamso el identificador del operador deinfijo[ci]
            if(idPilatope==5 && idinfijoci<=5) 	p=0;//id=5 -> ^
            else {
                if((idPilatope==4 || idPilatope==3) && (idinfijoci<=4 || idinfijoci<=3)) p=false; //id=4 -> /. id=3 -> *
                else {
                    if((idPilatope==1 || idPilatope==2) && (idinfijoci==1 || idinfijoci==2)) p=false;//id=1 -> +. id=2 -> -
                }
            }
        }
    }
    return p;
}
bool comma_char(char c) {
    if(c==39 || c==44 || c==46 || c==96) return true;
    else return false;
}
//transformar un string a variable
variable convert_string(string s,const data_src &datasrc) {
    // cout<<"convert string:"<<s<<endl;
    string name; //name si es incognita
    unit u; //unidad
    variable var;
    unsigned int i=0;
    if(s.size()>=1) {
        if((s[i]>='0' && s[i]<='9') || comma_char(s[i]==true)) { //if has a number
            char c;
            bool is_float=false;
            data_type dat=0; //numero
            unsigned int num_dec=1; //por cuanto dividir el caracter decimal siguiente
            for(i=0; i<s.size(); i++) {
                c=s[i];
                if(comma_char(s[i])==true) { //si el primer elemento es una coma, supone que es un numero 0.(x)
                    if(is_float==true) error_report(warning_check,"multiple, in same variable",1,1);
                    is_float=true;
                }
                else if(c>='0' && c<='9') {
                    if(is_float==false) { //añadir caracter entero
                        dat*=10;
                        dat+=c-'0';
                    }
                    if(is_float==true) { //añadir caracter decimal
                        data_type dat2;
                        dat2=c-'0';
                        dat2=dat2/(num_dec*10);
                        num_dec++;
                        dat+=dat2;
                    }
                }
                else {
                    break;
                }
            }
            var.set_value(dat);
            if(i<=s.size()-1) { //num+unit
                s=s.substr(i,s.size()-i);
                unit u;
                u=datasrc.get_unit(s);
                if(u.is_null()) error_report(user_error,"Unit not found",1,1);
                else var.set_unit(u);
            }
        }
        else { //variable incógnita o solo unidad
            unit u;
            u=datasrc.get_unit(s);
            if(u.is_null()) var.set_name(s); //incognita
            else {
                var.set_value(1);
                var.set_unit(u);
            }
        }
    }
    /*    const basic_unit_source *bsrc;
         bsrc=datasrc.get_basic_source2();
         cout<<"convert string return:";
         var.show(*bsrc);
         cout<<endl;*/
    return var;
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
expression pasarpostfijo(const vector<string> &infijo,const data_src &datasrc) {
    expression expr;
    int tope;
    tope=0;
    vector< string > Pila;//vector auxiliar, donde ser cargaran los operadores
    Pila.resize(infijo.size());
    for(unsigned int ci=0; ci<infijo.size(); ci++) {//recorre el vector de infijo
        if("("==infijo[ci]) {//si es un parentesis abierto lo metemos en la pila.
            tope++;
            Pila[tope]=infijo[ci];
        }
        else {
            if(")"==infijo[ci]) {//si es un parentesis cerrado.
                while(Pila[tope]!="(") {//mientras no aparezca un parentesis abierto metemos los operadores en la pila de operadores y en el vector de postfijo
                    expr.add_operation(datasrc.get_operator(Pila[tope]));//cargamos en la pila de operadores
                    tope--;
                }
                Pila[tope]="\0";//sobreescribe en el parentesis abierto.
                tope--;
            }
            else {//si no es ni un parentesis abierto ni cerrado.
                if(infijo[ci]!="#") {// si no es un "#", sabemos que es un operando (variable)
                    expr.add_variable(convert_string(infijo[ci],datasrc));
                }
                else {//es un operador
                    ci++;
                    if(Pila[tope]!="(") {//si en la en el tope de la pila no hay un parentesis abierto comprobamos la propiedad
                        // prioridad=1;//si prioridad=1 introduce en el Postfijo el valor actual de infijo. Si prioridad=0 introduce el valor que habia en la Pila.
                        //comprueba la prioridad
                        if(!fprioridad(Pila[tope],infijo[ci],datasrc)) {
                            while(tope>0 && Pila[tope]!="(") {//cargamos los operadores
                                expr.add_operation(datasrc.get_operator(Pila[tope]));//en la pila de operadores
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
        expr.add_operation(datasrc.get_operator(Pila[tope]));//la pila de operadores
        tope--;
    }
    return expr;//devolvemos el vector de postfijo
    //devolvemos en los argumentos por referencia:
    //-una pila de string con las variables
    //-una pila de operator con los operadores
    //-una pila de int para determinar si va 0=variable y 1=operador
}
expression convertirpostfijo(string a, const data_src &datasrc) {
    vector< string > infijo;
    check_parenthesis(a);
    infijo=convertir(a,datasrc); //convierte string a vector<string> (añade #delante de operadores)
    expression expr;
    expr=pasarpostfijo(infijo,datasrc);
    return expr;
}
