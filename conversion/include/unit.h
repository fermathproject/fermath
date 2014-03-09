/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Unit Class
Version:0.8
*/
#include "conversion.h"
//This class stores an unit, with the needed operations to conversionert into the standard unit of his magnitude
typedef unsigned short magnitude_id;
typedef unsigned short unit_id;
/*CHECK:
-si es simple no es compleja y viceversa
--si tiene vector<> no tiene conversion
-si es simple tiene nombre (si es compleja puede o no tener)
*/
class unit {
private:
    string name;
    string symbol; //the different names of the unit will be stored in a map
    vector<const unit *> num_unit;
    vector<const unit *> den_unit; //the unit is nummag/denmag
    conversion conv; //stores the conversion
    magnitude_id magid;
    unit_id id;

public:
    //CONSTRUCTORS
    unit() {
        magid=0;
        id=0;
    }
    //constructor for a basic unit
    unit(string name2,string symbol2,const conversion &conv2,magnitude_id magid2,unit_id id2=0) {
        name=name2;
        symbol=symbol2;
        conv=conv2;
        magid=magid2;
        id=id2;
        check();
    }
    //constructor for complex unit
    unit(string name2,string symbol2,const vector<const unit *> &num,const vector<const unit *> &den,magnitude_id id,unit_id id2=0) {
        name=name2;
        symbol=symbol2;
        num_unit=num;
        den_unit=den;
        magid=id;
        id=id2;
        clean_unit();
        check();
    }
    //complex unit without name
    unit(const vector<const unit *> &num,const vector<const unit *> &den,magnitude_id mid,unit_id id2=0) {
        magid=mid;
        id=id2;
        num_unit=num;
        den_unit=den;
        clean_unit();
        check();
    }

    /* unit(ifstream &input,magnitude_id magid2,unit_id id2=0) { //Constructor from a binary input
         read_unit(input,magid2);
         id=id2;
         magid=magid2;
     }*/

    unit(const unit &unit2) { //Copy constructor
        (*this)=unit2;
    }

    //MODIFICATION
    void set_conversion(const conversion &conv2) {
        conv=conv2;
        erase_conversion_units();
        check();
    }
    void set_conversion_units(const vector<const unit *> &num,const vector<const unit *> &den) {
        num_unit=num;
        den_unit=den;
        erase_conversion();
        clean_unit();
        check();
    }
    //set the id of magnitude
    void set_mag_id(magnitude_id m) {
        magid=m;
    }
    //set the id of unit
    void set_id(unit_id id2) {
        id=id2;
    }
    //remove all conversion units
    void erase_conversion_units() {
        num_unit.clear();
        den_unit.clear();
    }
    //remove the conversion data
    void erase_conversion() {
        conv.clear();
    }
    //clear the unit
    void clear() {
        clear_names();
        erase_conversion();
        erase_conversion_units();
        magid=0;
        id=0;
    }
    //clear conv and num/den
    void clear_conversion() {
        erase_conversion_units();
        erase_conversion();
    }
    void clear_names() {
        name.clear();
        symbol.clear();
    }
    //set name and symbol
    void set_name(string s) {
        name=s;
    }
    void set_symbol(string s) {
        symbol=s;
    }
    //ACCESS
    //return the id of magnitude
    magnitude_id mag_id() const {
        return magid;
    }
    unit_id get_id() const {
        return id;
    }
    //return the unit name
    string get_name() const {
        return name;
    }
    //return the unit symbol
    string get_symbol() const {
        return symbol;
    }
    //returns the conversion
    conversion get_conversion() const {
        return conv;
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
        return !conv.null_operation();
    }
    //return true if this is the standard unit of magnitude
    bool standard_unit() const {
        bool standard=true;
        if(complex_unit()==false) {
            standard=!have_conversion();
        }
        else {
            for(int i=0; i<den_unit.size() && standard==true; i++) {
                if(den_unit[i]->standard_unit()==false) standard=false;
            }
            for(int i=0; i<num_unit.size() && standard==true; i++) {
                if(num_unit[i]->standard_unit()==false) standard=false;
            }
        }
        return standard;
    }

