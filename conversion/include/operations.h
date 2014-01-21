/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Operations Class
Version:0.7
*/
#include "beta_rep.h"
#include "templates.h"
//Class to store and do simple operations with doubles
typedef unsigned short operation_id; //all operations are stores in an unsigned short
class operations {
private:
    vector<operation_id> op;
    vector<double> data;
public:
    //CONSTRUCTORS
    operations() {
    }
    operations(operation_id op2,double dat) {
        add_operation(op2,dat);
    }
    operations(operation_id op2) {
        add_operation(op2);
    }
    operations(vector <operation_id> &op2,vector<double> &dat) {
        op=op2;
        data=dat;
        check();
    }
    //Contructor from input
    operations(ifstream &input) {
        read_operations(input);
        check();
    }
    //add a new binary operation and data for conversion
    void add_operation(operation_id op2,double dat) {
        op.push_back(op2);
        data.push_back(dat);
    }
    //add a new unary operation for conversion
    void add_operation(operation_id op2) {
        op.push_back(op2+100);
    }
    //erase the operation and the data linked to it
    void remove_operation(int pos) {
        if(pos<op.size()) {
            if(op[pos]>100)  op.erase(op.begin()+(pos));  //if is unary operation, only erases de operation
            else { //binary operation, erase operation and data
                int dpos=0;
                for(int i=0; i<pos; i++) {
                    if(op[i]<=100) dpos++;
                }
                op.erase(op.begin()+(pos));  //erase operation
                data.erase(data.begin()+(dpos));//erase data
            }
        }
        check();
    }
    //erase all operations
    void clear() {
        op.clear();
        data.clear();
    }
    //ACCESS
    //if there is no operations
    bool null_operation() const {
        if(op.size()==0) return true;
        return false;
    }
    //if all the operations are products or divisions
    bool product_operation() const {
        bool b=true;
        for(int i=0; i<op.size() && b; i++) {
            if(op[i]!=3 && op[i]!=4) b=false; //only true if all operations are * or /
        }
        return b;
    }
    //CLASS JOBS
    //Return the result of the operations using d1 (conversion from unit)
    double operate(double d1) const {
        int tam=op.size();
        for(int i=0; i<tam; i++) {
            if(op[i]<=100)   d1=calc(op[i],d1,data[i]); //binary operation
            if(op[i]>100) d1=calc(op[i]-100,d1); //unary operation
        }
        return d1;
    }
    //Inverse conversion, this do the operation in the inverse order and changing operation when needed (conversion to unit)
    double inverse_operate(double d1) const {
        operation_id op2;
        for(int i=op.size()-1; i>=0; i--) {
            op2=op[i];
            if(op2%2==0) op2--;
            else op2++;
            if(op[i]<=100) d1=calc(op2,d1,data[i]);
            if(op[i]>100) d1=calc(op2-100,d1);
        }
        return d1;
    }

    //READ AND WRITE
    //write the operations in a binary file
    void write_operations(ofstream &out) const {
        binary_write_vector(op,out);
        binary_write_vector(data,out);
    }
    void read_operations(ifstream &input) {
        binary_read_vector(op,input);
        binary_read_vector(data,input);
    }

    //OPERATORS
    //operator== (size and data of both vectors must be equal)
    bool operator==(const operations &oper2) const {
        bool eq=true;
        unsigned s1,s2,s3,s4;
        s1=(*this).op.size();
        s2=(*this).data.size();
        s3=oper2.op.size();
        s4=oper2.data.size();
        if(s1!=s3 || s2!=s4) eq=false; //if vectors size is different
        for(int i=0; i<s1 && eq==true; i++) {
            if((*this).op[i]!=oper2.op[i]) eq=false;
        }
        for(int i=0; i<s2 && eq==true; i++) {
            if((*this).data[i]!=oper2.data[i]) eq=false;
        }
        return eq;
    }
    // operator!=
    bool operator!=(const operations &oper2) const {
        return !((*this)==oper2);
    }
    // operator=
    operations &operator=(const operations &op2) {
        if(this!=&op2) {
            (*this).data=op2.data;
            (*this).op=op2.op;
        }
        check();
        return *this;
    }

private:
    //operator <<, show the operations os the standard output
    friend ostream  &operator<< (ostream &out, const operations &oper) {
        vector<operation_id> a=oper.op;
        vector<double> b=oper.data;
        for(int i=0; i<a.size(); i++) {
            out<<"("<<a[i]<<",";
            if(i<b.size() && a[i]<=100) out<<b[i];
            else out<<"-";
            out<<") ";
        }
        return out;
    }
    //private methods for resolving operations
    double calc(operation_id cal, double n1,double n2) const { //binary operations
        double r=0;
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
    double calc(operation_id cal,double n) const { //unary operations
        double r=0;
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
    void check() {
        int siz1=op.size();
        int c=0;
        for(int i=0; i<siz1; i++) {
            if(op[i]<=100) c++;
        }
        if(c!=data.size()) error_report("Error in class operations while checking",1,1);
    }

};
