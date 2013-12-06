/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Class
Version:0.5
*/

//This class stores a whole magnitude as a vector of units to search them and operate between them
//TODO: change vector<string> names for a set<string> names
class magnitude {
private:
    int id;
    vector<string> names; //the first and second names are considered the principal name and symbol respectively
    vector<unit> units; //the first unit is considered the principal unit
public:
    //CONSTRUCTORS
    magnitude() {
    }
    magnitude(int id2,vector<string> names2,vector<unit> &units2) {
        id=id2;
        names=names2;
        units=units2;
        if(units[0].standard_unit()==false) {
            operations conv;
            units[0].set_conversion(conv);
            cout<<"Error, unidad principal de magnitud con conversion no nula";
        }
        set_all_magnitude_id(); //all magnitude id of units are this magnitude
    }
    magnitude(string name2,string symbol,int id2,vector<unit> &units2) {
        names.push_back(name2);
        names.push_back(symbol);
        id=id2;
        units=units2;
        if(units[0].standard_unit()==false) {
            operations conv;
            units[0].set_conversion(conv);
            cout<<"Error, unidad principal de magnitud con conversion no nula";
        }
        set_all_magnitude_id(); //all magnitude id of units are this magnitude
    }
    magnitude(string name2,string symbol,int id2,unit unit2) {
        names.push_back(name2);
        names.push_back(symbol);
        id=id2;
        units.push_back(unit2);
        if(units[0].standard_unit()==false) {
            operations conv;
            units[0].set_conversion(conv);
            cout<<"Error, unidad principal de magnitud con conversion no nula";
        }
        set_all_magnitude_id(); //all magnitude id of units are this magnitude
    }
    magnitude(ifstream &input,int id2) {
        id=id2;
        read_magnitude(input);
    }
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
    }
    //set all magnitude_id of the units in the magnitude
    void set_all_magnitude_id() {
        for(int i=0; i<units.size(); i++) units[i].set_mag_id(id);
    }
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
    //return a pointer to the unit with the name given
    unit *search_by_name(string name) {
        int pos=-1;
        int size=units.size();
        for(int i=0; i<size && pos<0; i++) {
            if(units[i].have_name(name)) pos=i;
        }
        if(pos==-1) {
            pos=0;
            cout<<"ERROR, unit "<<name<<" not found in magnitude "<<names[0]<<endl;
        }
        unit *uni;
        uni=&units[pos];
        return uni;
    }
    const unit &get_unit(int i=0) const {
        if(i<0 || i>units.size()) i=0;
        return units[i];
    }
    void write_magnitude(ofstream &out) {
        binary_write_vector(names,out); //Writes names string vector
        unsigned size=units.size();
        binary_write(size,out);
        for(unsigned i=0; i<size; i++) {
            units[i].write_unit(out);
        }
    }

    void read_magnitude(ifstream &input) {
        binary_read_vector(names,input);
        unsigned size;
        binary_read(size,input);
        units.clear();
        units.reserve(size);
        unit uni;
        for(unsigned i=0; i<size; i++) {
            uni.read_unit(input,id); //reads units and assign magnitude id
            units.push_back(uni);
        }
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
                result.add_unit(other.units[i]); //add all other units tho result
            }
        }
        else cout<<"FATAL ERROR(add of non suitable units), please, contact support\n";
        return result;
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
};
