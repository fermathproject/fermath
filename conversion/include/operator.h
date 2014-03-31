/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Operators Class
Version:0.9.2
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
private://le ponemos un identificador a cada operador.
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
    op(operation_id id2,bool bin) {
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
        read(input);
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
    void write(ofstream &out) const {
        binary_write(text,out);
        binary_write(id,out);
        binary_write(type,out);
    }
    void read(ifstream &input) {
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
        if(type==unary_operator && id>unary_max) error_report(error_check,"Operator id out of range",1,1);
        if(type==binary_operator && id>binary_max) error_report(error_check,"Operator id our of range",1,1);
    }
};

//*************************************************
/*
class op_list {
private://op_lista es un conjunto de operadores ordenados por el nombre.
    set<op> list;
public:
	//constructores
    op_list() {//constructor por defecto
    }
    op_list(const op &o) {
        add_operator(o);
    }
    op_list(const vector<op> &v) {// constructor a partir de un vector
        for(int i=0; i<v.size(); i++) add_operator(v.at(i));
    }
    op_list(const set<op> &l) {//constructor a partir de un set
        set<op>::iterator it;
        for(it=list.begin();it!=list.end(); ++it) add_operator(*it);
    }
    op_list(const op_list &op2) {//constructor de copia
        (*this)=op2;
    }
	//Operacion de añadir un operador al conjunto.
    void add_operator(const op &o) {
        list.insert(o);
        check();
    }
	//Operacion de eliminar un operador al conjunto.
    void remove_operator(const op &op2) {
	list.erase(op2);
    }
	//devuelve true si el operador dado por el string esta en el conjunto
    bool is_operator(const string &txt) const{ //TODO: cambiar find_operator por is_operator!! (antonio)
		return list.find(txt)!=list.end();
    }
	//devuelve el operador, a partir del nombre
	op get_op(const string &txt) const{
	op result;
	set<op>::iterator it=list.find(txt);
	if(it==list.end()) error_report(class_error,"operator not found",1,1);
	else result=(*it);

		return result;
	}
	//devuelve el ide de un operador a partir de su string. Teniendo en cuenta que devuelve -1 si es unary y el ide si es unario
	int get_id(string txt) const{//antonio: cambiar get_ide por get_id //FIXME
		set<op>::iterator it=list.find(txt);
		assert (it!=list.end());//si el operador no esta en el conjunto salta se produce un assert
		if ((*it).is_binary()) return (*it).get_id();
		else return -1;
	}

    // operator=
    //iguala la id y el tipo (no el texto)
    op_list &operator=(const op_list &op2) {
        if(this!=&op2) {
            (*this).list=op2.list;
        }
        return *this;
    }

	//devuevle el iterador begin del conjunto
	set<op>::iterator begin() const {
		return list.begin();
	}
	//devuevle el iterador end del conjunto
	set<op>::iterator end() const {
		return list.end();
	}

	//write the operations in a binary file
    void write(ofstream &out) const { //TODO: antonio, cambiar por write
		int size=list.size();
		binary_write(size,out);
		set<op>::iterator it;
    	for(it=begin(); it!=end(); ++it) {
        	(*it).write_operator(out);
    	}
    }
	//read the operations of a binary file
    void read_setoperator(ifstream &input) {
		int size;
		binary_read(size,input);
		op x;
		for(int i=0;i<size;i++){
			x.read_operator(input);
			add_operator(x);
		}

    }
private:
	//chequea. Recorre el conjunto comprodando que el ide del operador se encuentra dentro de un rango.
    void check() {
        set<op>::iterator it;
        for(it=list.begin();it!=list.end(); ++it) {
            if((*it).get_type()==unary_operator && (*it).get_id()>unary_max) error_report("Error in operator list while checking",1,1);
            if((*it).get_type()==binary_operator && (*it).get_id()>binary_max) error_report("Error in operator list while checking",1,1);
        }
    }

};*/
