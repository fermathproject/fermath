/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Unit Class
Version:0.7
*/
#include "operations.h"
//This class stores an unit, with the needed operations to conversionert into the standard unit of his magnitude
typedef unsigned short magnitude_id;
class unit {
private:
    vector<string> names;//the first 2 strings are the name and symbol of the unit used by the program
    vector<const unit *> num_unit;
    vector<const unit *> den_unit; //the unit is nummag/denmag
    operations conversion; //stores a conversion
    magnitude_id magid;


public:
    //CONSTRUCTORS
    unit() {
        magid=0;
    }
    unit(const vector<string> &names2,operations conversion2,const vector<const unit *> &num,const vector<const unit *> &den,magnitude_id id=0) {
        names=names2;
        num_unit=num;
        den_unit=den;
        magid=id;
        conversion=conversion2;
        clean_unit();
        check();
    }
    //constructor for complex unit
    unit(string name2,string symbol2,const vector<const unit *> &num,const vector<const unit *> &den,magnitude_id id=0) {
        names.push_back(name2);
        names.push_back(symbol2);
        num_unit=num;
        den_unit=den;
        magid=id;
        clean_unit();
        check();
    }
    //complex unit without name
    unit(const vector<const unit *> &num,const vector<const unit *> &den,magnitude_id id=0) {
        magid=id;
        num_unit=num;
        den_unit=den;
        clean_unit();
        check();
    }
    //constructor for a basic unit
    unit(string name2,string symbol2,const operations &conversion2,magnitude_id magid2=0) {
        names.push_back(name2);
        names.push_back(symbol2);
        conversion=conversion2;
        magid=magid2;
    }
    unit(ifstream &input,magnitude_id magid2=0) { //Constructor from a binary input
        read_unit(input,magid2);
    }

    unit(const unit &unit2) { //Copy constructor
        (*this)=unit2;
    }

    //MODIFICATION

    void set_conversion(operations &conversion2) {
        conversion=conversion2;
    }
    //set the id of magnitude
    void set_mag_id(unsigned short m) {
        magid=m;
    }
    //remove all conversion units
    void erase_conversion_units() {
        num_unit.clear();
        den_unit.clear();
    }
    //remove the conversion data
    void erase_conversion() {
        conversion.clear();
    }
    //clear the unit
    void clear() {
        names.clear();
        erase_conversion();
        erase_conversion_units();
        magid=0;
    }
    //add a new name to names array
    void add_name(string nam) {
        names.push_back(nam);
    }
    //ACCESS
    //return the id of magnitude
    magnitude_id mag_id() const {
        return magid;
    }
    //return the unit name
    string get_name(int i=-1) const {
        if(i<0 || i>names.size()) return names[0];
        else return names[i];
    }
    //returns all the names in a vector
    vector<string> get_names() const {
        return names;
    }
    //return the unit symbol
    string get_symbol() const {
        return names[1];
    }
    //returns the conversion
    operations get_conversion() const {
        return conversion;
    }
    //if the unit is a complex unit (formed by different units)
    bool complex_unit() const {
        if((num_unit.size()+den_unit.size())>0) return true;
        else return false;
    }
    //if the unit is a basic unit (denominator and numerator are empty)
    bool basic_unit() const {
        if(num_unit.empty() && den_unit.empty()) return true;
        else return false;
    }
    //if the unit has a conversion stored
    bool have_conversion() const {
        return !conversion.null_operation();
    }
    //return true if this is the standard unit of magnitude
    bool standard_unit() const {
        bool standard=conversion.null_operation();
        if(complex_unit()==true) {
            for(int i=0; i<den_unit.size(); i++) {
                if(den_unit[i]->standard_unit()==false) standard=false;
            }
            for(int i=0; i<num_unit.size(); i++) {
                if(num_unit[i]->standard_unit()==false) standard=false;
            }
            if(conversion.null_operation()==false) standard=false;
        }
        return standard;
    }
    //return true if unit has the name given
    bool have_name(string name) const {
        bool b=false;
        int size=names.size();
        for(int i=0; i<size && b==false; i++) {
            if(names[i]==name) b=true;
        }
        return b;
    }
    //return true if are the same magnitude
    bool same_magnitude(const unit &u) const {
        bool b=false;
        if(magid==u.mag_id()) b=true;
       //  if(magid==0 || u.mag_id()==0) b=true;
        if(b==false) {
            b=true;
            if(compare_vector_elements(den_unit,u.den_unit)==false) b=false;//TODO:check only magnitudes, not elements
            if(compare_vector_elements(num_unit,u.num_unit)==false) b=false;//FIXME
        }
        return b;
    }
    bool same_conversion(const unit &u) const {
        bool b=false;
        if(u.basic_unit() && (*this).basic_unit()) {
            if((*this).conversion==u.conversion) b=true;
        }
        else if(u.complex_unit() && (*this).complex_unit()) {
            if(compare_vector_elements(den_unit,u.den_unit)==false) b=false;
            if(compare_vector_elements(num_unit,u.num_unit)==false) b=false;
        }
        return b;
    }
    //returns true if the unit has information to be written
    bool writable_unit() const {
        //if(have_conversion()) return true;
        if(basic_unit()) return true;
        //else if(names.size()>0)return true;
        else return false;
    }
    bool null_unit() const {
        if(magid==0 && num_unit.empty() && den_unit.empty() && conversion.null_operation()) return true;
        else return false;
    }