    bool same_magnitude(const unit &u) const {
        bool basic1=basic_unit();
        bool basic2=u.basic_unit();
        if(basic1!=basic2) return false; //both should be simple or complex
        if(basic1==true) { //if is not a complex unit
            if(magid==u.magid) return true;
            else return false;
        }
        else { //if is complex
            bool b=true;
            int ns1=num_unit.size();
            int ns2=u.num_unit.size();
            int ds1=den_unit.size();
            int ds2=u.den_unit.size();
            if(ns1!=ns2 || ds1!=ds2) b=false;
            else {
                vector<magnitude_id> vmag1,vmag2; //vectors with all magnitudes
                for(int i=0; i<ns1; i++) {
                    vmag1.push_back(num_unit[i]->magid);
                    vmag2.push_back(u.num_unit[i]->magid);
                }
                if(compare_vector_elements(vmag1,vmag2)==false) b=false;
                else {
                    vmag1.clear();
                    vmag2.clear();
                    for(int i=0; i<ds1; i++) {
                        vmag1.push_back(den_unit[i]->magid);
                        vmag2.push_back(u.den_unit[i]->magid);
                    }
                    if(compare_vector_elements(vmag1,vmag2)==false) b=false;
                }
            }
            return b;
        }
    }
    bool have_name() const {
        if(name.empty()) return false;
        else return true;
    }
    bool have_symbol() const {
        if(symbol.empty()) return false;
        else return true;
    }

    bool same_conversion(const unit &u) const {
        bool b=false;
        if(u.basic_unit() && (*this).basic_unit()) {
            if((*this).conv==u.conv) b=true;
        }
        else if(u.complex_unit() && (*this).complex_unit()) {
            if(compare_vector_elements(den_unit,u.den_unit)==false) b=false;
            if(compare_vector_elements(num_unit,u.num_unit)==false) b=false;
        }
        return b;
    }
    bool same_id(const unit &u) const {
        if(id==u.id && id!=0 && u.id!=0) return true;
        else return false;
    }
    //returns true if the unit has information to be written
    bool writable_unit() const {
        //if(have_conversion()) return true;
        if(basic_unit()) return true;
        else if(have_name()==true) return true;//if is complex, it should have name
        else return false;
    }
    bool null_unit() const {
        //if(id==0) return true;
        if(magid==0 && num_unit.empty() && den_unit.empty() && conv.null_operation()) return true;
        else return false;
    }
    bool same_unit(const unit &unit2) const { //check if the magnitude unit and the conversion data is the same
        bool eq=true;
        if((*this).same_magnitude(unit2)==false) eq=false;
        if((*this).same_conversion(unit2)==false) eq=false;
        return eq;
    }
    //CLASS JOBS
    //returns the standard unit of magnitude from this unit value
    data_type standard_unit_value(data_type n) const {
        if(have_conversion() || basic_unit()) n=conv.operate(n); //if is basic or has conversion stored
        else { //try to conversionert using num/den vectors
            if(check_conversion()==false) error_report("ERROR, cant convert unit",1,1);
            for(int i=0; i<num_unit.size(); i++) n=num_unit[i]->standard_unit_value(n);
            for(int i=0; i<den_unit.size(); i++) n=den_unit[i]->value_from_standard_unit(n); //the unit is all products (checked) so it is possible to do the inverse operations when dividing
        }
        return n;
    }
    //returns the unit from a standard unit value
    data_type value_from_standard_unit(data_type n) const {
        if(have_conversion() || basic_unit()) n=conv.inverse_operate(n); //if is basic or has conversion stored
        else { //try to conversionert using num/den vectors
            if(check_conversion()==false) error_report("ERROR, cant convert unit",1,1);
            for(int i=0; i<num_unit.size(); i++) n=num_unit[i]->value_from_standard_unit(n);
            for(int i=0; i<den_unit.size(); i++) n=den_unit[i]->standard_unit_value(n);
        }
        return n;
    }
    //conversion n from one unit to another
    data_type convert_from(data_type n,const unit &a) const {
        n=a.standard_unit_value(n);
        n=value_from_standard_unit(n);
        return n;
    }
    void show(ostream &out=cout) const {
        cout<<"ID:"<<id<<"--"<<magid<<endl;
        if(have_name()) cout<<name<<"   "<<symbol<<endl;
        else cout<<"no name\n";
        if(complex_unit()==true) {
            cout<<"complex"<<endl;
            for(int i=0; i<num_unit.size(); i++) cout<<*(num_unit[i])<<" ";
            cout<<endl;
            for(int i=0; i<den_unit.size(); i++) cout<<*(den_unit[i])<<" ";
        }
        else {
            cout<<"basic"<<endl;
            cout<<"conversion:"<<conv;
        }
    }

