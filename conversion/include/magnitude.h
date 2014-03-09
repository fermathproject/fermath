/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Class
Version:0.8
*/
#include "unit.h"
//This class stores a whole magnitude as a vector of units to search them and operate between them
class magnitude {
private:
    magnitude_id id;
    string name;
    string symbol;
    unit punit;	//principal unit
    set<unit> units;
public:
    //CONSTRUCTORS
    magnitude() {
    }
    magnitude(magnitude_id id2,const string &name2,const string &symbol2,const unit &u,const set<unit> &units2) {
        id=id2;
        name=name2;
        symbol=symbol2;
        punit=u;
        if(punit.standard_unit()==false) {
            punit.erase_conversion();
            error_report("WARNING, unidad principal de magnitud con conversion no nula",0,1);
        }
        set_all_magnitude_id(); //all magnitude id of units are this magnitude
        check();
    }
    magnitude(magnitude_id id2,string name2,string symbol2,const unit &unit2) {
        name=name2;
        symbol=symbol2;
        id=id2;
        punit=unit2;
        if(punit.standard_unit()==false) {
            punit.erase_conversion();
            error_report("Warning, unidad principal de magnitud con conversion no nula",0,1);
        }
        set_all_magnitude_id(); //all magnitude id of units are this magnitude
        check();
    }
    magnitude(ifstream &input,magnitude_id id2) {
        id=id2;
        read_magnitude(input);
    }
    magnitude(const magnitude &mag) {
        (*this)=mag;
    }
    //MODIFICATION
    void set_principal_unit(const unit &unidad) {
        punit=unidad;
        punit.set_mag_id(id);
        if(punit.standard_unit()==false) {
            punit.erase_conversion();
            error_report("Warning, unidad principal de magnitud con conversion no nula",0,1);
        }
    }

    void set_name(const string &s) {
        name=s;
    }
    void set_symbol(const string &s) {
        symbol=s;
    }
    void set_id(magnitude_id id2) {
        id=id2;
        set_all_magnitude_id();
    }
    void erase_unit(const unit &u) {
        units.erase(u);
    }
    //add a new unit to the magnitude if dont exist
    void add_unit(unit unidad) {
        if(unidad.standard_unit()==false) {
            unidad.set_mag_id(id);
            units.insert(unidad);
            check();
        }
    }
    //add a vector of units
    void add_units(const vector<unit> &units) {
        for(int i=0; i<units.size(); i++) add_unit(units[i]);
        check();
    }

    //ACCESS
    string get_name() const {
        return name;
    }
    string get_symbol() const {
        return symbol;
    }
    magnitude_id get_id() const {
        return id;
    }

    //if the unit is in the magitude (using id)
    bool is_unit(const unit &unidad) const {
        if(unidad==punit) return true;
        else {
            set<unit>::iterator it;
            it=units.find(unidad);
            if(it==units.end()) return true;
            else return false;
        }
    }
    bool is_unit(unit_id id2) {
        unit u2;
        u2.set_id(id2);
        return is_unit(u2);
    }

    /*unit search(const unit &u2) {
        set<unit>::iterator it;
        it=units.find(u2);
        if(it==units.end()){
         error_report("Error,Unit not found",1,1);
         return u2;
         }
        return *it;
    }*/
    unit *search(unit_id id) {
        unit u;
        u.set_id(id);
        set<unit>::iterator it;
        it=units.find(u);
        if(it==units.end()) {
            error_report("Error,Unit not found",1,1);
            return u;
        }
        else return &(*it);
    }
    //How many units can be written
    unsigned int writable_units() const {
        unsigned int n=0;
        set<unit>::iterator it;
        if(punit.writable_unit()==true) n++;
        for(it=units.begin(); it!=units.end(); it++) {
            if((*it).writable_unit()==true) n++;
        }
        return n;
    }
    void show_magnitude(ostream &out=cout) {
        out<<id<<":"<<name<<"("<<symbol<<")"<<endl;
        set<unit>::iterator it;
        for(it=units.begin(); it!=units.end(); it++) {
            cout<<*it<<"  ";
        }
    }
    bool equal_units(const magnitude &mag) const {
        set<unit>::iterator it1,it2;
        bool b=true;
        for(it1==units.begin(); it1!=units.end() && b==true; it1++) {
            bool found=false;
            for(it2==mag.units.begin(); it2!=mag.units.end() && found==false; it2++) {
                if((*it1).same_unit(*it2)) found==true;
            }
            if(found==false) b=false;
        }
        return b;
    }


    //READ/WRITE
    void write_magnitude(ofstream &out) const {
        binary_write(name,out); //Writes names string vector
        binary_write(symbol,out);
        unsigned short wrsize=writable_units();//units that will be written
        binary_write(wrsize,out);//writes number of units that will be written
        if(punit.writable_unit()==true) punit.write_unit(out);
        set<unit>::iterator it;
        for(it=units.begin(); it!=units.end(); it++) {
            if((*it).writable_unit()==true)(*it).write_unit(out);
        }
    }