    //CLASS JOBS
    //returns the standard unit of magnitude from this unit value
    double standard_unit_value(double n) const {
        if(have_conversion() || basic_unit()) n=conversion.operate(n); //if is basic or has conversion stored
        else { //try to conversionert using num/den vectors
            if(check_conversion()==false) error_report("ERROR, cant convert unit",1,1);
            for(int i=0; i<num_unit.size(); i++) n=num_unit[i]->standard_unit_value(n);
            for(int i=0; i<den_unit.size(); i++) n=den_unit[i]->value_from_standard_unit(n); //the unit is all products (checked) so it is possible to do the inverse operations when dividing
        }
        return n;
    }
    //returns the unit from a standard unit value
    double value_from_standard_unit(double n) const {
        if(have_conversion() || basic_unit()) n=conversion.inverse_operate(n); //if is basic or has conversion stored
        else { //try to conversionert using num/den vectors
            if(check_conversion()==false) error_report("ERROR, cant convert unit",1,1);
            for(int i=0; i<num_unit.size(); i++) n=num_unit[i]->value_from_standard_unit(n);
            for(int i=0; i<den_unit.size(); i++) n=den_unit[i]->standard_unit_value(n);
        }
        return n;
    }
    //conversionert n from one unit to another
    double convert_from(double n,unit &a) const {
        n=a.standard_unit_value(n);
        n=value_from_standard_unit(n);
        return n;
    }

    //READ/WRITE (TODO:read and write complex_units)?
    //do binary write of unit(if possible)
    bool write_unit(ofstream &out) const {
        bool wr;
        wr=writable_unit();
        if(wr==true) { //only writes the unit if it has real info
            bool complex;
            complex=complex_unit();
            binary_write(complex,out);
            binary_write_vector(names,out); //Writes names string vector
            conversion.write_operations(out); //Writes conversion operations
            if(complex==true) {
                error_report("Warning, trying to write complex unit",0,1);
                //TODO:write num/den
            }
        }
        return wr;
    }
    void read_unit(ifstream &input,unsigned short magid2=0) {
        bool complex;
        binary_read(complex,input);
        binary_read_vector(names,input);//read names
        conversion.read_operations(input);//read conversion data
        if(complex==true) {
            error_report("Warning, trying to read complex unit",0,1);
            //TODO:read num/den
        }
        magid=magid2;
        check();
    }

    //OPERATORS
    //operator==
    bool operator==(const unit &unit2) const { //check if the magnitude unit and the conversion data is the same
        bool eq=true;
        if((*this).same_magnitude(unit2)==false) eq=false;
        if((*this).same_conversion(unit2)==false) eq=false;
        return eq;
    }
    // operator!=
    bool operator!=(const unit &unit2) const {
        return !((*this)==unit2);
    }
    // operator=
    unit &operator=(const unit &unit2) {
        if(this!=&unit2) {
            (*this).names=unit2.names;
            (*this).magid=unit2.magid;
            (*this).conversion=unit2.conversion;
            (*this).num_unit=unit2.num_unit;
            (*this).den_unit=unit2.den_unit;
        }
        return *this;
    }
    //operator + (to unify two units in one, if they are the same unit)
    const unit operator+(const unit &other) const {
        unit result;
        result=(*this);
        if(result==other) { //if they are the same unit
            add_vector(result.names,other.names); //add one vector to another, if the names are not included
        }
        else error_report("FATAL ERROR(add of non suitable units), please, contact support",1,1);
        return result;
    }
    //operator *
    const unit operator*(const unit &other) const { //TODO:check (core dumped) FIXME
        unit result;
        result.add_numerator_unit((*this)); //result is the product of two units
        result.add_numerator_unit(other);
        result.convert_if_simple(); //if result only has one unit, it makes a simple unit again
        return result;
    }
    //operator /
    const unit operator/(const unit &other) const {
        unit result;
        result.add_numerator_unit((*this));
        result.add_denominator_unit(other);
        result.convert_if_simple(); //if result only has one unit, it makes a simple unit again
        return result;
    }
    //operator +=
    unit operator+=(const unit &u) {
        (*this)=(*this)+u;
        return *this;
    }
    //operator *=
    unit operator*=(const unit &u) {
        (*this)=(*this)*u;
        return *this;
    }
    //operator /=
    unit operator/=(const unit &u) {
        (*this)=(*this)/u;
        return *this;
    }

private:
    //operator <<, show the unit on the standard output
    friend ostream  &operator<< (ostream &out, const unit &uni) { //FIXME
        if(uni.names.size()>0) {
            //    out<<uni.names[0];
            if(uni.names.size()>1) out<<"("<<uni.names[1]<<")";
        }
        else if(uni.complex_unit()) {
            if(uni.num_unit.size()==0) out<<"1";
            else for(int i=0; i<uni.num_unit.size(); i++) {
                    out<<uni.num_unit[i]->get_symbol();
                }
            if(uni.den_unit.size()>0) {
                out<<"/";
                for(int i=0; i<uni.den_unit.size(); i++) {
                    out<<uni.den_unit[i]->get_symbol();
                }
            }
        }
        return out;
    }
    void clean_unit() {
        simplify_vectors(den_unit,num_unit);
        check();
    }

