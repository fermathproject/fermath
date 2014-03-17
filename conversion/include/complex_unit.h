/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Complex Unit Class, Magnitude Class & Complex Unit Source Class
Version:0.9
*/

#include "basic_unit.h"
typedef unsigned short magnitude_id; //id for difference between magnitude
typedef unsigned short complex_unit_id; //id for a complex unit in a magnitude
typedef pair<magnitude_id,complex_unit_id> unit_id; //full id needed for an unit (magnitude and complex_unit)
//This class works both, basic and complex unit as two vector of ids pointing to basic units
class complex_unit {
private:
    string name; //if the unit has another name different of basic units as default name (Newtons)
    multiset<basic_unit_id> avect;
    multiset<basic_unit_id> bvect; //the unit will be avect/bvect
public:
    complex_unit() {
    }
    //costructor for complex unit(with name)
    complex_unit(string name2,const multiset<basic_unit_id> &a,const multiset<basic_unit_id> &b,const basic_unit_source &src) {
        name=name2;
        avect=a;
        bvect=b;
        check(src);
    }
    //costructor for complex unit
    complex_unit(const multiset<basic_unit_id> &a,const multiset<basic_unit_id> &b,const basic_unit_source &src) {
        avect=a;
        bvect=b;
        check(src);
    }
    //constructor for simple unit
    complex_unit(basic_unit_id bid,const basic_unit_source &src) {
        avect.insert(bid);
        //TODO: checkings
        check(src);
    }
    complex_unit(const complex_unit &cunit2) {
        (*this)=cunit2;
    }

