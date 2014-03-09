/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Operators Class
Version:0.8
*/
#include "beta_rep.h"
#include "templates.h"
using namespace std;
typedef unsigned short operation_id; //0 es null
const operation_id binary_max=6;
const operation_id unary_max=10; //maximun values for an operator
#define unary_operator 0
#define binary_operator 1
class op {
private://le ponemso un identificador a cada operador.
    string text;
    operation_id id;
    bool type;//binary operator or unary operator
public:
    op() {
        id=0;
    }
    op(string text2,operation_id id2,bool bin) {
        text=text2;
        id=id2;
        type=bin;
    }
    op(const op &oper2) {
        (*this)=oper2;
        text=oper2.get_text();
    }
    op(const string &s) {
        id=0;
        text=s;
    }
    op(ifstream &input) {
        read_operator(input);
    }
    //Modificators
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
    //Access
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
    bool same_name(op oper2) const {
        if(text==oper2.get_text()) return true;
        else return false;
    }
    bool is_null() const {
        if(id==0) return true;
        else return false;
    }
    bool same_op(const op &oper2) {
        bool eq=true;
        if(id!=oper2.get_id()) eq=false;
        if(type!=oper2.is_binary()) eq=false;
        return eq;
    }
    //write the operations in a binary file
    void write_operator(ofstream &out) const {
        binary_write(text,out);
        binary_write(id,out);
        binary_write(type,out);
    }
    void read_operator(ifstream &input) {
        binary_read(text,input);
        binary_read(id,input);
        binary_read(type,input);
    }
    //show operator in detail
    void show_operator(ostream &out=cout) const {
        out<<text<<"  "<<"id:"<<id<<"  ";
        if(is_binary()) out<<"binary";
        else out<<"unary";
        out<<"\n";
    }
    bool have_name() const {
        return !(text.empty());
    }
    void erase_name() {
        text.clear();
    }

    //OPERATORS
    //operator==
    //dos operaciones son iguales si nombre son iguales
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
    bool operator>(const op &oper2) const {
        if(text>oper2.text) return true;
        else return false;
    }
    bool operator<=(const op &oper2) const {
        if(text<=oper2.text) return true;
        else return false;
    }
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
    //operator <<, show the operator os the standard output
    friend ostream  &operator<< (ostream &out, const op &oper) {
        out<<oper.text;
        return out;
    }

    void check() {
        if(type==unary_operator && id>unary_max) error_report("Error in operator while checking",1,1);
        if(type==binary_operator && id>binary_max) error_report("Error in operator while checking",1,1);
    }
};


