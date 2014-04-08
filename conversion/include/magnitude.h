/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project: Magnitude Class
Version:0.9.3
*/

#include "unit.h"
typedef unsigned short magnitude_id; //id for difference between magnitude
typedef unsigned short complex_unit_id; //id for a complex unit in a magnitude
typedef pair<magnitude_id,complex_unit_id> unit_id; //full id needed for an unit (magnitude and unit)
unit_id null_id=make_pair(0,0);
//FUNCTIONS to work with ids ****
bool same_magnitude_id(unit_id id1,unit_id id2) {
    return (id1.first==id2.first);
}
bool same_magnitude_id(unit_id id1,magnitude_id id2) {
    return (id1.first==id2);
}
unit_id change_complex_id(unit_id id,complex_unit_id newid) {
    id.second=newid;
    return id;
}
unit_id change_magnitude_id(unit_id id,magnitude_id newid) {
    id.first=newid;
    return id;
}
void clear_unit_id(unit_id  id) {
    id.first=0;
    id.second=0;
}

//********************
class magnitude {
private:
    map<complex_unit_id,unit> src;
    complex_unit_id standard_unit;
    string name; //standard name of magnitude
public:
    magnitude() {
        standard_unit=0;
    }

    magnitude(const string &name2,const map<complex_unit_id,unit> &src2,complex_unit_id stdu) {
        src=src2;
        name=name2;
        standard_unit=stdu;
    }
    //constructor for a magnitude with his standard unit
    magnitude(const string &n2,const unit &std) {
        complex_unit_id id;
        id=add_unit(std);
        set_name(n2);
        standard_unit=0;
        set_standard_unit(id);
        check();
    }
    magnitude(const string &name2) {
        name=name2;
    }
    magnitude(const magnitude &m) {
        (*this)=m;
    }
    complex_unit_id add_unit(const unit &u) {
        complex_unit_id id=0;
        if(is_unit(u)==false) {
            id=next_id();
            if(src.size()==0) standard_unit=id;
            pair<complex_unit_id,unit> p;
            p.first=id;
            p.second=u;
            src.insert(p);
        }
        check();
        return id;
    }


    //removes unit, warning!!
    bool remove_unit(complex_unit_id id) {
        return src.erase(id);
    }

    void set_name(string n) {
        name=n;
    }
    void set_standard_unit(complex_unit_id uid) {
        if(is_unit(uid)==true) {
            standard_unit=uid;
        }
    }
    void clear() {
        src.clear();
        name.clear();
        standard_unit=0;
    }
    //ACCESS
    bool is_null() const {
        return src.empty();
    }
    string get_name()const {
        return name;
    }
    //search for unit (not by id)
    bool is_unit(const unit &u) const {
        map<complex_unit_id,unit>::const_iterator it;
        bool is=false;
        for(it=src.begin(); it!=src.end() && !is; it++) {
            if(u.same_unit((*it).second)==true) is=true;
        }
        return is;
    }
    //return size
    int size() const {
        return src.size();
    }

    bool is_unit(complex_unit_id id) const {
        map<complex_unit_id,unit>::const_iterator it;
        it=src.find(id);
        if(it==src.end()) return false;
        else return true;
    }

    unit search(complex_unit_id id) const {
        unit u;
        map<complex_unit_id,unit>::const_iterator it;
        it=src.find(id);
        if(it!=src.end()) u=(*it).second;
        return u;
    }
    unit get_standard_unit() const {
        return search(standard_unit);
    }
    complex_unit_id get_standard_unit_id() const {
        return standard_unit;
    }
    vector<complex_unit_id> get_units_ids() const {
        map<complex_unit_id,unit>::const_iterator it;
        vector<complex_unit_id> v;
        for(it=src.begin(); it!=src.end(); it++)  v.push_back((*it).first);
        return v;
    }
    //returns all the basic units used in magnitude
    set<basic_unit_id> get_basic_units() const {
        map<complex_unit_id,unit>::const_iterator it;
        set<basic_unit_id> result;
        for(it=src.begin(); it!=src.end(); it++) {
            pair< multiset<basic_unit_id>,multiset<basic_unit_id> > p;
            p=((*it).second).get_basic_units();
            merge_basic_id(p.first,result);
            merge_basic_id(p.second,result); //adds all the basic units in the result
        }
        return result;
    }
    //if is the same magnitude
    bool same_magnitude(const magnitude &mag2) const {
        unit a,b;
        a=(*this).get_standard_unit();
        b=mag2.get_standard_unit();
        if(a==b) return true;
        else return false;
    }