    //MODIFICATION
    //add the elements of unit2 to unit1
    void add_unit(const complex_unit &unit2) {
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
    //add the elements of unit2 to unit1, but in the different vectors (1/unit2)
    void add_inverse_unit(const complex_unit &unit2) {
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
    //TODO:void add_units(const vector<complex_unit> &v,const vector<complex_unit> &v)
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
    bool same_unit(const complex_unit &unit2) const {
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
    bool operator==(const complex_unit &unit2) const {
        if((*this).same_unit(unit2)==true) return true;
        else return false;
    }
    // operator!=
    bool operator!=(const complex_unit &unit2) const {
        return !((*this)==unit2);
    }
    // operator=
    complex_unit &operator=(const complex_unit &unit2) {
        if(this!=&unit2) {
            (*this).avect=unit2.avect;
            (*this).bvect=unit2.bvect;
            (*this).name=unit2.name;
        }
        check();
        return (*this);
    }

    //operator *
    //merge two units as the result of multiply both units
    const complex_unit operator*(const complex_unit &other) const {
        complex_unit result=(*this);
        result.add_unit(other);
        return result;
    }
    //operator /
    //merge two units as the resut of dividing both
    const complex_unit operator/(const complex_unit &other) const {
        complex_unit result=(*this);
        result.add_inverse_unit(other);
        return result;
    }
    bool check_with_basic(const basic_unit_source &src) const {
        int maxid=src.max_id();
        bool b=true;
        multiset<basic_unit_id>::iterator it;
        for(it=avect.begin(); it!=avect.end() && b==true; it++) {
            if((*it)>maxid) b=false;
        }
        for(it=bvect.begin(); it!=bvect.end() && b==true; it++) {
            if((*it)>maxid) b=false;
        }
        return b;
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
private:
    //operator <<, show the operations os the standard output
    /*   friend ostream  &operator<< (ostream &out, const complex_unit &unit2) {
           if(unit2.have_default_name()) out<<unit2.get_name();
           else if(unit2.is_null()==false) {
               multiset<basic_unit_id>::iterator it1;
               if((unit2.avect).size()==0) out<<"1";
               else {
                   for(it1=(unit2.avect).begin(); it1!=(unit2.avect).end(); it1++) out<<(unit2.src).get_name(*it1);
               }
               if((unit2.bvect).size()!=0) {
                   out<<"/";
                   for(it1=(unit2.bvect).begin(); it1!=(unit2.bvect).end(); it1++) out<<(unit2.src).get_name(*it1);
               }
           }
           return out;
       }*/
    //if there are repeated units in numerator and denominator, erases them
    void clean_units() {
        basic_unit_id a,b;
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

    void check(const basic_unit_source &src) const {
        if(is_complex() && product_conversion(src)==false) error_report("Warning, not product conversion in complex unit",1,1);
        int maxid=src.max_id();
        bool b=true;
        multiset<basic_unit_id>::iterator it;
        for(it=avect.begin(); it!=avect.end() && b==true; it++) {
            if((*it)>maxid) b=false;
        }
        for(it=bvect.begin(); it!=bvect.end() && b==true; it++) {
            if((*it)>maxid) b=false;
        }
        if(b==false) error_report("Error, basic units id dont exists",1,1);
    }
    void check() const {
        //if(is_complex() && product_conversion()==false) error_report("Warning, not product conversion in complex unit",1,1);
    }
};



//######################################################
class magnitude {
private:
    map<complex_unit_id,complex_unit> src;
    complex_unit_id standard_unit;
    string name; //standard name of magnitude
public:
    magnitude() {
        standard_unit=0;
    }

    magnitude(const string &name2,const map<complex_unit_id,complex_unit> &src2,complex_unit_id stdu) {
        src=src2;
        name=name2;
        standard_unit=stdu;
    }
    //constructor for a magnitude with his standard unit
    magnitude(const string &n2,const complex_unit &std,const basic_unit_source &src) {
        complex_unit_id id;
        id=add_unit(std);
        set_name(n2);
        standard_unit=0;
        set_basic_unit(id,src);
        check();
    }
    magnitude(const string &name2) {
        name=name2;
    }
    magnitude(const magnitude &m) {
        (*this)=m;
    }
    complex_unit_id add_unit(const complex_unit &u) {
        complex_unit_id id=0;
        if(is_unit(u)==false) {
            id=next_id();
            // if(u.standard_unit(src)==true) standard_unit==id;
            pair<complex_unit_id,complex_unit> p;
            p.first=id;
            p.second=u;
            src.insert(p);
        }
        check();
        return id;
    }

    //removes unit, warning!!
    /*  bool remove_unit(complex_unit_id id) {
          return src.erase(id);
      }*/

    void set_name(string n) {
        name=n;
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
    bool is_unit(const complex_unit &u) const {
        map<complex_unit_id,complex_unit>::const_iterator it;
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
        map<complex_unit_id,complex_unit>::const_iterator it;
        it=src.find(id);
        if(it==src.end()) return false;
        else return true;
    }

    complex_unit search(complex_unit_id id) const {
        complex_unit u;
        map<complex_unit_id,complex_unit>::const_iterator it;
        it=src.find(id);
        if(it!=src.end()) u=(*it).second;
        return u;
    }
    complex_unit get_standard_unit() const {
        return search(standard_unit);
    }
    //if is the same magnitude
    bool same_magnitude(const magnitude &mag2) const {
        complex_unit a,b;
        a=(*this).get_standard_unit();
        b=mag2.get_standard_unit();
        if(a==b) return true;
        else return false;
    }

    //JOBS
    //convert from first unit to second
    data_type convert(data_type data,complex_unit_id d1,complex_unit_id d2,const basic_unit_source &bsrc) const {
        complex_unit u1,u2;
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
            (*this).standard_unit==mag2.standard_unit;
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
        map<complex_unit_id,complex_unit>::const_iterator it;
        for(it=src.begin(); it!=src.end(); it++) {
            binary_write((*it).first,out);
            ((*it).second).write(out);
        }
    }

    void read(ifstream &input) {
        pair<complex_unit_id,complex_unit> p;
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

    /*        //operator + //TODO:maybe impossible to do this way
           	//merge two magnitude
               const magnitude operator+(const magnitude &other) const {
               magnitude result(*this);
               if(result.same_magnitude(other)){
              map<complex_unit_id,complex_unit>::iterator it1,it2;
              for(it1=other.begin();it1!=other.end();it1++){
               if(is_unit(it1.second)==false){
                   result.add_unit(other);
                   }
                   }
                   }
                   else error_report("Error, impossible to merge different magnitudes",1,1);
                   return result;
               }*/
private:
    void set_basic_unit(complex_unit_id id,const basic_unit_source &src) {
        if(is_unit(id)==true) {
            complex_unit u;
            u=search(id);
            if(u.standard_unit(src)) standard_unit=id;
        }
    }
    //search the next "free" id
    complex_unit_id next_id() const {
        complex_unit_id id;
        id=size()+1;
        return id;
    }
    bool set_standard_unit(basic_unit_source basic_src) {
        bool b=false;
        map<complex_unit_id,complex_unit>::iterator it;
        for(it=src.begin(); it!=src.end() && b==false; it++) {
            if(((*it).second).standard_unit(basic_src)==true) {
                b=true;
                standard_unit=(*it).first;
            }
        }
    }
    void check() {
        //TODO:only one standard unit
        if(name.empty()) error_report("Warning, magnitude with no name",1,1);
        if(is_unit(standard_unit)==false) error_report("Warning, magnitude with no standard_unit",1,1);
        map<complex_unit_id,complex_unit>::iterator it1,it2;
        bool b=true;
        string s1,s2;
        for(it1=src.begin(); it1!=src.end() && b==true; it1++) {
            it2=it1;
            it2++;
            while(it2!=src.end() && b==true) {
                if((*it2).second==(*it1).second) b=false;
                s1=((*it1).second).get_name();
                s2=((*it2).second).get_name();
                if(s1.empty()==false && s1==s2) b=false;
            }
        }
        if(b==false) error_report("Fatal Error, same units or units with same names in same magnitude",1,1);
        if(is_unit(0)==true) error_report("Fatal Error, unit in magnitude with id=0 (null)",1,1);
    }
};



//##############################
//This class stores all the complex unit according to the basic_unit_source
class unit_source {
private:
    map<magnitude_id,magnitude> src; //source
    basic_unit_source basic_src; //basic_source
public:
    //CONSTRUCTORS
    unit_source() {
    }
    unit_source(const map<magnitude_id,magnitude> &src2,basic_unit_source bsrc2) {
        src=src2;
        set_basic_source(bsrc2);
        check();
    }

    //MODIFICATION
    void set_basic_source(basic_unit_source bsrc2) {
        basic_src=bsrc2;
    }
    magnitude_id add_magnitude(const magnitude &mag) {
        string n1=mag.get_name();
        magnitude_id res;
        res=search_magnitude_id(n1);
        if(res==0) {
            res=next_id(); //obtains magnitude id
            pair<magnitude_id,magnitude> p;
            p.first=res;
            p.second=mag;
            src.insert(p);
        }
        return res;
    }
    //add unit to src and basic_src
    unit_id add_basic_unit(const basic_unit &bunit,magnitude_id magid) {
        basic_unit_id bid;
        unit_id resid;
        bid=basic_src.add(bunit); //the unit is added to basic source
        complex_unit unit2(bid,basic_src); //complex_unit version of a basic_unit
        resid=add_complex_unit(unit2,magid); //the unit is added to complex source
        return resid;
    }
    //add a complex unit
    unit_id add_complex_unit(const complex_unit &unit2,magnitude_id magid) {
        complex_unit_id uid=0;
        if(unit2.check_with_basic(basic_src)==false) error_report("Error,complex_unit with non-exstent basic ids",1,1);
        else {
            map<magnitude_id,magnitude>::iterator it;
            it=src.find(magid);
            if(it!=src.end()) {
                uid=(*it).second.add_unit(unit2); //result of adding the unit in the magnitude
            }
            else {
                error_report("Error,magnitude of the unit not found",1,1);
            }
        }
        unit_id u;
        u.first=magid;
        u.second=uid;
        return u;
    }
    void clear() {
        basic_src.clear();
        src.clear();
    }
    //ACCESS
    bool is_unit(unit_id p) const {
        if(is_magnitude(p.first)==false) return false;
        else {
            magnitude m=search_magnitude(p.first);
            bool b=m.is_unit(p.second);
            return b;
        }
    }
    unsigned int size()const {
        return src.size();
    }
    magnitude_id next_id() {
        magnitude_id id;
        id=size()+1;
        return id;
    }
    complex_unit search_unit(unit_id p) const {
        complex_unit result;
        magnitude m=search_magnitude(p.first);
        result=m.search(p.second);
        return result;
    }

    bool is_magnitude(magnitude_id id) const {
        map<magnitude_id,magnitude>::const_iterator it;
        it=src.find(id);
        if(it!=src.end()) return true;
        else return false;
    }

    magnitude search_magnitude(magnitude_id id) const {
        magnitude u;
        map<magnitude_id,magnitude>::const_iterator it;
        it=src.find(id);
        if(it!=src.end()) u=(*it).second;
        else error_report("Warning, searching for a non-existent id",1,1);
        return u;
    }
    magnitude_id search_magnitude_id(string n) const {
        map<magnitude_id,magnitude>::const_iterator it;
        magnitude_id res=0;
        bool found=false;
        for(it=src.begin(); it!=src.end() && !found; it++) {
            if(((*it).second).get_name()==n) {
                found=true;
                res=(*it).first;
            }
        }
        return res;
    }
    string get_magnitude_name(magnitude_id id) const {
        string result;
        result=(search_magnitude(id)).get_name();
        return result;
    }

    //I/O
    void write(ofstream &out) const {
        unsigned short siz=src.size();
        map<magnitude_id,magnitude>::const_iterator it;
        basic_src.write(out);
        binary_write(siz,out);
        for(it=src.begin(); it!=src.end(); it++) {
            binary_write((*it).first,out);
            ((*it).second).write(out);
        }
    }

    void read(ifstream &input) {
        clear();
        unsigned short siz;
        pair<magnitude_id,magnitude> p;
        basic_src.read(input);
        binary_read(siz,input);
        for(int i=0; i<siz; i++) {
            binary_read(p.first,input);
            (p.second).read(input);
            src.insert(p);
        }
    }
private:
    void check() {
        if(is_magnitude(0)==true) error_report("Error, magnitude with id=0",1,1);
        //int maxid=bsrc.max_id();
        map<magnitude_id,magnitude>::iterator it;
        bool b=true;
        for(it=src.begin(); it!=src.end() && b; it++) {
            //    ((*it).second).check();
        }
    }
};


//FUNCTIONS
bool same_magnitude(unit_id id1,unit_id id2) {
    return (id1.first==id2.first);
}
bool same_magnitude(unit_id id1,magnitude_id id2) {
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
bool is_null(unit_id id) {
    if(id.first==0 && id.second==0) return true;
    else return false;
}
