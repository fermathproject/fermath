/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Class
Version:0.1
*/
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
    void add_unit(unit &unidad) {
        unidad.set_mag_id(id);
        units.push_back(unidad);
    }

};
