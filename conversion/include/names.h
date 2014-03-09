/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Class
Version:0.8
*/

#include"magnitude.h"
class names_list {
private:
    map<string,pair<magnitude_id,unit_id> > unit_names; //stores unit names
    map<string,magnitude_id> magnitude_names; //stores magnitudes names
    //map<string,operation_id>; //stores operations names
    const magnitude_db *mag_list;
public:
    names_list() {
    }
    names_list(map<string,pair<magnitude_id,unit_id> > u,map<string,magnitude_id> m,magnitude_db *ml=0) {
        unit_names=u;
        magnitude_names=m;
        mag_list=ml;
        check();
    }
    void add_unit_name(string n,unit_id uid,magnitude_id mid) {
        bool h=true;
        if(mag_list!=0) {
            h=mag_list->have_unit(uid,mid);
            if(h==false) error_report("Warning, unit id not found in list",1,1);
        }
        if(h==true) {
            pair<magnitude_id,unit_id> p;
            p.first=mid;
            p.second=uid;
            unit_names[n]=p;
        }
    }
    void add_magnitude_name(string n,magnitude_id mid) {
        bool h=true;
        if(mag_list!=0) {
            h=mag_list->have_magnitude(mid);
            if(h==false) error_report("Warning, magnitude id not found in list",1,1);
        }
        if(h==true) {
            magnitude_names[n]=mid;
        }
    }

    void set_magnitude_list(magnitude_db *mlist) {
        mag_list=mlist;
        check();
    }
    bool have_magnitude_db() const {
        if(mag_list==0) return false;
        else return true;
    }
    bool is_magnitude_name(string n) const {
        map<string,magnitude_id>::iterator it;
        it=magnitude_names.find(n);
        if(it==magnitude_names.end()) return false;
        else return true;
    }
    bool is_unit_name(string n) const {
        map<string,magnitude_id,unit_id>::iterator it;
        it=unit_names.find(n);
        if(it==unit_names.end()) return false;
        else return true;
    }
    magnitude_id get_magnitude_id(string n) const {
        magnitude_id mid=0;
        map<string,magnitude_id>::iterator it;
        it=magnitude_names.find(n);
        if(it==magnitude_names.end()) mid=0;
        else mid=it->second;
        return mid;
    }
    pair<magnitude_id,unit_id> get_unit_id(string n) const {
        pair<magnitude_id,unit_id> id;
        id.first=0;
        id.second=0;
        map<string,magnitude_id,unit_id>::iterator it;
        it=unit_names.find(n);
        if(it!=unit_names.end()) {
            id=it->second;
        }
        return id;
    }

    unit *search_unit(string n) const {
        unit *u=0;
        if(have_magnitude_db()) {
            pair<magnitude_id,unit_id> p=get_unit_id(n);
            u=mag_list->search_unit(p->second,p->first);
        }
        return u;
    }
    unit *search_magnitude(string n) const {
        unit *u=0;
        if(have_magnitude_db()) {
            magnitude_id mid=get_magnitude_id(n);
            u=mag_list->search_magnitude(mid);
        }
        return u;
    }

    //search for unit and magnitude

private:
    check() {
        /*      if(have_magnitude_db()){
              bool b=false;
              set<magnitude_id> vmid;
              set<unit_id> vid; //ids already checked
              unit_id uid;
              magnitude_id mid;
              map<string,magnitude_id>::iterator it1;
              map<string,magnitude_id,unit_id>::iterator it2;
              for(it1.magnitude_names.begind();it1!=magnitude_names.end() && b=false;it1++){
              mid=it->second;
              if(vmid.find(mid)==vmid.end()){ //if the id is not in the set


              }
              }
              }
          }

        */
    }

}



};
