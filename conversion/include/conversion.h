/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Conversion Class
Version:0.8
*/
#include "operator.h"

typedef double data_type;
//Class to store and do simple operations with doubles
class conversion {
private:
    vector<op> operations;
    vector<data_type> data;
public:
    //CONSTRUCTORS
    conversion() {
    }
    conversion(op op2,data_type dat) {
        add_operation(op2,dat);
    }
    conversion(op op2) {
        add_operation(op2);
    }
    conversion(vector <op> &op2,vector<data_type> &dat) {
        for(int i=0; i<op2.size(); i++) {
            op2[i].erase_name();
        }
        operations=op2;
        data=dat;
        check();
    }
    //Contructor from input
    conversion(ifstream &input) {
        read_conversion(input);
        check();
    }
    //add a new binary operation and data for conversion
    void add_operation(op op2,data_type dat) {
        op2.erase_name();
        if(op2.is_null()==true) error_report("Error,no es posible añadir operacion nula a conversion",1,1);
        else {
            if(op2.is_binary()==false) {
                error_report("Warning, añadiendo operacion unaria, el valor sera eliminado",1,1);
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
        if(op2.is_null()==true) error_report("Error,no es posible añadir operacion nula a conversion",1,1);
        else {
            if(op2.is_binary()==true)  error_report("Error, necesario valor para añadir operacion binaria",1,1);
            else    operations.push_back(op2);
        }
        check();
    }

    //erase the operation and the data linked to it
    void remove_operation(int pos) {
        if(pos<operations.size()) {
            if(operations[pos].is_binary()==false)  operations.erase(operations.begin()+(pos));  //if is unary operation, only erases de operation
            else { //binary operation, erase operation and data
                int dpos=0;
                for(int i=0; i<pos; i++) {
                    if(operations[i].is_binary()==true) dpos++;
                }
                operations.erase(operations.begin()+(pos));  //erase operation
                data.erase(data.begin()+(dpos));//erase data
            }
        }
        check();
    }
    //erase all operations
    void clear() {
        operations.clear();
        data.clear();
    }
    //ACCESS
    //if there is no operations
    bool null_operation() const {
        if(operations.empty()==true) return true;
        return false;
    }
    //if all the operations are products or divisions
    bool product_operation() const {
        bool b=true;
        operation_id x;
        for(int i=0; i<operations.size() && b; i++) {
            x=operations[i].get_id();
            if(x!=3 && x!=4) b=false; //only true if all operations are * or /
        }
        return b;
    }
    //CLASS JOBS
    //Return the result of the operations using d1 (conversion from unit)
    data_type operate(data_type d1) const {
        check();
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
    data_type inverse_operate(data_type d1) const {
        check();
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

    //READ AND WRITE
    //write the operations in a binary file
    void write_conversion(ofstream &out) const {
        binary_write_vector(data,out);
        unsigned short opsize=operations.size();
        binary_write(opsize,out);
        for(int i=0; i<opsize; i++) {
            operations[i].write_operator(out);
        }
    }
    void read_conversion(ifstream &input) {
        unsigned short opsize;
        clear();
        binary_read_vector(data,input);
        binary_read(opsize,input);
        operations.reserve(opsize);
        op op2;
        for(unsigned short i=0; i<opsize; i++) {
            op2.read_operator(input);
            operations.push_back(op2);
        }
        check();
    }

    //OPERATORS
    //operator== (size and data of both vectors must be equal)
    bool operator==(const conversion &oper2) const {
        bool eq=true;
        unsigned s1,s2,s3,s4;
        s1=(*this).operations.size();
        s2=(*this).data.size();
        s3=oper2.operations.size();
        s4=oper2.data.size();
        if(s1!=s3 || s2!=s4) eq=false; //if vectors size is different
        for(int i=0; i<s1 && eq==true; i++) {
            if((*this).operations[i]!=oper2.operations[i]) eq=false;
        }
        for(int i=0; i<s2 && eq==true; i++) {
            if((*this).data[i]!=oper2.data[i]) eq=false;
        }
        return eq;
    }
    // operator!=
    bool operator!=(const conversion &oper2) const {
        return !((*this)==oper2);
    }
    // operator=
    conversion &operator=(const conversion &op2) {
        if(this!=&op2) {
            (*this).data=op2.data;
            (*this).operations=op2.operations;
        }
        check();
        return (*this);
    }

private:
    //operator <<, show the operations os the standard output
    friend ostream  &operator<< (ostream &out, const conversion &oper) {
        vector<op> a=oper.operations;
        vector<double> b=oper.data;
        for(int i=0; i<a.size(); i++) {
            out<<"("<<a[i].get_id()<<",";
            if(i<b.size() && a[i].is_binary()) out<<b[i];
            else out<<"-";
            out<<") ";
        }
        return out;
    }
    //private methods for resolving operations
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
            /*case 11:
                r=fabs(n);
                break;*/
        }
        return r;
    }
    void check() const {
        int siz1=operations.size();
        int c=0;
        for(int i=0; i<siz1; i++) {
            if(operations[i].is_null()==true) error_report("Error, operation in conversion should not be null",1,1);
            if(operations[i].have_name()==true) error_report("Warning, operation in conversion should not have a name",0,1);
            if(operations[i].is_binary()==true) c++;
        }
        if(c!=data.size()) error_report("Error in class operations while checking",1,1);
    }

};
