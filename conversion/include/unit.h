/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Unit Class
Version:0.4
*/
//This class stores an unit, with the needed operations to convert into the standard unit of his magnitude
//TODO: change vector<string> names for a set<string> names
class unit {
private:
    int id;
    vector<string> names;//the first 2 strings are the name and symbol of the unit used by the program
    operations conversion; //conversion to standard units
    int magid; //id of magnitude
public:
    //CONSTRUCTORS
    unit() {
    }
    unit(int id2, vector<string> &names2, operations &conv2,int magid2=0) {
        id=id2;
        names=names2;
        conversion=conv2;
        magid=magid2;
    }
    unit(string name2,string symbol2,int id2,operations &conv2,int magid2=0) {
        names.push_back(name2);
        names.push_back(symbol2);
        id=id2;
        conversion=conv2;
        magid=magid2;
    }
    unit(ifstream &input,int magid2,int unitid=0) { //Constructor from a binary input
        magid=magid2;
        read_unit(input,unitid);
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
    //convert n from one unit to another
    double convert_from(double n,unit &a) {
        n=a.standard_unit_value(n);
        n=value_from_standard_unit(n);
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
    //return the unit id
    int get_id() {
        return id;
    }
    void set_id(int id2) {
        id=id2;
    }
    //return the unit name
    string get_name(int i=-1) {
        if(i<0 || i>names.size()) return names[0];
        else return names[i];
    }
    //return the unit symbol
    string get_symbol() {
        return names[1];
    }
    //add a new name to names array
    void add_name(string nam) {
        names.push_back(nam);
    }
    //do binary write of unit
    void write_unit(ofstream &out) {
        //binary_write(magid,out);
        binary_write_vector(names,out); //Writes names string vector
        conversion.write_operations(out); //Writes conversion operations
    }
    void read_unit(ifstream &input,int i=0) {
        //binary_read(magid,input);
        id=i;
        binary_read_vector(names,input);
        conversion.read_operations(input);
    }
    bool have_name(string name) {
        bool b=false;
        int size=names.size();
        for(int i=0; i<size && b==false; i++) {
            if(names[i]==name) b=true;
        }
        return b;
    }
private:
    //operator <<, show the unit on the standard output
    friend ostream  &operator<< (ostream &out, const unit &uni) {
        out<<uni.id<<":"<<uni.names[0]<<"("<<uni.names[1]<<")"<<endl;
        out<<uni.conversion;
        //  write_vector(uni.names,out);
        return out;
    }
};
