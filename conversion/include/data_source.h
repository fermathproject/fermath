/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Data Source Class
Version:0.9.2
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
        magnitude m(n); //new magnitude name
        id=src.add_magnitude(m);//add magnitude and returns id
        add_names(id,v); //adds all names of magnitude to the glossary
        add_magnitude_name(id,n);//adds the principal name of magnitude (if it isnt in v)
        return id;
    }

    unit_id add_unit(const unit &u,magnitude_id id,vector<string> &v) {
        unit_id uid;
        uid=src.add_unit(u,id);
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
    //merge two different data_sources
    void merge(const data_src &dat) {     //TODO:test
        basic_unit_source  bus;
        bus=dat.get_basic_source(); //the basic unit source of dat
        vector<magnitude_id> midvect;
        midvect=(dat.src).get_magnitude_ids();
        magnitude_id mid1,mid2;
        for(unsigned int i=0; i<midvect.size(); i++) { //add all magnitudes
            vector<string> mnames;
            vector<complex_unit_id> cuid;
            magnitude m;
            mid1=midvect[i];
            m=get_magnitude(mid1); //get magnitude
            mnames=(dat.names).get_magnitude_names(mid1); //get all the names of the magnitude
            mid2=add_magnitude(m.get_name(),mnames); //creates new magnitude with names of original
            cuid=m.get_units_ids(); //gets the ids of units in magnitude
            for(unsigned int j=0; j<cuid.size(); j++) { //adds all units of magnitude (resolving problems with the basic units)
                unit u1,u2;
                u1=m.search(cuid[j]); //takes one unit from the magnitude
                u2.set_name(u1.get_name()); //u2 have the same name as u1
                pair< multiset<basic_unit_id>,multiset<basic_unit_id> > bunits;
                multiset<basic_unit_id>::const_iterator bunit_it;
                bunits=u1.get_basic_units(); //takes all the basic units
                //resolve and add every basic unit used in the unit
                multiset<basic_unit_id> v1,v2; //new basic units of u2
                for(bunit_it==(bunits.first).begin(); bunit_it!=(bunits.first).end(); bunit_it++) {
                    basic_unit_id buid1=(*bunit_it);
                    basic_unit_id buid2;
                    basic_unit bu;
                    bu=bus.get_basic_unit(buid1);
                    buid2=src.add_basic_unit(bu); //adds basic unit, buid2 is the new id
                    v1.insert(buid2);
                }
                for(bunit_it==(bunits.second).begin(); bunit_it!=(bunits.second).end(); bunit_it++) {
                    basic_unit_id buid1=(*bunit_it);
                    basic_unit_id buid2;
                    basic_unit bu;
                    bu=bus.get_basic_unit(buid1);
                    buid2=src.add_basic_unit(bu); //adds basic unit, buid2 is the new id
                    v2.insert(buid2);
                }
                u2.add_basic_units(v1,v2); //u2 is the unit with resolved basic_units_ids
                unit_id new_uid;
                vector<string> unames=(dat.names).get_unit_names(make_pair(mid1,cuid[j])); //get all the names of the magnitude
                new_uid=add_unit(u2,mid2,unames); //add the unit to the source
                if(cuid[j]==m.get_standard_unit_id()) { //set standard unit with new id
                    src.set_magnitude_standard_unit(mid2,new_uid.first);
                }
            }
        }
    }

    //ACCESS
    magnitude get_magnitude(string &n) const {
        magnitude m;
        magnitude_id mid=0;
        mid=get_magnitude_id(n);
        m=get_magnitude(mid);
        return m;
    }

    unit get_unit(string &n) const {
        unit u;
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

    unit get_unit(unit_id uid) const {
        unit u;
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
    //returns the id of the complex unit version of the basic unit
    unit_id get_complex_unit_id(const basic_unit_id uid) const {
        return get_unit_id(get_basic_unit_name(uid)); //search the unit with the name of the basic unit
    }
    const basic_unit_source &get_basic_source() const {
        return src.get_basic_source();
    }
    //check if two units are the same magnitude, if the size of avect and bevect is the same, and the magnitude of the basic unit is the same, the unit is the same magnitude
    bool same_magnitude(const unit &a,const unit &b) const {
        pair<unsigned int,unsigned int> siz1,siz2;
        siz1=a.get_basic_units_size();
        siz2=b.get_basic_units_size();
        if(siz1!=siz2) return false; //the size should be the same
        else {
            bool found=true;
            pair< multiset<basic_unit_id>,multiset<basic_unit_id> > p1,p2;
            p1=a.get_basic_units();
            p2=b.get_basic_units();
            multiset<basic_unit_id>::const_iterator it1,it2;
            it1=(p1.first).begin();
            it2=(p2.first).begin();
            //check the magnitude of avect
            while(found==true && it1!=(p1.first).end()) { //the size is the same, so no problem if dont compare it2
                if(same_magnitude(*it1,*it2)==false) found=false;
                it1++;
                it2++;
            }
            it1=(p1.second).begin();
            it2=(p2.second).begin();
            //check the magnitude of bvect
            while(b==true && it1!=(p1.second).end()) {
                if(same_magnitude(*it1,*it2)==false) found=false;
                it1++;
                it2++;
            }
            return found;
        }
    }
    bool same_magnitude(basic_unit_id bid1,basic_unit_id bid2) const {
        unit_id id1,id2;
        id1=get_complex_unit_id(bid1);
        id2=get_complex_unit_id(bid2);
        return same_magnitude_id(id1,id2);
    }

    void write(ofstream &out) const {
        names.write(out);
        src.write(out);
    }
    void read(ifstream &input) {
        clear();
        names.read(input);
        src.read(input);
    }
    void show(ostream &out=cout) {
        src.show(out);
        out<<endl;
        names.show(out);
    }
private:
    string get_basic_unit_name(basic_unit_id bid) const {
        return src.get_basic_unit_name(bid);
    }
    void check() {
        names.check();
        src.check();
    }
};
