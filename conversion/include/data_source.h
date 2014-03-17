/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Data Source Class
Version:0.9
*/

#include "glossary.h"
//This class controls I/O and relations between sources and glossary

class data_src {
private:
    glossary names; //stores names for units and magnitudes
    unit_source src; //stores basic and complex units and magnitudes
public:
    //CONSTRUCTOR
    data_src() {
    }
    data_src(const unit_source &src2,const glossary &names2) {
        names=names2;
        src=src2;
    }
    data_src(ifstream &input) {
        read(input);
    }
    //MODIFICATION
    magnitude_id add_magnitude(const string &n,const vector<string> &v) {
        magnitude_id id;
        magnitude m(n); //new magnitude the name
        id=src.add_magnitude(m);//add magnitude and returns id
        add_names(id,v); //adds all names of magnitude to the glossary
        add_magnitude_name(id,n);//adds the principal name of magnitude (if it isnt in v)
        return id;
    }

    unit_id add_unit(const complex_unit &u,magnitude_id id,vector<string> &v) {
        unit_id uid;
        uid=src.add_complex_unit(u,id);
        add_names(uid,v);
        if(u.have_default_name()) add_unit_name(uid,u.get_name());
        return uid;
    }
    unit_id add_unit(const basic_unit &bunit,magnitude_id magid,vector<string> &v) {
        unit_id uid;
        uid=src.add_basic_unit(bunit,magid);
        add_names(uid,v);
        add_unit_name(uid,bunit.get_name());
        return uid;
    }
    void add_names(magnitude_id id,const vector<string> &v) {
        names.add_names(id,v);
    }
    void add_names(unit_id id,const vector<string> &v) {
        names.add_names(id,v);
    }
    void add_magnitude_name(magnitude_id id,const string &n) {
        names.add_magnitude_name(id,n);
    }
    void add_unit_name(unit_id id,const string &n) {
        names.add_unit_name(id,n);
    }
    void clear() {
        names.clear();
        src.clear();
    }


    //ACCESS
    magnitude get_magnitude(string &n) const {
        magnitude m;
        magnitude_id mid=0;
        mid=get_magnitude_id(n);
        m=get_magnitude(mid);
        return m;
    }

    complex_unit get_unit(string &n) const {
        complex_unit u;
        unit_id uid;
        uid.first=0;
        uid.second=0;
        uid=get_unit_id(n);
        u=get_unit(uid);
        return u;
    }

    magnitude get_magnitude(magnitude_id mid) const {
        magnitude m;
        m=src.search_magnitude(mid);
        return m;
    }

    complex_unit get_unit(unit_id uid) const {
        complex_unit u;
        u=src.search_unit(uid);
        return u;
    }

    unit_id get_unit_id(const string &n) const {
        unit_id id;
        id=names.search_unit(n);
        return id;
    }

    magnitude_id get_magnitude_id(const string &n) const {
        magnitude_id id;
        id=names.search_magnitude(n);
        return id;
    }

    //TODO: unificar distintos data_source
    void write(ofstream &out) const {
        names.write(out);
        src.write(out);
    }
    void read(ifstream &input) {
        clear();
        names.read(input);
        src.read(input);
    }
private:
    void check() {
        //TODO
    }
};