    //READ/WRITE
    //do binary write of unit(if possible)
    bool write_unit(ofstream &out) const {
        bool wr;
        wr=writable_unit();
        if(wr==true) { //only writes the unit if it has real info
            binary_write(name,out);
            binary_write(symbol,out); //write name and symbol
            bool complex=complex_unit();
            binary_write(complex,out); //rite if is complex or not
            if(complex==false) {
                conv.write_conversion(out); //Writes conversion operations
            }
            else {
                //  error_report("Warning, trying to write complex unit",0,1);
                int siz1=num_unit.size();
                int siz2=den_unit.size();
                string s;
                binary_write(siz1,out);
                for(int i=0; i<siz1; i++) { //write numerator
                    s=num_unit[i]->get_name();
                    binary_write(s,out);
                }
                binary_write(siz2,out);
                for(int i=0; i<siz2; i++) { //write denominator
                    s=den_unit[i]->get_name();
                    binary_write(s,out);
                }
            }
        }
        return wr;
    }
    void read_unit(ifstream &input,unit_id id2,magnitude_id magid2=0) {
        bool complex;
        binary_read(name,input);
        binary_read(symbol,input);
        binary_read(complex,input);
        if(complex==false) conv.read_conversion(input);//read conversion data
        else {
            error_report("ERROR, impossible to read complex unit",0,1);
        }
        magid=magid2;
        id=id2;
        check();
    }
    //OPERATORS //TODO operators <,>
    //operator==
    bool operator==(const unit &unit2) const { //check if the magnitude unit and the conversion data is the same
        return (id==unit2.id);
    }
    // operator!=
    bool operator!=(const unit &unit2) const {
        return !((*this)==unit2);
    }
    //operator <,> (compares id)
    bool operator<(const unit &unit2) const {
        if(id<unit2.id) return true;
        else rclass magnitude_db {
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
            bool empty() const {
                return mag_list.empty();
            }
            unsigned int size() const {
                return mag_list.size();
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
                unit *u;
                m=search_magnitude(magid);
                u=m->search(id);
                return u;
            }


private:
            void check() {
                //THING TO CHECK¿?
            }

            eturn false;
        }
        bool operator>(const unit &unit2) const {
            if(id>unit2.id) return true;
            else return false;
        }
        // operator=
        unit &operator=(const unit &unit2) {
            if(this!=&unit2) {
                (*this).name=unit2.name;
                (*this).symbol=unit2.symbol;
                (*this).magid=unit2.magid;
                (*this).conv=unit2.conv;
                (*this).num_unit=unit2.num_unit;
                (*this).den_unit=unit2.den_unit;
                (*this).id=unit2.id;
                check();
            }
            return *this;
        }
        //operator *
        const unit operator*(const unit &other) const {
            unit result;
            result.add_numerator_unit((*this)); //result is the product of two units
            result.add_numerator_unit(other);
            result.clean_unit();
            return result;
        }
        //operator /
        const unit operator/(const unit &other) const {
            unit result;
            result.add_numerator_unit((*this));
            result.add_denominator_unit(other);
            result.clean_unit();
            return result;
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
        friend ostream  &operator<< (ostream &out, const unit &uni) {
            if(uni.have_symbol()) out<<uni.symbol;
            else if(uni.have_name()) out<<uni.name;
            else if(uni.complex_unit()) {
                for(int i=0; i<(uni.num_unit).size(); i++) {
                    out<<*(uni.num_unit[i]);
                }
                if((uni.num_unit).size()==0) out<<"1";
                if((uni.den_unit).size()>0) out<<"/";
                for(int i=0; i<(uni.den_unit).size(); i++) {
                    out<<*(uni.den_unit[i]);
                }
            }
            else {
                error_report("Warning, unit cant be shown",1,1);
            }
            return out;
        }
        void clean_unit() {
            simplify_complex_unit();
            convert_if_simple(); //convert a complex unit into a simple unit if possible
            check(); //check
        }
        //if the conversion can be used in complex units
        bool suitable_complex_conversion() const { //return if you can do a conversion in a unit based on this (for example m/s)
            return conv.product_operation();
        }
        //converts a complex unit into a simple unit if it is possible
        void convert_if_simple() {
            if(den_unit.empty()==true && num_unit.size()==1)(*this)=*(num_unit[0]);
        }
        //adds a basic unit (if true in numerator, false denominator)
        void add_basic_unit(const unit &u,bool numerator=true) {
            const unit *p=&u;
            if(u.complex_unit()) error_report("FATAL ERROR: adding a not basic unit",1,1);
            else {
                conv.clear();
                if(numerator==true) {
                    //    if(erase(den_unit,u)==false) { //try to erase the unit from denominator, if it exist
                    num_unit.push_back(p);//if the unit is not the unit in denominator, adds unit in numerator
                    //    }
                }
                else { //if the unit is added to denominator
                    //   if(erase(num_unit,u)==false) {
                    den_unit.push_back(p);
                    // }
                }
            }
        }
        //add an unit, if it is not simple, add the conversion units, after this, clean the unit
        void add_numerator_unit(const unit &u) {
            if(u.basic_unit()==true) {
                add_basic_unit(u,true); //if is a simple unit, add the unit
            }
            else {
                for(int i=0; i<(u.num_unit).size(); i++) add_basic_unit(*(u.num_unit[i]),true);//adds the numerator units
                for(int i=0; i<(u.den_unit).size(); i++) add_basic_unit(*(u.den_unit[i]),false);//adds the denominator units
            }
        }
        void add_denominator_unit(const unit &u) {
            if(u.basic_unit()==true) {
                add_basic_unit(u,false); //if is a simple unit
            }
            else {
                for(int i=0; i<(u.num_unit).size(); i++) add_basic_unit(*(u.num_unit[i]),false);//adds the numerator units
                for(int i=0; i<(u.den_unit).size(); i++) add_basic_unit(*(u.den_unit[i]),true);//adds the denominator units
            }
        }
        //it erases the units that are of the same magnitude (¿only equal units?)
        void simplify_complex_unit() {
            if(complex_unit()==true) {
                for(int i=0; i<num_unit.size(); i++) {
                    bool found=false;
                    for(int j=0; j<den_unit.size() && found==false; j++) {
                        if((num_unit[i]->mag_id()==den_unit[j]->mag_id()) && (num_unit[i]->mag_id()!=0 && den_unit[j]->mag_id()!=0)) {
                            found=true;
                            num_unit.erase(num_unit.begin()+i);
                            den_unit.erase(den_unit.begin()+j);
                            i--;
                        }
                    }
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
            error_id err=0;
            //if(magid!=0 || id!=0) b=false;
            if(basic_unit()==complex_unit()) {
                err=1;//a unit cant be basic and complex
            }
            else if(basic_unit()==true) {
                if(!num_unit.empty() || !den_unit.empty()) err=2;//if is a basic unit, both vectors should be empty
                if(!have_name() && !have_symbol()) err=3; //if is basic, it should have name
            }
            else if(complex_unit()==true) {
                if(conv.null_operation()==false) err=4; //if complex, it shouldnt have conversion operations
                if(num_unit.empty() && den_unit.empty()) err=5; //if complex, vectors cant be empty
                if(num_unit.size()==1 && den_unit.empty()==true) err=6; //it cant be complex if only has one unit
                for(int i=0; i<num_unit.size() && err==0; i++)  if(num_unit[i]->complex_unit()) err=7;
                for(int i=0; i<den_unit.size() && err==0; i++) if(den_unit[i]->complex_unit()) err=8; //all units should be basic
            }
            if(err>0) error_report(err,(string)"FATAL ERROR IN UNIT while checking",1,1);
        }
    };
