/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Class
Version:0.4
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
    }
    magnitude(ifstream &input,int id2) {
        id=id2;
        read_magnitude(input);
    }
    //add a new unit to the magnitude
    void add_unit(unit unidad) {
        unidad.set_mag_id(id);
        units.push_back(unidad);
    }
    //set all magnitude_id of the units in the magnitude
    void set_all_magnitude_id() {
        for(int i=0; i<units.size(); i++) units[i].set_mag_id(id);
    }
    void set_all_units_id(int &id) {
        for(int i=0; i<units.size(); i++) {
            units[i].set_id(id++);
        }
    }
    string get_name(int i=-1) {
        if(i>=0 && i<names.size()) return names[i];
        else return names[0];
    }
    string get_symbol() {
        return names[1];
    }
    //if the unit is in the magitude
    bool is_unit(unit &unidad) {
        bool is=false;
        int id2=unidad.get_id();
        for(int i=0; i<units.size() && is==false; i++) is=(id2==units[i].get_id());
        return is;
    }
    bool is_unit(string name) {
        bool is=false;
        for(int i=0; i<units.size() && is==false; i++) is=units[i].have_name(name);
        return is;
    }
    //return the unit with the name given
    unit &search_by_name(string name) {
        int pos=-1;
        int size=units.size();
        for(int i=0; i<size && pos<0; i++) {
            if(units[i].have_name(name)) pos=i;
        }
        return units[pos];
    }
    unit &get_unit(int i=0) {
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
            uni.read_unit(input);
            units.push_back(uni);
        }
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
