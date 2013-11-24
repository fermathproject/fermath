/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Unit Class
Version:0.2
*/
class unit {
private:
    int id;
    string name;
    string symbol;
    vector<string> names;
    operations conversion; //conversion to standard units
    int magid; //id of magnitude (TO DO)
public:
    //CONSTRUCTORS
    unit() {
    }
    unit(string name2,string symbol2,int id2, vector<string> &names2, operations &conv2,int magid2=0) {
        name=name2;
        symbol=symbol2;
        id=id2;
        names=names2;
        conversion=conv2;
        magid=magid2;
    }
    unit(string name2,string symbol2,int id2,operations &conv2,int magid2=0) {
        name=name2;
        symbol2=symbol;
        id=id2;
        conversion=conv2;
        magid=magid2;
    }

    void set_conversion(operations &conv) {
        conversion=conv;
    }


    //returns the standard unit of magnitude from this unit value
    double standard_unit_value(double n) {
        n=conversion.operate(n);
        return n;
    }
    //returns the unit from a standard unit value
    double value_from_standard_unit(double n) {
        n=conversion.inverse_operate(n);
        return n;
    }
    //return true if this is the standard unit of magnitude
    bool standard_unit() {
        return conversion.null_operation();
    }
    //return the id of magnitude
    int mag_id() {
        return magid;
    }
    //set the id of magnitude
    void set_mag_id(int m) {
        magid=m;
    }
    int get_id() {
        return id;
    }
    string get_name(int i=-1) {
        if(i<0) return name;
        else return names.at(i);
    }
    string get_symbol() {
        return symbol;
    }
};
