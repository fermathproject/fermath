/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Expression Class
Version:0.7
*/

//This class stores and process an expression with variables using stacks


//(5-3)*3+(2*2)  //inffix notation
//5 3 - 3 * 2 2 * + //suffix notation

//the suffix notation can be represented as:
//5 3 3 2 2
//- * * +
//0 0 1 0 1 0 0 1 1
#include "variable.h"

#define SEL_OPERATION 1
#define SEL_DATA 0 //macros for selection stack
class expression { //TODO:use variable operators in calc
private:
    string name;
    stack<operation_id> operations;
    stack<variable> data;
    stack<bool> selection; //0=data 1=operation
public:
    //CONSTRUCTORS
    expression() {
    }
    expression(const string &name2,const stack<operation_id> &operations2,const stack<variable> &data2,const stack<bool> &selec) {
        name=name2;
        operations=operations2;
        data=data2;
        selection=selec;
        check();
    }
    expression(const stack<operation_id> &operations2,const stack<variable> &data2,const stack<bool> &selec) {
        operations=operations2;
        data=data2;
        selection=selec;
        check();
    }

    expression(operation_id op,const variable &var1,const variable &var2) {
        add_data(var1);
        add_data(var2);
        add_operation(op);
        check();
    }
    expression(operation_id op,const variable &var) {
        add_data(var);
        add_operation(op);
        check();
    }
    //MODIFICATIONS
    void add_data(variable var) {
        data.push(var);
        selection.push(SEL_DATA);
        check();
    }
    void add_operation(operation_id op) {
        operations.push(op);
        selection.push(SEL_OPERATION);
        check();
    }
    void remove_last_element() {
        bool b=selection.top();
        selection.pop();
        if(b==SEL_DATA) data.pop();
        else operations.pop();
        check();
    }
    void set_name(const string &n) {
        name=n;
    }
    void erase_name() {
        name.clear();
    }
    void clear() {
        erase_name();
        for(int i=0; i<data.size(); i++) data.pop();
        for(int i=0; i<operations.size(); i++) operations.pop();
        for(int i=0; i<selection.size(); i++) selection.pop();
        check();
    }
    //ACCESS
    bool have_name() const {
        return !name.empty();
    }
    string get_name() const {
        return name;
    }



    variable solve_expression() const { //TODO: checking if operation have solution and segmentation fail
        stack<variable> dat=data;
        stack<bool> selec=selection;
        stack<operation_id> op=operations;
        stack<variable> result;
        bool b;
        unsigned o;
        while(selec.empty()==false) {
            b=selec.top();
            selec.pop();
            if(b==SEL_DATA) {
                result.push(dat.top());
                dat.pop();
            }
            if(b==SEL_OPERATION) {
                o=op.top();
                op.pop();
                solve_operation(result,o); //solve one operation
            }
        }
        return result.top();
    }

private:
    friend ostream  &operator<< (ostream &out, const expression &exp) {
        if(exp.have_name()) out<<exp.name<<"=";
        stack<variable> dat=exp.data;
        stack<bool> selec=exp.selection;
        stack<operation_id> op=exp.operations;
        bool b;
        while(selec.empty()==false) {
            b=selec.top();
            selec.pop();
            if(b==false) {
                out<<dat.top()<<" ";
                dat.pop();
            }
            if(b==true) {
                out<<op.top()<<" ";
                op.pop();
            }
        }
        return out;
    }
    variable calc(operation_id cal,const variable &n1,const variable &n2) const { //binary operations
        variable r;
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
            if(n2==0) error_report("error in division(fix this)",1,1);
            r=n1/n2;
            break;
            /*  case 5:
                  r=pow(n1,n2);
                  break;
              case 6:
                  if(n2==0) error_report("error en raiz(fix this)",1,1);
                  r=pow(n1,1/n2);
                  break;*/
        }
        return r;
    }
    variable calc(operation_id cal,const variable &n) const { //unary operations
        variable r=n;
        switch(cal) {
            /* case 1:
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
                */
        }
        return r;
    }
    //solve one operation
    void solve_operation(stack<variable> &result,operation_id op) const {
        variable x;
        if(op>100) {
            op-=100;
            variable a=result.top();
            result.pop();
            x=calc(op,a);
            result.push(x);
        }
        else {
            variable a=result.top();
            result.pop();
            variable b=result.top();
            result.pop();
            x=calc(op,a,b);
            result.push(x);
        }
    }

    void check() const {
        bool b=true;
        if(operations.size()+data.size()!=selection.size()) b=false;
        if(b==false) error_report("ERROR while checking expression",1,1);
    }

};
