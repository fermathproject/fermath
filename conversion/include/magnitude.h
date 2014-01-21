/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Class
Version:0.7
*/
#include "unit.h"
//This class stores a whole magnitude as a vector of units to search them and operate between them
class magnitude {
private:
    magnitude_id id;
    vector<string> names; //the first and second names are considered the principal name and symbol respectively
    vector<unit> units; //the first unit is considered the principal unit
public:
    //CONSTRUCTORS
    magnitude() {
    }
    magnitude(magnitude_id id2,const vector<string> &names2,const vector<unit> &units2) {
        id=id2;
        names=names2;
        units=units2;
        if(units[0].standard_unit()==false) {
            operations conv;
            units[0].set_conversion(conv);
            error_report("Error, unidad principal de magnitud con conversion no nula",0,1);
        }
        set_all_magnitude_id(); //all magnitude id of units are this magnitude
        check();
    }
    magnitude(string name2,string symbol,int id2,const vector<unit> &units2) {
        names.push_back(name2);
        names.push_back(symbol);
        id=id2;
        units=units2;
        if(units[0].standard_unit()==false) {
            operations conv;
            units[0].set_conversion(conv);
            error_report("Error, unidad principal de magnitud con conversion no nula",1,1);
        }
        set_all_magnitude_id(); //all magnitude id of units are this magnitude
        check();
    }
    magnitude(string name2,string symbol,int id2,const unit &unit2) {
        names.push_back(name2);
        names.push_back(symbol);
        id=id2;
        units.push_back(unit2);
        if(units[0].standard_unit()==false) {
            operations conv;
            units[0].set_conversion(conv);
            error_report("Error, unidad principal de magnitud con conversion no nula",1,1);
        }
        set_all_magnitude_id(); //all magnitude id of units are this magnitude
        check();
    }
    magnitude(ifstream &input,magnitude_id id2) {
        id=id2;
        read_magnitude(input);
    }
    //MODIFICATION
    //add a new unit to the magnitude (if it exist, it merge both units)
    void add_unit(unit unidad) {
        unidad.set_mag_id(id);
        int size=units.size();
        bool eq=false;
        for(int i=0; i<size; i++) {
            if(unidad==units[i]) {
                eq=true;
                units[i]=units[i]+unidad;
            }
        }
        if(eq==false) units.push_back(unidad);
        check();
    }
    //add a vector of units
    void add_units(const vector<unit> &units) {
        for(int i=0; i<units.size(); i++) add_unit(units[i]);
        check();
    }
    void add_name(string s) {
        bool add=true;
        for(int i=0; i<names.size() && add==true; i++) {
            if(s==names[i]) add=false;
        }
        if(add==true) names.push_back(s);
        check();
    }

    //ACCESS
    string get_name(int i=-1) const {
        if(i>=0 && i<names.size()) return names[i];
        else return names[0];
    }
    string get_symbol() const {
        return names[1];
    }
    //if the unit is in the magitude
    bool is_unit(unit &unidad) const {
        bool is=false;
        // int id2=unidad.get_id();
        for(int i=0; i<units.size() && is==false; i++) is=(unidad==units[i]);
        return is;
    }
    bool is_unit(string name) const {
        bool is=false;
        for(int i=0; i<units.size() && is==false; i++) is=units[i].have_name(name);
        return is;
    }
    //return the unit with the name given
    unit search_by_name(string name) const {
        int pos=-1;
        int size=units.size();
        for(int i=0; i<size && pos<0; i++) {
            if(units[i].have_name(name)) pos=i;
        }
        if(pos==-1) {
            pos=0;
            cout<<"ERROR, unit "<<name<<" not found in magnitude "<<names[0]<<endl;
            error_report("unit not found",1,1);
        }
        unit uni;
        uni=units[pos];
        return uni;
    }
    const unit &get_unit(int i=0) const {
        if(i<0 || i>units.size()) i=0;
        return units[i];
    }
    //How many units can be written
    unsigned short writable_units() const {
        unsigned short n=0;
        for(int i=0; i<units.size(); i++) {
            if(units[i].writable_unit()) n++;
        }
        return n;
    }
    bool have_name() const {
        if(names.size()>0) return true;
        else return false;
    }
    bool have_symbol() const { //symbol should be the second element of names
        if(names.size()>1) return true;
        else return false;
    }
    //READ/WRITE
    void write_magnitude(ofstream &out) const {
        binary_write_vector(names,out); //Writes names string vector
        unsigned short wrsize=writable_units();//units that will be written
        unsigned short size=units.size();//all units in magnitude
        binary_write(wrsize,out);//writes number of units that will be written
        for(unsigned short i=0; i<size; i++) {
            if(units[i].writable_unit()==true)   units[i].write_unit(out);
        }
    }

    void read_magnitude(ifstream &input) {
        unsigned short size;
        units.clear();
        binary_read_vector(names,input);
        binary_read(size,input);
        units.reserve(size);
        unit uni;
        for(unsigned short i=0; i<size; i++) {
            uni.read_unit(input,id); //reads units and assign magnitude id
            units.push_back(uni);
        }
        check();
    }

    //OPERATORS
    //operator==
    bool operator==(const magnitude &mag2) const { //check if id,principal unit and name are the same
        bool eq=true;
        if((*this).id!=mag2.id) eq=false; //check id
        else if((*this).units[0]!=mag2.units[0]) eq=false; //check pricipal unit
        //else if((*this).names[0]!=mag2.names[0]) eq=false; //check principal name
        return eq;
    }
    //operator !=
    bool operator!=(const magnitude &mag2) const {
        return !((*this)==mag2);
    }
    // operator=
    magnitude &operator=(const magnitude &mag2) {
        if(this!=&mag2) {
            (*this).names=mag2.names;
            (*this).id=mag2.id;
            (*this).units=mag2.units;
        }
        return *this;
    }
    //operator + (to unify two magnitudes in one, if they are the same unit)
    const magnitude operator+(const magnitude &other) const {
        magnitude result;
        result=(*this);
        if(result==other) { //if they are the same magnitude
            add_vector(result.names,other.names); //add one vector to another, if the names are not included
            int size=other.units.size();
            for(int i=0; i<size; i++) {
                result.add_unit(other.units[i]); //add all other units to result
            }
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
        out<<mag.id<<":"<<mag.names[0]<<"("<<mag.names[1]<<")"<<endl;
        int size=mag.units.size();
        for(int i=0; i<size; i++) {
            cout<<mag.units[i]<<endl;
        }
        return out;
    }
    //set all magnitude_id of the units in the magnitude
    void set_all_magnitude_id() {
        for(int i=0; i<units.size(); i++) units[i].set_mag_id(id);
    }
    void check() const {
        bool b=true;
        for(int i=0; i<units.size(); i++) {
            if(units[i].mag_id()!=id) b=false;
        }
        if(units[0].standard_unit()==false) b=false;
        if(b=false) error_report("Error in check_magnitude",1,1);
    }
};
