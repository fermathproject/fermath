/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project: Unit Class, Magnitude Class
Version:0.9.2
*/

#include "basic_unit.h"
typedef unsigned short magnitude_id; //id for difference between magnitude
typedef unsigned short complex_unit_id; //id for a complex unit in a magnitude
typedef pair<magnitude_id,complex_unit_id> unit_id; //full id needed for an unit (magnitude and unit)
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
unit_id set_unit_id(complex_unit_id uid, magnitude_id newid) {
    unit_id result;
    result.first=newid;
    result.second=uid;
    return result;
}
bool is_null_id(unit_id id) {
    if(id.first==0 && id.second==0) return true;
    else return false;
}
void clear_unit_id(unit_id &id) {
    id.first=0;
    id.second=0;
}
//****************

//This class works both, basic and complex unit as two vector of ids pointing to basic units
class unit {
private:
    string name; //if the unit has another name different of basic units as default name (Newtons)
    multiset<basic_unit_id> avect;
    multiset<basic_unit_id> bvect; //the unit will be avect/bvect
public:
    unit() {
    }
    //costructor for complex unit(with name)
    unit(string name2,const multiset<basic_unit_id> &a,const multiset<basic_unit_id> &b) {
        name=name2;
        avect=a;
        bvect=b;
        check();
    }
    //costructor for complex unit
    unit(const multiset<basic_unit_id> &a,const multiset<basic_unit_id> &b) {
        avect=a;
        bvect=b;
        check();
    }
    //constructor for simple unit
    unit(basic_unit_id bid) {
        avect.insert(bid);
    }
    unit(const string &n) {
        set_name(n);
    }
    unit(const unit &cunit2) {
        (*this)=cunit2;
    }

    //MODIFICATION
    //add the elements of unit2 to unit1 (WARNING: this dont check if units are the same magnitude (g*kg)
    void add_unit(const unit &unit2) {
        multiset<basic_unit_id>::iterator it1,it2;
        it1=(unit2.avect).begin();
        it2=(unit2.avect).end();
        avect.insert(it1,it2);
        it1=(unit2.bvect).begin();
        it2=(unit2.bvect).end();
        bvect.insert(it1,it2);
        clean_units();
        check();
    }
    //add the elements of unit2 to unit1, but in the different vectors (1/unit2) (WARNING: this dont check if units are the same magnitude (g*kg)
    void add_inverse_unit(const unit &unit2) {
        multiset<basic_unit_id>::iterator it1,it2;
        it1=(unit2.avect).begin();
        it2=(unit2.avect).end();
        bvect.insert(it1,it2); //unit2.avect --> bvect
        it1=(unit2.bvect).begin();
        it2=(unit2.bvect).end();
        avect.insert(it1,it2);
        clean_units();
        check();
    }
    //adds the basic units to he complex unit
    void add_basic_units(const multiset<basic_unit_id> &avect2,const multiset<basic_unit_id>  &bvect2) {
        multiset<basic_unit_id>::iterator it1,it2;
        it1=avect2.begin();
        it2=avect2.end();
        avect.insert(it1,it2);
        it1=bvect2.begin();
        it2=bvect2.end();
        bvect.insert(it1,it2);
        clean_units();
        check();
    }

    void clear() {
        avect.clear();
        bvect.clear();
        name.clear();
    }
    void set_name(string n) {
        name=n;
    }

    //ACCESS
    string get_name() const {
        return name;
    }
    bool have_default_name() const {
        return !(name.empty());
    }
    bool is_basic() const {
        if(avect.size()==1 && bvect.size()==0) return true;
        else return false;
    }
    bool is_complex() const {
        return !(is_basic());
    }
    bool is_null() const {
        if(avect.size()==0 && bvect.size()==0) return true;
        else return false;
    }
    //compares two units using the basic_units ids
    bool same_unit(const unit &unit2) const {
        if((*this).avect==unit2.avect && (*this).bvect==unit2.bvect) return true;
        else return false;
    }
    //if all basic units are null_conversion, it is standard unit
    bool standard_unit(const basic_unit_source &src) const {
        bool b=false;
        if(is_null()==false) b=true;
        multiset<basic_unit_id>::iterator it1;
        for(it1=avect.begin(); it1!=avect.end() && b!=false; it1++) {
            if(src.standard_unit(*it1)==false) b=false;
        }
        for(it1=bvect.begin(); it1!=bvect.end() && b!=false; it1++) {
            if(src.standard_unit(*it1)==false) b=false;
        }
        return b;
    }
    pair< multiset<basic_unit_id>,multiset<basic_unit_id> > get_basic_units() const {
        pair< multiset<basic_unit_id>,multiset<basic_unit_id> > p;
        p.first=avect;
        p.second=bvect;
        return p;
    }
    pair<unsigned int,unsigned int> get_basic_units_size() const {
        pair<unsigned int,unsigned int> p;
        p.first=avect.size();
        p.second=bvect.size();
        return p;
    }