    //if the conversion can be used in complex units
    bool suitable_complex_conversion() const { //return if you can do a conversion in a unit based on this (for example m/s)
        return conversion.product_operation();
    }

    //converts a complex unit into a simple unit if it is possible
    void convert_if_simple() {
        if(den_unit.empty()==true && num_unit.size()==1)(*this)=*(num_unit[0]);
    }

    //add a unit, if it is not simple, add the conversion units, after this, clean the unit
    void add_numerator_unit(const unit &u) {
        conversion.clear();
        if(u.basic_unit()==true) {
            add_basic_unit(u,true); //if is a simple unit, add the unit
        }
        else {
            for(int i=0; i<(u.num_unit).size(); i++) add_basic_unit(*(u.num_unit[i]),true);//adds the numerator units
            for(int i=0; i<(u.den_unit).size(); i++) add_basic_unit(*(u.den_unit[i]),false);//adds the denominator units
        }
        clean_unit();//clean the unit (if there are repeated elements in num and den)
        check();
    }
    void add_denominator_unit(const unit &u) {
        conversion.clear();
        if(u.basic_unit()==true) add_basic_unit(u,false); //if is a simple unit,
        else {
            for(int i=0; i<(u.num_unit).size(); i++) add_basic_unit(*(u.num_unit[i]),false);//adds the numerator units
            for(int i=0; i<(u.den_unit).size(); i++) add_basic_unit(*(u.den_unit[i]),true);//adds the denominator units
        }
        clean_unit();//clean the unit (if there are repeated elements in num and den)
        check();
    }
    //adds a basic unit (if true in numerator, false denominator)
    void add_basic_unit(const unit &u,bool numerator=true) {
        const unit *p=&u;
        if(u.complex_unit()) error_report("FATAL ERROR: adding a not basic unit",0,1);
        if(numerator==true) {
            if(erase(den_unit,u)==false) { //try to erase the unit from denominator, if it exist
                num_unit.push_back(p);//if the unit is not the unit in denominator, adds unit in numerator
            }
        }
        else { //if the unit is added to denominator
            if(erase(num_unit,u)==false) {
                den_unit.push_back(p);
            }
        }
    }
    //check if the conversion can be made
    bool check_conversion() const {
        bool b=true;
        if(have_conversion()==false) { //checks if the unit can be converted with the units conversion
            for(int i=0; i<num_unit.size() && b; i++) {
                if(num_unit[i]->suitable_complex_conversion()==false) b=false;
            }
            for(int i=0; i<den_unit.size() && b; i++) {
                if(den_unit[i]->suitable_complex_conversion()==false) b=false;
            }
        }
        return b;
    }
    //check if the unit is correct
    void check() const {
        bool b=true;
        if(basic_unit()==true) {
            if(!num_unit.empty() || !den_unit.empty()) b=false;//if is a basic unit, both vectors should be empty
            if(complex_unit()==true) b=false;//cant be a complex and basic unit
        }
        if(complex_unit()==true) {
            if(basic_unit()==true) b=false;
            //  if(conversion.null_operation()==false) b=false; //if complex, it shouldnt have conversion operations
            if(num_unit.empty() && den_unit.empty()) b=false; //if complex, vectors cant be empty
            for(int i=0; i<num_unit.size() && b==true; i++)  if(num_unit[i]->complex_unit()) b=false;
            for(int i=0; i<den_unit.size() && b==true; i++) if(den_unit[i]->complex_unit()) b=false; //all units should be basic
        }
        if(b==false) error_report("FATAL ERROR IN UNIT while checking, please contact support",1,1);
    }
};
