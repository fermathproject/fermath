/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Unit Class
Version:0.1
*/
class unit {
private:
    int id;
    string name;
    string symbol;
    vector<string> names;
    conversion conv; //conversion to standard units
    int magid; //id of magnitude (TO DO)
public:
    //CONSTRUCTORS
    unit() {
    }
    unit(string name2,string symbol2,int id2, vector<string> &names2, conversion &conv2,int magid2=0) {
        name=name2;
        symbol=symbol2;
        id=id2;
        names=names2;
        conv=conv2;
        magid=magid2;
    }
    unit(string name2,string symbol2,int id2,conversion &conv2,int magid2=0) {
        name=name2;
        symbol2=symbol;
        id=id2;
        conv=conv2;
        magid=magid2;
    }

    //convert the unit to the standard unit of magnitude
    double standard_unit_value(double n) {
        n=conv.convert(n);
        return n;
    }
    //convert the standard unit to this unit
    double value_from_standard_unit(double n) {
        n=conv.inverse_convert(n);
        return n;
    }
    //return true if this is the standard unit of magnitude
    bool standard_unit() {
        return conv.null_conversion();
    }
    //return the id of magnitude
    int mag_id() {
        return magid;
    }
    //set the id of magnitude
    void set_mag_id(int m) {
        magid=m;
    }
};
