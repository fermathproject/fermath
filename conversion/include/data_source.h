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
    void merge(data_src &dat) {
        //TODO
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

    /*   //change the basic units of the multisets according to the magnitude of the basic units of the unit
    pair< multiset<basic_unit_id>,multiset<basic_unit_id> > change_basic_units(pair< multiset<basic_unit_id>,multiset<basic_unit_id> > p,const unit &u){
       pair< multiset<basic_unit_id>,multiset<basic_unit_id> >  p2=u.get_basic_units();
        set<basic_unit_id> bunits; //to stores all the basic units with no repeated units from u
        set<basic_unit_id>::iterator bit; //iterator to move along the set
       multiset<basic_unit_id>::iterator it1,it2;
       set<unit_id> cid;
       it1=(p2.first).begin();
       it2=(p2.first).end();
       bunits.insert(it1,it2);
       (p2.first).clear(); //clear first multiset
        it1=(p2.second).begin();
       it2=(p2.second).end();
       bunits.insert(it1,it2);
       (p2.second).clear();//clear second multiset
       //Transform the basic_unit_id set in unit_id set
    	unit_id  id2;
       for(bit=bunits.begin();bit!=bunits.end();bit++){
    	   id2=get_complex_unit_id(*bit);
    	   cid.insert(id2);
       }
       bunits.clear();


       for(it1=(p.first).begin();it1!=(p.first).end();it1++){



       }



    return p;
    }*/


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
