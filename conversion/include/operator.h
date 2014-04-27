/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Operators Class
Version:0.9.4
*/

#include "beta_rep.h"
#include "templates.h"
using namespace std;
typedef unsigned short operation_id; //0 es null
const operation_id binary_max=6;
const operation_id unary_max=4; //maximun values for an operator
#define unary_operator 0
#define binary_operator 1
class op {
private://cada operador esta formado por:un nombre, un identificador y un tipo(0 unary y 1 binary)
    string text;
    operation_id id;
    bool type;//binary operator or unary operator
public:
    //constructor
    op() {//constructor por defecto
        id=0;
    }
    op(operation_id id2,bool bin) {
        id=id2;
        type=bin;
    }
    op(string text2,operation_id id2,bool bin) {
        text=text2;
        id=id2;
        type=bin;
    }
    op(const op &oper2) {//constructor de copia
        (*this)=oper2;
        text=oper2.get_text();
    }
    op(const string &s) { //construcctor a partir de un string
        id=0;
        text=s;
    }
    op(ifstream &input) { //construcctor a partir de un archivo
        read(input);
    }

    //Modificators SET
    void set_text(string text2) {
        text=text2;
    }
    void set_operation_id(operation_id id2) {
        id=id2;
    }
    void set_as_binary() {
        type=binary_operator;
    }
    void set_as_unary() {
        type=unary_operator;
    }
    void set(string text2,operation_id id2,bool type2) {
        text=text2;
        id=id2;
        type=type2;
    }
    void clear() {
        id=0;
        text="";
    }

    //Access GET
    string get_text() const {
        return text;
    }
    operation_id get_id() const {
        return id;
    }
    bool get_type() const {
        return type;
    }
    //returns the id of the inverse operation (function not guaranteed)
    operation_id get_inverse_id() const {
        operation_id result;
        result=id;
        if(result!=0) {
            if(result%2==0) result--;
            else result++;
        }
        return result;
    }
    //true si es una operacion binaria
    bool is_binary() const {
        return type;
    }
    //true si es una operacion unaria
    bool is_unary() const {
        return !type;
    }
    bool have_name() const {
        return !text.empty();
    }
    bool same_name(op oper2) const {//devuelve true si los operadores tiene el mismo nombre
        if(text==oper2.get_text()) return true;
        else return false;
    }
    bool is_null() const {//devuelve true si operator es nulo
        if(id==0) return true;
        else return false;
    }
    bool same_op(const op &oper2) { //devuelve true si los operadores son el mismo( tiene el mismo id y el mismo tipo)
        bool eq=true;
        if(id!=oper2.get_id()) eq=false;
        if(type!=oper2.is_binary()) eq=false;
        return eq;
    }
    //write the operations in a binary file
    void write(ofstream &out) const {
        binary_write(text,out);
        binary_write(id,out);
        binary_write(type,out);
    }
    //read the operation of binary file
    void read(ifstream &input) {
        binary_read(text,input);
        binary_read(id,input);
        binary_read(type,input);
    }
    //show operator in detail(text,id,type)
    void show_operator(ostream &out=cout) const {
        out<<text<<"  "<<"id:"<<id<<"  ";
        if(is_binary()) out<<"binary";
        else out<<"unary";
        out<<"\n";
    }
    //elimina el nombre dle operador. Mantiene el ide y el tipo
    void erase_name() {
        text.clear();
    }

    void  show(ostream &out=cout) const {
        out<<text<<"  "<<id<<"  ";
        if(is_binary()) out<<"(bin)";
        else out<<"(un)";
    }
    //OPERATORS
    //operator==
    //dos operaciones son iguales si nombre son iguales, no tiene en cuenta id no tipo.
    bool operator==(const op &oper2) const {
        bool eq=true;
        //  if(id!=oper2.get_id()) eq=false;
        //  if(type!=oper2.is_binary()) eq=false;
        if(same_name(oper2)==false) eq=false;
        return eq;
    }
    //operador con texto
    bool operator==(const string &a) const {
        return text==a;
    }
    // operator!=
    bool operator!=(const op &oper2) const {
        return !((*this)==oper2);
    }
    //operator <,> (compares text)
    bool operator<(const op &oper2) const {
        if(text<oper2.text) return true;
        else return false;
    }
    //operator <,> (compares text)
    bool operator>(const op &oper2) const {
        if(text>oper2.text) return true;
        else return false;
    }
    //operator <,> (compares text)
    bool operator<=(const op &oper2) const {
        if(text<=oper2.text) return true;
        else return false;
    }
    //operator <,> (compares text)
    bool operator>=(const op &oper2) const {
        if(text>=oper2.text) return true;
        else return false;
    }

    // operator=
    //iguala la id y el tipo (no el texto)
    op &operator=(const op &op2) {
        if(this!=&op2) {
            (*this).id=op2.id;
            (*this).type=op2.type;
            //  (*this).text=op2.text;
        }
        return *this;
    }

private:
    //operator <<, show the operator os the standard output. Solo muestra el nombre del operador.
    friend ostream  &operator<< (ostream &out, const op &oper) {
        out<<oper.text;
        return out;
    }
    //cheque las operaciones. Tiene en cuenta el el ide y el numero maximo del ide de dicho tipo.
    void check() {
        if(type==unary_operator && id>unary_max) error_report(error_check,"Error in operator while checking",1,1);
        if(type==binary_operator && id>binary_max) error_report(error_check,"Error in operator while checking",1,1);
    }
};


