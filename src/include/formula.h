/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca*/
/*
Fermath Project:Formula
Version:1.1
*/

#include "expression.h"
//This class stores a formula using magnitudes and operators

class formula {
private:
    string name; //if formula has a name
    vector<magnitude_id> mag_v;
    vector<op> operation_v;
    vector<bool> selection;
public:
    formula() {
    }
    formula(const string &nam) {
        name=nam;
    }
    formula(const formula &form) {
        (*this)=from;
    }
    //MODIFICATION
    void add_magnitude(const magnitude_id &mid) {
        mag_v.push_back(mid1);
        selection.push_back(selec_d);
    }
    void add_operation(op oper) {
        oper.erase_name();
        operation_v.push_back(oper);
        selection.push_back(selec_operation);
    }
    void set_name(const string &name2) {
        name=name2;
    }
    void erase_name() {
        name.clear();
    }
    void clear() {
        erase_name();
        mag_v.clear();
        operation_v.clear();
        selection.clear();
    }


    //ACCESS
    string get_name() const {
        return name;
    }



    // operator=
    formula &operator=(const formula &form2) {
        if(this!=&form2) {
            (*this).clear();
            (*this).name=form2.name;
            (*this).mag_v=form2.mag_v;
            (*this).operation_v=form2.operation_v;
            (*this).selection=form2.selection;
        }
        return (*this);
    }

private:
    void clean_operators() {
        for(unsigned int i=0; i<operation_v.size(); i++) {
            operation_v[i].erase_name();
        }
    }
    void check() const {
    }

};
