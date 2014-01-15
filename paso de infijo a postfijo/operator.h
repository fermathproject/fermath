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


using namespace std;
typedef unsigned short operation_id; //0 es null
#define unary_operator 0
#define binary_operator 1
class op {
private://le ponemso un identificador a cada operador.
    string text;
    operation_id id;
    bool type;//binary operator or unary operator
public:
    op() {
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
    //Access
    string get_text() const {
        return text;
    }
    operation_id get_id() const {
        return id;
    }
    //true si es una operacion binaria
    bool is_binary() const {
        return type;
    }
    bool same_name(op oper2) const {
        if(text==oper2.get_text()) return true;
        else return false;
    }
    //write the operations in a binary file
   /* void write_operator(ofstream &out) const {
        binary_write(text,out);
        binary_write(id,out);
        binary_write(type,out);
    }
    void read_operator(ifstream &input) {
        binary_read(text,input);
        binary_read(id,input);
        binary_read(type,input);
    }*/



    //OPERATORS
    //operator==
    //dos operaciones son iguales si su id y tipo son iguales
    bool operator==(const op &oper2) const {
        bool eq=true;
        if(id!=oper2.get_id()) eq=false;
        if(type!=oper2.is_binary()) eq=false;
        //if(same_name(oper2)==false) eq=false;
        return eq;
    }
    bool operator==(const string & a) const {
        return text==a;
    }

    // operator!=
    bool operator!=(const op &oper2) const {
        return !((*this)==oper2);
    }
    // operator=
    //iguala la id y el tipo (no el texto)
    op &operator=(const op &op2) {
        if(this!=&op2) {
            (*this).id=op2.id;
            (*this).type=op2.type;
            //(*this).text=op2.text;
        }
        return *this;
    }
/*
private:
    //operator <<, show the operations os the standard output
    friend ostream  &operator<< (ostream &out, const op &oper) {
        out<<text<<endl<<"id:"<<id<<"  ";
        if(is_binary()) out<<"binay"<<endl;
        else out<<"unary"<<endl;
        return out;
    }

}

void binary_write_vector(const vector<op> &v,ofstream &out) {
    max_size siz=v.size();
    op elem;
    binary_write(siz,out); //writes vector size
    for(max_size i=0; i<siz; i++) {
        elem=v[i];
        elem.write_operator(out);
    }
}

void binary_read_vector(vector<op> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read vector size
    op elem;
    v.clear();
    v.reserve(siz); //so its not necessary to change vector capacity later
    for(max_size i=0; i<siz; i++) {
        elem.read_operator(input);
        v.push_back(elem);
    }
}*/

};
