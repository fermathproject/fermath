/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Basic Unit Class & Basic Unit Source Class
Version:0.9.2
*/

#include "operator.h"

typedef double data_type; //type of data for calc
typedef double conversion_data; //type of data for conversion calc
typedef unsigned short basic_unit_id;

class basic_unit {
private:
    vector<op> operations;
    vector<conversion_data> data;
    string name;
public:
    //CONSTRUCTORS
    basic_unit() {
    }
    basic_unit(const string &name2,const vector<op> &operations2,const vector<conversion_data> &data2) {
        operations=operations2;
        data=data2;
        name=name2;
        erase_operations_names();
        check();
    }
    basic_unit(const string &name2,const op &oper) {
        name=name2;
        add_operation(oper);
    }
    basic_unit(const string &name2,const op &oper,const conversion_data &dat) {
        name=name2;
        add_operation(oper,dat);
    }
    basic_unit(const string &n) {
        name=n;
    }
    basic_unit(ifstream &input) {
        (*this).read(input);
    }
    basic_unit(const basic_unit &b) {
        (*this)=b;
    }
    //MODIFICATION
    //add a new binary operation and data for conversion
    void add_operation(op op2,conversion_data dat) {
        op2.erase_name();
        if(op2.is_null()==true) error_report(user_error,"no es posible añadir operacion nula a conversion",0,1);
        else {
            if(op2.is_binary()==false) {
                error_report(user_error,"añadiendo operacion unaria, el valor de operacion sera eliminado",0,1);
                add_operation(op2);
            }
            else {
                operations.push_back(op2);
                data.push_back(dat);
            }
        }
        check();
    }
    //add a new unary operation for conversion
    void add_operation(op op2) {
        op2.erase_name();
        if(op2.is_null()==true) error_report(user_error,"no es posible añadir operacion nula a conversion",0,1);
        else {
            if(op2.is_binary()==true)  error_report(user_error,"necesario valor para añadir operacion binaria",0,1);
            else    operations.push_back(op2);
        }
        check();
    }

    //erase the operation and the data linked to it
    void remove_operation(unsigned int pos) {
        if(pos<operations.size()) {
            if(operations[pos].is_binary()==false)  operations.erase(operations.begin()+(pos));  //if is unary operation, only erases de operation
            else { //binary operation, erase operation and data
                int dpos=0;
                for(unsigned int i=0; i<pos; i++) {
                    if(operations[i].is_binary()==true) dpos++;
                }
                operations.erase(operations.begin()+(pos));  //erase operation
                data.erase(data.begin()+(dpos));//erase data
            }
        }
        check();
    }
    void set_name(const string &name2) {
        name=name2;
        if(name.empty()) error_report(class_error,"basic_unit should have a name",1,1);
    }
    void clear() {
        operations.clear();
        name.clear();
        data.clear();
    }


    //ACCESSS
    //if all the operations are products or divisions
    string get_name() const {
        return name;
    }
    //if there is no operations
    bool null_conversion() const {
        if(operations.empty()==true) return true;
        else return false;
    }
    bool product_conversion() const {
        bool b=true;
        operation_id x;
        for(unsigned int i=0; i<operations.size() && b; i++) {
            x=operations[i].get_id();
            if(x!=3 && x!=4) b=false; //only true if all operations are * or /
        }
        return b;
    }
    bool same_name(const basic_unit &unit2) const {
        if((*this).name==unit2.name) return true;
        else return false;
    }
    //CLASS JOBS
    //Return the result of the operations using d1 (conversion from unit)
    data_type convert(data_type d1) const {
        //check();
        int tam=operations.size();
        int c=0; //counter for data
        for(int i=0; i<tam; i++) {
            if(operations[i].is_binary()==true) {
                d1=calc(operations[i].get_id(),d1,data[c]); //binary operation
                c++;
            }
            if(operations[i].is_binary()==false) d1=calc(operations[i].get_id(),d1); //unary operation
        }
        return d1;
    }
    //Inverse conversion, this do the operation in the inverse order and changing operation when needed (conversion to unit)
    data_type inverse_convert(data_type d1) const {
        // check();
        int c=data.size()-1;
        for(int i=operations.size()-1; i>=0; i--) { //binary operation
            if(operations[i].is_binary()==true) {
                d1=calc(operations[i].get_inverse_id(),d1,data[c]);
                c--;
            }
            if(operations[i].is_binary()==false) d1=calc(operations[i].get_inverse_id(),d1);//unary operation
        }
        return d1;
    }