    void read_magnitude(ifstream &input) { //TODO
        /*   unsigned short size;
           units.clear();
           binary_read_vector(names,input);
           binary_read(size,input);
           units.reserve(size);
           unit uni;
           for(unsigned short i=0; i<size; i++) {
               uni.read_unit(input,id); //reads units and assign magnitude id
               units.push_back(uni);
           }
           check();*/
    }

    //OPERATORS
    //operator==
    bool operator==(const magnitude &mag2) const { //check if id,principal unit and ¿name? are the same (dont check all the units!!!)
        bool eq=true;
        if((*this).id!=mag2.id) eq=false; //check id
        else if(punit!=mag2.punit) eq=false; //check pricipal unit
        //  else if(name!=mag2.name || symbol!=mag2.symbol) eq=false; //check principal name and symbol
        return eq;
    }
    //operator <,> (compares id)
    bool operator<(const magnitude &mag2) const {
        if(id<mag2.id) return true;
        else return false;
    }
    bool operator>(const magnitude &mag2) const {
        if(id>mag2.id) return true;
        else return false;
    }
    //operator !=
    bool operator!=(const magnitude &mag2) const {
        return !((*this)==mag2);
    }
    // operator=
    magnitude &operator=(const magnitude &mag2) {
        if(this!=&mag2) {
            (*this).name=mag2.name;
            (*this).symbol=mag2.symbol;
            (*this).id=mag2.id;
            (*this).units=mag2.units;
            (*this).punit=mag2.punit;
        }
        return *this;
    }
    //operator + (to unify two magnitudes in one, if they are the same unit)
    const magnitude operator+(const magnitude &other) const {
        magnitude result;
        result=(*this);
        if(result==other) { //if they are the same magnitude
            result.merge_units(other.units);
        }
        else error_report("FATAL ERROR(add of non suitable units), please, contact support",1,1);
        return result;
    }
    //adds one unit
    const magnitude operator+(const unit &u) const {
        magnitude result;
        result=(*this);
        result.add_unit(u);
        return result;
    }

    //operator +=
    magnitude operator+=(const magnitude &mag) {
        (*this)=(*this)+mag;
        return *this;
    }
    //operator +=
    magnitude operator+=(const unit &u) {
        (*this)=(*this)+u;
        return *this;
    }
private:
    //operator <<, show the magnitude on the standard output
    friend ostream  &operator<< (ostream &out, const magnitude &mag) {
        out<<mag.name<<"("<<mag.symbol<<")"<<endl;
        return out;
    }
    //set all magnitude_id of the units in the magnitude
    void set_all_magnitude_id() {
        punit.set_mag_id(id);
        set<unit>::iterator it;
        for(it=units.begin(); it!=units.end(); it++) {
            //   it->set_mag_id(id); //dont work because in set are const elements (to keep order)
            const_cast<unit &>(*it).set_mag_id(id);
        }
    }
    void merge_units(const set<unit> &u2) {
        units.insert(u2.begin(),u2.end());
        set_all_magnitude_id();
        check();
    }
    void check() const {
        bool b=true;
        set<unit>::iterator it;
        if(punit.standard_unit()==false) b=false;
        for(it=units.begin(); it!=units.end(); it++) {
            if((*it).mag_id()!=id) b=false;
        }
        if(b=false) error_report("Error in check_magnitude",1,1);
    }
};



//##############################################



class magnitude_db {
private:
    set<magnitude> mag_list;

public:
    magnitude_db() {
    }
    magnitude_db(const set<magnitude> &m) {
        mag_list=m;
        check();
    }
    magnitude_db(const magnitude &m) {
        add_magnitude(m);
        check()
    }
    void add(const magnitude &m) {
        mag_list.insert(m);
        check()
    }
    void add(const set<magnitude> &m) {
        mag_list.insert(m.begin(),m.end());
        check()
    }
    void add(const vector<magnitude> &m) {
        for(int i=0; i<m.size(); i++)  add_magnitude(m);
        check()
    }
    void clear() {
        mag_list.clear();
    }
    bool erase(const magnitude &m) {
        int x;
        x=mag_list.erase(m);
        if(x>=1) return true;
        else if(x==0) return false;
    }


    bool empty() const {
        return mag_list.empty();
    }
    unsigned int size() const {
        return mag_list.size();
    }

    bool have_magnitude(magnitude_id id) const {
        magnitude m;
        m.set_id(id);
        set<magnitude>::iterator it;
        it=mag_list.find(m);
        if(it==mag_list.end()) return false;
        else return true;
    }
    magnitude *search_magnitude(magnitude_id id) const {
        magnitude x;
        x.set_id(id);
        set<magnitude>::iterator it;
        it=mag_list.find(x);
        if(it==mag_list.end()) {
            error_report("Warning, magnitude not found",1,1);
            return x;
        }
        else return &(*it);
    }

    bool have_unit(const unit_id id,magnitude_id magid) const {
        magnitude *m;
        if(have_magnitude(magid)==false) return false;
        else {
            m=search_magnitude(magid);
            return m->is_unit(id);
        }
    }

    unit *search_unit(unit_id id,magnitude_id magid)const {
        magnitude *m;
        unit *u=0;
        m=search_magnitude(magid);
        u=m->search(id);
        return u;
    }


private:
    void check() {
        //THING TO CHECK¿?
    }
};
