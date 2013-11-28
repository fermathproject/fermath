/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Class
Version:0.3
*/

//This class stores a whole magnitude as a vector of units to search them and operate between them
class magnitude {
private:
    int id;
    string name;
    string symbol;
    unit punit;
    vector<string> names;
    vector<unit> units;

public:
    //CONSTRUCTORS
    magnitude() {
    }
    magnitude(string name2,string symbol2,int id2,vector<string> names2,vector<unit> &units2,unit &punit2) {
        name=name2;
        symbol=symbol2;
        id=id2;
        names=names2;
        units=units2;
        punit=punit2;
    }
    magnitude(string name2,string symbol2,int id2,vector<unit> &units2,unit &punit2) {
        name=name2;
        symbol=symbol2;
        id=id2;
        units=units2;
        punit=punit2;
    }
    //add a new unit to the magnitude
    void add_unit(unit unidad) {
        unidad.set_mag_id(id);
        units.push_back(unidad);
    }
    //set all magnitude_id of the units in the magnitude
    void set_all_magnitude_id() {
        punit.set_mag_id(id);
        for(int i=0; i<units.size(); i++) units[i].set_mag_id(id);
    }
    string get_name(int i=-1) {
        if(i<0) return name;
        else return names.at(i);
    }
    string get_symbol() {
        return symbol;
    }
    //if the unit is in the magitude
    bool is_unit(unit &unidad) {
        int id2=unidad.get_id();
        bool is=(id2==punit.get_id());
        for(int i=0; i<units.size() && is==0; i++) is=(id2==units[i].get_id());
        return is;
    }

};