    //I/O
    //write the basic unit in a binary file
    void write(ofstream &out) const {
        binary_write(name,out);
        binary_write_vector(data,out);
        unsigned short opsize=operations.size();
        binary_write(opsize,out);
        for(int i=0; i<opsize; i++) {
            operations[i].write(out);
        }
    }
    void read(ifstream &input) {
        unsigned short opsize;
        clear();
        binary_read(name,input);
        binary_read_vector(data,input);
        binary_read(opsize,input);
        operations.resize(opsize);
        for(unsigned short i=0; i<opsize; i++) {
            operations[i].read(input);
        }
        check();
    }
    //show the complete information of basic_unit
    void show(ostream &out=cout) const {
        out<<name<<":";
        for(unsigned int i=0; i<operations.size(); i++) {
            out<<"("<<operations[i].get_id()<<",";
            if(i<data.size() && operations[i].is_binary()) out<<data[i];
            else out<<"-";
            out<<") ";
        }
    }
    //OPERATORS
    //operator==
    bool operator==(const basic_unit &unit2) const {
        if(same_name(unit2)==false) return false;
        else {
            if(same_conversion(unit2)==true) return true;
            else return false;
        }
    }
    // operator!=
    bool operator!=(const basic_unit &u2) const {
        return !((*this)==u2);
    }
    // operator=
    basic_unit &operator=(const basic_unit &op2) {
        if(this!=&op2) {
            (*this).data=op2.data;
            (*this).operations=op2.operations;
            (*this).name=op2.name;
        }
        check();
        return (*this);
    }
private:
    //operator <<, show the operations os the standard output
    friend ostream  &operator<< (ostream &out, const basic_unit &u) {
        out<<u.name;
        return out;
    }
    void erase_operations_names() {
        for(unsigned int i=0; i<operations.size(); i++) {
            operations[i].erase_name();
        }
    }

    bool same_conversion(const basic_unit &unit2) const {
        bool eq=true;
        unsigned int s1,s2,s3,s4;
        s1=(*this).operations.size();
        s2=(*this).data.size();
        s3=unit2.operations.size();
        s4=unit2.data.size();
        if(get_name()!=unit2.get_name()) eq=false;
        if(s1!=s3 || s2!=s4) eq=false; //if vectors size is different
        for(unsigned int i=0; i<s1 && eq==true; i++) {
            if((*this).operations[i]!=unit2.operations[i]) eq=false;
        }
        for(unsigned int i=0; i<s2 && eq==true; i++) {
            if((*this).data[i]!=unit2.data[i]) eq=false;
        }
        return eq;
    }
    //private methods for resolving operations
    //TODO:move the methods out of the class
    data_type calc(operation_id cal, data_type n1,data_type n2) const { //binary operations
        data_type r=0;
        switch(cal) {
        case 1:
            r=n1+n2;
            break;
        case 2:
            r=n1-n2;
            break;
        case 3:
            r=n1*n2;
            break;
        case 4:
            if(n2==0) cout<<"error in division(fix this)";
            r=n1/n2;
            break;
        case 5:
            r=pow(n1,n2);
            break;
        case 6:
            if(n2==0) cout<<"error en raiz(fix this)";
            r=pow(n1,1/n2);
            break;
        }
        return r;
    }
    data_type calc(operation_id cal,data_type n) const { //unary operations
        data_type r=0;
        switch(cal) {
        case 1:
            if(n<0) cout<<"error en raiz cuadrada(arreglar esto)";
            r=sqrt(n);
            break;
        case 2:
            r=n*n;
            break;
        case 3:
            r=sin(n);
            break;
        case 4:
            r=asin(n);
            break;
        case 5:
            r=cos(n);
            break;
        case 6:
            r=acos(n);
            break;
        case 7:
            r=tan(n);
            break;
        case 8:
            r=atan(n);
            break;
        case 9:
            r=exp(n);
            break;
        case 10:
            r=log(n);
            break;
        }
        return r;
    }