    //JOBS
    //convert from first unit to second
    data_type convert(data_type data,complex_unit_id d1,complex_unit_id d2,const basic_unit_source &bsrc) const {
        unit u1,u2;
        u1=search(d1);
        u2=search(d2);
        data=u1.convert_to_standard(data,bsrc);
        data=u2.convert_from_standard(data,bsrc);
        return data;
    }

    //OPERATORS
    //operator== (compares using ids of basic_units)
    bool operator==(const magnitude &mag2) const {
        if((*this).src==mag2.src) return true;
        else return false;
    }
    // operator!=
    bool operator!=(const magnitude &mag2) const {
        return !((*this)==mag2);
    }
    // operator=
    magnitude &operator=(const magnitude &mag2) {
        if(this!=&mag2) {
            (*this).name=mag2.name;
            (*this).src=mag2.src;
            (*this).standard_unit=mag2.standard_unit;
        }
        check();
        return (*this);
    }
    //I/O
    void write(ofstream &out) const {
        unsigned short siz=src.size();
        binary_write(name,out);
        binary_write(standard_unit,out);
        binary_write(siz,out);
        map<complex_unit_id,unit>::const_iterator it;
        for(it=src.begin(); it!=src.end(); it++) {
            binary_write((*it).first,out);
            ((*it).second).write(out);
        }
    }
    void read(ifstream &input) {
        pair<complex_unit_id,unit> p;
        binary_read(name,input);
        binary_read(standard_unit,input);
        unsigned short siz;
        binary_read(siz,input);
        src.clear();
        for(int i=0; i<siz; i++) {
            binary_read(p.first,input);
            (p.second).read(input);
            src.insert(p);
        }
    }
    void show(const basic_unit_source &bsrc,ostream &out=cout) const {
        out<<name<<"   (";
        map<complex_unit_id,unit>::const_iterator it;
        for(it=src.begin(); it!=src.end(); it++) {
            if(it!=src.begin()) out<<",";
            ((*it).second).show(bsrc,out);
        }
        out<<")   std:";
        (get_standard_unit()).show(bsrc,out);
    }

    void check(const basic_unit_source &src) const {
        //TODO:check standard unit!!
        check();
    }
private:
    /* void set_basic_unit(complex_unit_id id,const basic_unit_source &src) {
         if(is_unit(id)==true) {
             unit u;
             u=search(id);
             if(u.standard_unit(src)) standard_unit=id;
         }
     }*/
    void merge_basic_id(const multiset<basic_unit_id> &v,set<basic_unit_id> &result) const {
        multiset<basic_unit_id>::const_iterator it;
        for(it=v.begin(); it!=v.end(); it++) result.insert(*it);
    }
    //search the next "free" id
    complex_unit_id next_id() const {
        complex_unit_id id;
        id=size()+1;
        return id;
    }
    /*   bool set_standard_unit(basic_unit_source basic_src) {
           bool b=false;
           map<complex_unit_id,unit>::iterator it;
           for(it=src.begin(); it!=src.end() && b==false; it++) {
               if(((*it).second).standard_unit(basic_src)==true) {
                   b=true;
                   standard_unit=(*it).first;
               }
           }
       }*/

    void check() const {
        if(name.empty()) error_report(warning_check,"magnitude with no name",1,1);
        if((is_unit(standard_unit)==false || standard_unit==0) && src.empty()==false) error_report(warning_check,"magnitude with no standard_unit",1,1);
        map<complex_unit_id,unit>::const_iterator it1,it2;
        bool b=true;
        bool b2=true;
        string s1,s2;
        for(it1=src.begin(); it1!=src.end() && (b==true || b2==true); it1++) {
            it2=it1;
            it2++;
            while(it2!=src.end() && (b==true || b2==true)) {
                if((*it2).second==(*it1).second) b=false;
                s1=((*it1).second).get_name();
                s2=((*it2).second).get_name();
                if(s1.empty()==false && s1==s2) b2=false;
                it2++;
            }
        }
        if(b==false) error_report(fatal_error,"repeated units in same magnitude",1,1);
        if(b2==false) error_report(class_error,"units with same name in magnitude",1,1);
        if(is_unit(0)==true) error_report("Fatal Error, unit in magnitude with id=0 (null)",1,1);
    }
};




