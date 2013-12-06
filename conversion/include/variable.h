/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Variable Class
Version:0.5
*/

//this class stores and operate with a variable, it can have an unit or not, also operates with undefined variables (variables without a value)
class variable {
private:
    double value;
    unit *unidad;//TODO change unit* to unit? or change some methods //unit where belongs
    string name;
    bool dim_unit; //if variable has an unit
    bool numeric_value; //if variable has a value
    //int type_of_unit; //decimal,hexadecimal....
public:

    variable() {//a null variable
        dim_unit=false;
        numeric_value=false;
    }
    variable(string name2,float val2,unit *uni) {//a variable with name, value and unit
        numeric_value=true;
        value=val2;
        name=name2;
        dim_unit=true;
        unidad=uni;
    }
    variable(float n) { //a variable with no dimension
        value=n;
        numeric_value=true;
        dim_unit=false;
    }
    variable(string name2,float val2) { //a variable with name and value
        value=val2;
        numeric_value=true;
        dim_unit=false;
        name=name2;
    }
    variable(float val2,unit *uni) { //a variable with no name
        value=val2;
        dim_unit=true;
        numeric_value=true;
        unidad=uni;
    }
    variable(string name2) { //a variable with only a name
        dim_unit=false;
        numeric_value=false;
        name=name2;
    }

    bool have_unit() const {
        return dim_unit;
    }
    bool have_value() const {
        return numeric_value;
    }
    bool have_name() const {
        return !(name.empty());
    }
    //returns the magnitude of the variable unit
    int magnitude() const {
        int m=-1;
        if(dim_unit==true) m=unidad->mag_id();
        return m;
    }
    void set_unit(unit &uni,bool change_unit=true) { //if change_unit==true, the value change according to the unit if possible
        if(!dim_unit) {
            change_unit=false;
            dim_unit=true;
        }
        else {
            if(change_unit && (uni.mag_id()!=unidad->mag_id())) {
                change_unit=false;
                cout<<"ERROR, changing a not suitable unit in variable"<<endl;
            }
        }
        if(change_unit==false) {
            unidad=&uni;
        }
        else {
            double x;
            x=get_standard_value();
            unidad=&uni;
            set_value_from_standard(x);
        }
    }
    double get_value() const {
        if(numeric_value) return value;
        else return value; //CHANGE?
    }
    double get_standard_value() const { //get standard value of unit
        if(numeric_value && dim_unit) {
            return unidad->standard_unit_value(value);
        }
        else return value;
    }
    void set_value_from_standard(double x) {
        value=unidad->value_from_standard_unit(x);
    }
    unit &get_unit() {
        return *unidad;
    }

    //OPERATORS
    //operator==
    bool operator==(const variable &var2) const { //check if the value of variables are wqual
        bool eq=false;
        bool v1,v2,d1,d2;
        v1=(*this).numeric_value;
        v2=var2.numeric_value;
        d1=(*this).dim_unit;
        d2=var2.dim_unit;
        if(v1 && v2) {
            double x=(*this).value;
            double y=var2.value;
            if(!d1 && !d2 && x==y) eq=true;
            else if(d1 && d2) {
                x=(*this).get_standard_value();
                y=var2.get_standard_value();
                if(x==y) eq=true;
            }
        }
        return eq;
    }
    // operator!=
    bool operator!=(const variable &var2) const {
        return !((*this)==var2);
    }
    // operator=
    variable &operator=(const variable &var2) {
        if(this!=&var2) {
            (*this).name=var2.name;
            (*this).value=var2.value;
            (*this).unidad=var2.unidad;
            (*this).dim_unit=var2.dim_unit;
            (*this).numeric_value=var2.numeric_value;
        }
        return *this;
    }


    //operator+:adds two variables if they have a value and are the same magnitude (or dont have magnitude)
    const variable operator+(const variable &other) const {
        variable result=(*this);
        //variable other=var2;
        bool v1,v2,d1,d2,dim_suit=false;
        v1=result.numeric_value;
        v2=other.numeric_value;
        d1=result.dim_unit;
        d2=other.dim_unit;
        if(d1 && d2) {
            if((result.unidad)->mag_id()==(other.unidad)->mag_id()) dim_suit=true;
        }//if the units are from the same magnitude
        if(v1 && v2) { //if both have numeric_value
            double x=result.value;
            double y=other.value;
            if(!d1 && !d2) result.value=x+y; //if they are adimensional variable
            else if(d1 && d2) {
                if(dim_suit) {
                    x=result.get_standard_value();
                    y=other.get_standard_value();
                    x=x+y;
                    result.set_value_from_standard(x);
                }
            }
        }
        return result;
    }
    //operator -
    const variable operator-(const variable &other) const {
        variable result=(*this);
        //variable other=var2;
        bool v1,v2,d1,d2,dim_suit=false;
        v1=result.numeric_value;
        v2=other.numeric_value;
        d1=result.dim_unit;
        d2=other.dim_unit;
        if(d1 && d2) {
            if((result.unidad)->mag_id()==(other.unidad)->mag_id()) dim_suit=true;
        }//if the units are from the same magnitude
        if(v1 && v2) { //if both have numeric_value
            double x=result.value;
            double y=other.value;
            if(!d1 && !d2) result.value=x-y; //if they are adimensional variable
            else if(d1 && d2) {
                if(dim_suit) {
                    x=result.get_standard_value();
                    y=other.get_standard_value();
                    x=x-y;
                    result.set_value_from_standard(x);
                }
            }
        }
        return result;
    }
    //TODO: operator *,operator /
    //TODO?: operators +=,++,--,-=....
private:
    //operator <<, show the variable on the standard output
    friend ostream  &operator<< (ostream &out, const variable &var) {
        if(var.have_name()) out<<var.name<<":";
        if(var.have_value()) out<<var.value<<" ";
        if(var.have_unit()) out<<var.unidad->get_symbol();
        return out;
    }

};