    //JOBS
    //conversion to a standard unit
    data_type convert_to_standard(data_type d1,const basic_unit_source &src) const {
        multiset<basic_unit_id>::iterator it1;
        for(it1=avect.begin(); it1!=avect.end(); it1++) d1=src.convert(d1,*it1); //numerator
        for(it1=bvect.begin(); it1!=bvect.end(); it1++) d1=src.inverse_convert(d1,*it1); //denominator
        return d1;
    }
    //conversion from the standard unit
    data_type convert_from_standard(data_type d1,const basic_unit_source &src) const {
        multiset<basic_unit_id>::iterator it1;
        for(it1=avect.begin(); it1!=avect.end(); it1++) d1=src.inverse_convert(d1,*it1); //numerator
        for(it1=bvect.begin(); it1!=bvect.end(); it1++) d1=src.convert(d1,*it1); //denominator
        return d1;
    }
    //OPERATORS
    //operator== (compares using ids of basic_unts)
    bool operator==(const unit &unit2) const {
        if((*this).same_unit(unit2)==true) return true;
        else return false;
    }
    // operator!=
    bool operator!=(const unit &unit2) const {
        return !((*this)==unit2);
    }
    // operator=
    unit &operator=(const unit &unit2) {
        if(this!=&unit2) {
            (*this).avect=unit2.avect;
            (*this).bvect=unit2.bvect;
            (*this).name=unit2.name;
        }
        check();
        return (*this);
    }
    //I/O
    void write(ofstream &out) const {
        string name; //if the unit has another name different of basic units as default name (Newtons)
        multiset<basic_unit_id>::iterator it;
        unsigned short siz1=avect.size(),siz2=bvect.size();
        binary_write(name,out); //write name
        binary_write(siz1,out);
        for(it=avect.begin(); it!=avect.end(); it++) { //writes avect
            binary_write(*it,out);
        }
        binary_write(siz2,out);
        for(it=bvect.begin(); it!=bvect.end(); it++) {//writes bvect
            binary_write(*it,out);
        }
    }
    void read(ifstream &input) {
        unsigned short siz;
        basic_unit_id id;
        string n;
        binary_read(n,input);
        name=n;
        binary_read(siz,input);
        avect.clear();
        for(int i=0; i<siz; i++) {
            binary_read(id,input);
            avect.insert(id);
        }
        binary_read(siz,input);
        bvect.clear();
        for(int i=0; i<siz; i++) {
            binary_read(id,input);
            bvect.insert(id);
        }
    }
    void show(const basic_unit_source &src,ostream &out=cout) const {
        if(have_default_name()) out<<name<<"   ";
        else if(is_null()==false) {
            multiset<basic_unit_id>::iterator it;
            if(avect.size()==0) out<<"1";
            else {
                for(it=avect.begin(); it!=avect.end(); it++) out<<src.get_name(*it);
            }
            if(bvect.size()!=0) {
                out<<"/";
                for(it=bvect.begin(); it!=bvect.end(); it++) out<<src.get_name(*it);
            }
        }
    }

    void check(const basic_unit_source &src) const {
        if(is_complex() && product_conversion(src)==false) error_report(warning_check,"not product conversion in complex unit",1,1);
        int maxid=src.max_id();
        bool b=true;
        multiset<basic_unit_id>::const_iterator it;
        for(it=avect.begin(); it!=avect.end() && b==true; it++) {
            if((*it)>maxid) b=false;
        }
        for(it=bvect.begin(); it!=bvect.end() && b==true; it++) {
            if((*it)>maxid) b=false;
        }
        if(b==false) error_report(error_check,"basic units id dont exists",1,1);
        check();
    }
private:
    //if there are repeated units in numerator and denominator, erases them
    void clean_units() {
        multiset<basic_unit_id>::iterator it1=avect.begin();
        multiset<basic_unit_id>::iterator it2=bvect.begin();
        multiset<basic_unit_id>::iterator it3;
        while(it1!=avect.end() && it2!=bvect.end()) {
            if((*it1)==(*it2)) { //if equal, removes elements (erase includes "it++")
                it3=it1;
                it1++;
                avect.erase(it3);
                it3=it2;
                it2++;
                bvect.erase(it3);
            }
            else if((*it1)>(*it2)) {
                it1++;
            }
            else {
                it2++;
            }
        }
    }
    //if all basic units are converted using products
    bool product_conversion(const basic_unit_source &src) const {
        bool p=true;
        multiset<basic_unit_id>::iterator it1;
        for(it1=avect.begin(); it1!=avect.end() && p!=false; it1++) {
            if(src.product_conversion(*it1)==false) p=false;
        }
        for(it1=bvect.begin(); it1!=bvect.end() && p!=false; it1++) {
            if(src.product_conversion(*it1)==false) p=false;
        }
        return p;
    }
    void check() const {
        bool found=false;
        multiset<basic_unit_id>::const_iterator it1,it2;
        for(it1=avect.begin(); it1!=avect.end() && found==false; it1++) {
            for(it2=bvect.begin(); it2!=bvect.end() && found==false; it2++) {
                if((*it1)==(*it2)) found=true;
            }
        }
        if(found==true) error_report(class_error,"basic units repeated in unit vectors",1,0);
    }
};



//######################################################
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
    //TODO:merge magnitudes!!!

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




