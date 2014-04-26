/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project: Unit Class
Version:0.9.5
*/

#include "basic_unit.h"
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
        set_name(name2);
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
        name=format_string(n);
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
