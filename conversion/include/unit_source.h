/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Unit Source Class
Version:0.9.2
*/
#include "unit.h"

//##############################
//This class stores all the complex unit according to the basic_unit_source
class unit_source {
private:
    map<magnitude_id,magnitude> src; //magnitude source
    basic_unit_source basic_src; //basic_unit source
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
    //returns the id of magnitude with the name given, if it dont exists, creates new magnitude
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
    void set_magnitude_standard_unit(magnitude_id mid,complex_unit_id cuid) {
        map<magnitude_id,magnitude>::iterator it;
        it=src.find(mid);
        if(it==src.end()) error_report(warning_check,"searching for a non-existent id",1,0);
        else((*it).second).set_standard_unit(cuid);
    }
    //add basic unit (no complex version)
    basic_unit_id add_basic_unit(const basic_unit &bunit) {
        basic_unit_id bid;
        bid=basic_src.add(bunit);
        return bid;
    }
    //add unit to src and basic_src
    unit_id add_basic_unit(const basic_unit &bunit,magnitude_id magid) {
        basic_unit_id bid;
        unit_id resid;
        bid=basic_src.add(bunit); //the unit is added to basic source
        unit unit2(bid); //unit version of a basic_unit
        resid=add_unit(unit2,magid); //the unit is added to complex source
        return resid;
    }
    //add a complex unit
    unit_id add_unit(const unit &unit2,magnitude_id magid) {
        complex_unit_id uid=0;
        unit2.check(basic_src);
        map<magnitude_id,magnitude>::iterator it;
        it=src.find(magid);
        if(it!=src.end()) {
            uid=((*it).second).add_unit(unit2); //result of adding the unit in the magnitude
        }
        else {
            error_report(user_error,"magnitude of the unit not found",1,1);
        }
        unit_id u=make_pair(magid,uid);
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
    magnitude_id next_id() const {
        magnitude_id id;
        id=size()+1;
        return id;
    }
    vector<magnitude_id> get_magnitude_ids() const {
        map<magnitude_id,magnitude>::iterator it;
        vector<magnitude_id> v;
        for(it==src.begin(); it!=src.end(); it++) {
            v.push_back((*it).first);
        }
        return v;
    }
    unit search_unit(unit_id p) const {
        unit result;
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
        else error_report(warning_check,"searching for a non-existent id",1,0);
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
    string get_basic_unit_name(basic_unit_id bid) const {
        return basic_src.get_name(bid);
    }
    const basic_unit_source &get_basic_source() const {
        return basic_src;
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
    void show(ostream &out=cout) const {
        out<<"Basic Units"<<endl;
        basic_src.show(out);
        out<<endl<<"Magnitude List"<<endl;
        map<magnitude_id,magnitude>::const_iterator it; //source
        for(it=src.begin(); it!=src.end(); it++) {
            out<<(*it).first<<":";
            ((*it).second).show(basic_src,out);
            out<<endl;
        }
    }
    void check() {
        if(is_magnitude(0)==true) error_report(class_error,"magnitude with id=0",1,1);
        map<magnitude_id,magnitude>::iterator it;
        bool b=true;
        for(it=src.begin(); it!=src.end() && b; it++) {
            ((*it).second).check(basic_src);
        }
    }
private:

};
