/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Operators_list Class
Version:3
*/

#include <assert.h>     /* assert */
#include "operator.h"
using namespace std;

//#define unary_operator 0
//#define binary_operator 1

class op_list {
private://op_lista es un conjunto de operadores ordenados por el nombre.
    set<op> list;
public:
	//constructores
    op_list() {//constructor por defecto
    }
    op_list(op o) {
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
    void add_operator(op o) {
        list.insert(o);
        check();
    }
	//Operacion de eliminar un operador al conjunto.
    void remove_operator(const op &op2) {
	list.erase(op2);

    }
	//devuelve true si el operador dado por el string esta en el conjunto
    bool find_operator(string txt) const{
		return list.find(txt)!=list.end();

    }
	//devuelve el operador, a partir del nombre
	op get_op(string txt) const{
		set<op>::iterator it=list.find(txt);
		assert (it!=list.end());//si el operador no esta en el conjunto salta se produce un assert
		return *(it);

	}
	//devuelve el ide de un operador a partir de su string. Teniendo en cuenta que devuelve -1 si es unary y el ide si es unario
	int get_ide(string txt) const{//Tiene esta salida ya que se isa para la prioridad.
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
    void write_setoperator(ofstream &out) const {
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

};

