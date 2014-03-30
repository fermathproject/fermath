/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Glossary Class
Version:0.9.2
*/

#include "unit_source.h"
//stores all the names of the units and magnitudes, returning the full id, also stores sets of the ids for control of added units
class glossary {
private:
    // set<magnitude_id> magnitude_list; //stores all the magnitude_ids in the glossary
    // set<unit_id> unit_list; //stores all the unit_ids in the glossary
    map<string,magnitude_id> magnitude_dic;
    map<string,unit_id > unit_dic;
public:
    //CONSTRUCTORS
    glossary() {
    }
    glossary(const map<string,magnitude_id> &mdic,const map<string,unit_id > &udic) {
        magnitude_dic=mdic;
        unit_dic=udic;
    }
    //MODIFICATION
    //add a bunch of names to the glossary (all of them from a magnitude)
    void add_names(magnitude_id mid,const vector<string> &names) {
        for(unsigned int i=0; i>names.size(); i++) {
            add_magnitude_name(mid,names[i]);
        }
        //  add_to_list(mid); //inserts the id in the list
    }
    //add a names from a unit
    void add_names(unit_id id,const vector<string> &names) {
        for(unsigned int i=0; i<names.size(); i++) {
            add_unit_name(id,names[i]);
        }
    }
    //add one name of the magnitude, return false if the unit exists and couldn be added
    void add_magnitude_name(magnitude_id mid,const string &name) {
        pair<string,magnitude_id> p;
        p.first=name;
        p.second=mid;
        magnitude_dic.insert(p);
    }
    void add_unit_name(unit_id uid,const string &name) {
        pair<string,unit_id> p;
        p.first=name;
        p.second=uid;
        unit_dic.insert(p);
        //  add_to_list(id); //inserts the id in the list
    }

    void clear() {
        //  magnitude_list.clear();
        // unit_list.clear();
        magnitude_dic.clear();
        unit_dic.clear();
    }
    //ACCESS
    magnitude_id search_magnitude(const string &name) const {
        magnitude_id mid=0;
        map<string,magnitude_id>::const_iterator it;
        it=magnitude_dic.find(name);
        if(it!=magnitude_dic.end()) mid=(*it).second;
        return mid;
    }
    unit_id search_unit(const string &name) const {
        unit_id uid;
        clear_unit_id(uid); //0 as default
        map<string,unit_id>::const_iterator it;
        it=unit_dic.find(name);
        if(it!=unit_dic.end()) uid=(*it).second;
        return uid;
    }
    //search all the names of unit
    vector<string> get_unit_names(unit_id id) const {
        vector<string> v;
        map<string,unit_id>::const_iterator it;
        for(it=unit_dic.begin(); it!=unit_dic.end(); it++) {
            if((*it).second==id) v.push_back((*it).first);
        }
        return v;
    }
    //search all the names of magnitude
    vector<string> get_magnitude_names(magnitude_id id) const {
        vector<string> v;
        map<string,magnitude_id>::const_iterator it;
        for(it=magnitude_dic.begin(); it!=magnitude_dic.end(); it++) {
            if((*it).second==id) v.push_back((*it).first);
        }
        return v;
    }

    //I/O
    void write(ofstream &out) const {
        unsigned short siz;
        map<string,magnitude_id>::const_iterator it1;
        map<string,unit_id>::const_iterator it2;
        siz=magnitude_dic.size();
        binary_write(siz,out);
        for(it1=magnitude_dic.begin(); it1!=magnitude_dic.end(); it1++) {
            binary_write((*it1).first,out);
            binary_write((*it1).second,out);
        }
        siz=unit_dic.size();
        binary_write(siz,out);
        for(it2=unit_dic.begin(); it2!=unit_dic.end(); it2++) {
            binary_write((*it2).first,out);
            binary_write((*it2).second,out);
        }
    }

    void read(ifstream &input) {
        clear();
        unsigned short siz;
        pair<string,magnitude_id> p1;
        pair<string,unit_id> p2;
        binary_read(siz,input);
        for(int i=0; i<siz; i++) {
            binary_read(p1.first,input);
            binary_read(p1.second,input);
            magnitude_dic.insert(p1);
        }
        binary_read(siz,input);
        for(int i=0; i<siz; i++) {
            binary_read(p2.first,input);
            binary_read(p2.second,input);
            unit_dic.insert(p2);
        }
    }
    void show(ostream &out=cout) const {
        out<<"Glossary"<<endl;
        map<string,magnitude_id>::const_iterator it1;
        map<string,unit_id>::const_iterator it2;
        out<<"magnitude"<<endl;
        for(it1=magnitude_dic.begin(); it1!=magnitude_dic.end(); it1++) {
            out<<(*it1).first<<" - "<<(*it1).second;;
            out<<endl;
        }
        out<<endl;
        out<<"unit"<<endl;
        unit_id uid;
        for(it2=unit_dic.begin(); it2!=unit_dic.end(); it2++) {
            uid=(*it2).second;
            out<<(*it2).first<<" - "<<uid.first<<","<<uid.second;
            out<<endl;
        }
    }
    void  check() {
        //TODO
    }
private:

    /*   string remove_magnitude_name(magnitude_id uid) {
           pair<string,magnitude_id> p;
           map<string,magnitude_id>::iterator it;
           it=magnitude_dic.find(uid);
           if(it!=magnitude_dic.end()) {
               p=*it;
               magnitude_dic.remove(it);
               return p.first;
           }
           else return "";
       }

       string remove_unit_name(unit_id uid) {
           pair<string,unit_id> p;
           map<string,unit_id>::iterator it;
           it=unit_dic.find(uid);
           if(it!=unit_dic.end()) {
               p=*it;
               unit_dic.remove(it);
               return p.first;
           }
           else return "";
       }*/
    /*    pair<string,unit_id> remove_unit_name(map<string,unit_id>::iterator it) {
            pair<string,unit_id> p;
            p=*it;
            unit_dic.remove(it);
            return p;
        }*/

    void remove_unit_name(const string &s) {
        map<string,unit_id>::iterator it;
        it=unit_dic.find(s);
        if(it!=unit_dic.end()) unit_dic.erase(s);
    }
    void remove_magnitude_name(const string &s) {
        map<string,magnitude_id>::iterator it;
        it=magnitude_dic.find(s);
        if(it!=magnitude_dic.end()) magnitude_dic.erase(s);
    }


};
