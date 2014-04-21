/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca*/
/*
Fermath Project:Expression
Version:0.9.4
*/

#include "variable_calc.h"
//This class stores an expresion as vectors of operators and variables in posfix form
//For example: 5kg + 8kg * 3 --> 8kg 3 * 5 kg +
#define selec_data 0
#define selec_operation 1
class expression {
private:
    string name; //if expr has a name
    vector<variable> data_v;
    vector<op> operation_v;
    vector<bool> selection;
public:
    //CONSTRUCTORS
    expression() {
    }
    expression(const string &name2,const vector<variable> &data_v2,const vector<op> &op2, const vector<bool> &selec2) {
        name=name2;
        data_v=data_v2;
        operation_v=op2;
        selection=selec2;
        clean_operators();
        check();
    }
    expression(const vector<variable> &data_v2,const vector<op> &op2,const vector<bool> &selec2) {
        data_v=data_v2;
        operation_v=op2;
        slection=selec2;
        clean_operators();
        check()
    }
    expression(const variable &var1) {
        add_variable(var1,oper);
        clean_operators();
        check();
    }
    expression(const expression &expr2) {
        (*this)=expr2;
    }
    //MODIFICATION
    void add_variable(const variable &var1) {
        data_v.push_back(var1);
    }
    void set_name(const string &name2) {
        name=name2;
    }
    void erase_mame() {
        name.clear();
    }
    void clear() {
        erase_name();
        data_v.clear();
        operation_v.clear();
        selection.clear();
    }
    //add unary operation
    void add_operation(operation_id oper) {
        if(oper>unary_max || oper==0) error_report(fatal_error,"operation_id not valid",1,1);
        else {
            op oper2(oper,unary_operator);
            operation_v.push_back(oper);
        }
        clean_operators();
        check();
    }
    //add binary operation
    void add_operation(const variable &var,operation_id oper) {
        if(oper>binary_max || oper==0) error_report(fatal_error,"operation_id not valid",1,1);
        else {
            data_v.push_back(var);
            op oper2(oper,binary_operator);
            operation_v.push_back(oper);
        }
        clean_operators();
        check();
    }

    //ACCESS
    string get_name()const {
        return name;
    }
    bool have_name() const {
        return !name.empty();
    }
    //true if only has a variable and no operations
    bool is_variable() const {
        if(data_v.size()==1 && operations.empty()==true) return true;
        else return false;
    }

    //JOBS
    variable evaluate(const data_src &src) const { //TODO:solve if dont have solution
        check();
        stack<variable> res;
        op oper;
        unsigned int p1=0,p2=0;
        for(unsigned int i=0; i<selection.size(); i++) {
            if(selection[i]==selec_data) {
                res.push(data_v[p1]);
                p1++;
            }
            else { //gets variables from stack, operate, and insert the again at top
                oper=operation_v[p2];
                if(oper.is_binary()) { //binary operation
                    variable a,b;
                    a=res.top();
                    res.pop();
                    b=res.top();
                    res.pop();
                    res.push(calculate(a,b,oper.get_id(),src);
                }
                else { //unary operation
                    variable a;
                    a=res.top();
                    res.pop();
                    res.push(calculate(a,oper.get_id(),src);
                }
                p2++;
            }
        }
        return res.top();
    }
    /* variable get_result(const data_src &src) const {
         variable result;
         expression expr2=(*this).evaluate(src);
         if(expr2.is_variable()==true) result=expr2;
         else error_report(user_error,"no result in expresion",0,1);
         return result;
     }*/
    //TODO:show expression
    // operator=
    expression &operator=(const expression &expr2) {
        if(this!=&expr2) {
            ⁽*this).clear();
            (*this).name=expr2.name;
            (*this).data_v=expr2.data_v;
            (*this).operation_v=expr2.operation_v;
            (*this).selection=expr2.selection;
        }
        return (*this);
    }

private:
    void clean_operators() {
        for(unsigned int i=0; i<operation_v.size(); i++) {
            operation_v[i].erase_name();
        }
    }
    void check() {
        unsigned int j=1;
        for(unsigned int i=0; i<operation_v.size(); i++) {
            if(operation_v[i].get_id()==0) error_report(user_error,"null operator in expr",1,1);
            if(operation_v[i].have_name()==true) error_report(warning_check,"operation in expr with name",1,1);
            if(operation_v[i].is_binary()==true) j+=1;
            if(j!=data_v.size()) error_report(class_error,"Data and expression with different sizes",1,1);
        }
    }
};
