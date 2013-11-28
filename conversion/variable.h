/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Class
Version:0.3
*/

//this class stores and operate with a variable, it can have an unit or not, also operates with undefined variables (variables without a value)
class variable {
private:
    double val;
    unit *unidad; //unit where belongs
    string name;
    bool dim_unit; //if variable has an unit
    bool value; //if variable has a value
public:

    variable() {
        dim_unit=0;
        value=0;
    }
    variable(string name2,float val2,unit &uni) {
        value=true;
        val=val2;
        name=name2;
        dim_unit=true;
        unidad=&uni;
    }
    variable(float n) {
        val=n;
        value=true;
        dim_unit=false;
    }
    variable(string name2,float val2) {
        val=val2;
        value=true;
        dim_unit=false;
        name=name2;
    }
    variable(float val2,unit &uni) {
        val=val2;
        dim_unit=true;
        value=true;
        unidad=&uni;
    }
    variable(string name2) {
        dim_unit=false;
        value=false;
        name=name2;
    }
    //returns the magnitude of the variable unit
    int magnitude() {
        int m=-1;
        if(dim_unit==true) m=unidad->mag_id();
        return m;
    }
    double get_value() {
        if(value) return val;
        else return val;
    }
    double get_standard_value() {
        if(value && dim_unit) {
            return unidad->standard_unit_value(val);
        }
        else return val;
    }
    //this method adds two variables if them have a value and are the same magnitude
    const variable operator+(const variable &other) const {
        variable result=*this;
        if(result.value && result.dim_unit && other.value && other.dim_unit) {
            double x,y;
            x=result.unidad->standard_unit_value(result.val);
            y=other.unidad->standard_unit_value(other.val);
            x=x+y;
            result.val=result.unidad->value_from_standard_unit(x);
        }
        return result;
    }

};