    void check() const {
        unsigned  int siz1=operations.size();
        unsigned int c=0;
        if(name.empty()) error_report(error_check,"basic unit should have name",1,1);
        for(unsigned int i=0; i<siz1; i++) {
            if(operations[i].is_null()==true) error_report(warning_check,"operation in conversion should not be null",1,1);
            if(operations[i].have_name()==true) error_report(warning_check,"operation in conversion should not have a name",0,1);
            if(operations[i].is_binary()==true) c++;
        }
        if(c!=data.size()) error_report(class_error,"problem in conversion of basic unit",1,1);
    }
};

//*********************************************

/*This class stores all the basic units in a vector, the units can be added but not removed or changed of position, also,
all the units should be different, the position in the vector will be considerate as the basic_unit_id, which will be returned when added a unit
*/
class basic_unit_source {
private:
    vector<basic_unit> src;
public:
    basic_unit_source() {
    }
    basic_unit_source(const vector<basic_unit> &src2) {
        src=src2;
        check();
    }
    //MODIFICATION
    basic_unit_id add(const basic_unit &uni) {
        int siz=src.size();
        for(int i=0; i<siz; i++) {
            if(src[i]==uni) { //if the unit exists, return the id of the existing unit
                return i;
            }
            else if(uni.same_name(src[i])==true) { //if exist a different unit with same name, error
                error_report(fatal_error,"two basic units with same name",1,1);
                return 0;
            }
        }
        basic_unit_id i=next_id();
        src.push_back(uni);
        return i;
    }
    void clear() {
        src.clear();
    }
    //ACCESS
    //convert to standard
    data_type convert(data_type d1,basic_unit_id id1) const {
        d1=src[id1].convert(d1);
        return d1;
    }
    basic_unit get_basic_unit(basic_unit_id buid) {
        return src[buid];
    }
    
    //convert from standard
    data_type inverse_convert(data_type d1,basic_unit_id id1) const {
        d1=src[id1].inverse_convert(d1);
        return d1;
    }
    string get_name(basic_unit_id id1) const {
        string s;
        if(id1<src.size()) s=src[id1].get_name();
        else error_report(class_error,"Error,basic_unit id not found",1,1);
        return s;
    }
    bool product_conversion(basic_unit_id id1) const {
        return src[id1].product_conversion();
    }
    bool standard_unit(basic_unit_id id1) const {
        return src[id1].null_conversion();
    }
    int next_id() const {
        return src.size();
    }
    int max_id() const {
        return src.size()-1;
    }
    //I/O
    void write(ofstream &out) const {
        unsigned short siz=src.size();
        binary_write(siz,out);
        for(int i=0; i<siz; i++) {
            src[i].write(out);
        }
    }
    void read(ifstream &input) {
        unsigned short siz;
        binary_read(siz,input);
        src.clear();
        src.reserve(siz);
        for(int i=0; i<siz; i++) {
            basic_unit bunit(input);
            src.push_back(bunit);
        }
    }
    void show(ostream &out=cout) const {
        for(unsigned int i=0; i<src.size(); i++) {
            cout<<i<<":";
            src[i].show(out);
            out<<endl;
        }
    }

private:
    void check() const {
        for(unsigned int i=0; i<src.size()-1; i++) {
            for(unsigned int j=i+1; j<src.size(); j++) {
                if(src[j].same_name(src[i])) error_report(fatal_error," basic units with same name",1,1);
            }
        }
    }

};
