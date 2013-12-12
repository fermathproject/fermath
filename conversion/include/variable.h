/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Variable Class
Version:0.6
*/

//this class stores and operate with a variable, it can have an unit or not, also operates with undefined variables (variables without a value)
class variable {
private:
    double value;
    unit unidad;
    string name;
    bool dim_unit; //if variable has an unit
    bool numeric_value; //if variable has a value
    int unit_mult; //indicates if the unit is pow
    //int type_of_unit; //decimal,hexadecimal....
public:

    variable() {//a null variable
        dim_unit=false;
        numeric_value=false;
    }
    variable(string name2,float val2,unit &uni,int mult=1) {//a variable with name, value and unit
        numeric_value=true;
        value=val2;
        name=name2;
        dim_unit=true;
        unidad=uni;
        set_mult(mult);//set and check unit_mult
    }
    variable(float n) { //a variable with no dimension
        value=n;
        numeric_value=true;
        dim_unit=false;
        unit_mult=1;
    }
    variable(string name2,float val2) { //a variable with name and value
        value=val2;
        numeric_value=true;
        dim_unit=false;
        name=name2;
        unit_mult=1;
    }
    variable(float val2,unit &uni,int mult=1) { //a variable with no name
        value=val2;
        dim_unit=true;
        numeric_value=true;
        unidad=uni;
        set_mult(mult);
    }
    variable(string name2) { //a variable with only a name
        dim_unit=false;
        numeric_value=false;
        name=name2;
        unit_mult=1;
    }
    variable(const variable &var) { //copy constructor
        (*this)=var;
    }
    void erase_name() {
        name.clear();
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
    int magnitude_id() const {
        int m=-1;
        if(dim_unit==true) m=unidad.mag_id();
        return m;
    }
    //set new unit, not changing unit_mult
    void set_unit(unit &uni,bool change_unit=true) { //if change_unit==true, the value change according to the unit if possible
        if(!dim_unit) {
            change_unit=false;
            dim_unit=true;
        }
        else {
            if(change_unit && (uni.mag_id()!=unidad.mag_id())) {
                change_unit=false;
                cout<<"ERROR, changing a not suitable unit in variable"<<endl;
            }
        }
        if(change_unit==false) {
            unidad=uni;
        }
        else {
            double x;
            x=get_standard_value();
            unidad=uni;
            set_value_from_standard(x);
        }
    }
    //change the unit and mult
    void set_unit(unit &uni,int mult) { //if change_unit==true, the value change according to the unit if possible
        if(!dim_unit) {
            dim_unit=true;
            unidad=uni;
            set_mult(mult);
        }
        else if(uni.mag_id()!=unidad.mag_id()) {
            cout<<"ERROR, changing a not suitable unit in variable"<<endl;
            unidad=uni;
            set_mult(mult);
        }
        else {
            double x;
            x=get_standard_value();
            unidad=uni;
            set_mult(mult);
            set_value_from_standard(x);
        }
    }
    int get_mult() const {
        return unit_mult;
    }
    double get_value() const {
        if(numeric_value) return value;
        else return value; //CHANGE?
    }
    double get_standard_value() const { //get standard value of unit
        if(numeric_value && dim_unit) {
            double v=pow(abs(value),1/unit_mult);
            v=unidad.standard_unit_value(v);
            v=pow(v,unit_mult);
            if(value<0) v=-v;
            return v;
        }
        else return value;
    }

    void set_value_from_standard(double x) {//set the value x as standard(assuming x has the same potence)
        if(dim_unit) {
            double v=pow(abs(x),1/unit_mult);
            v=unidad.value_from_standard_unit(v);
            value=pow(v,unit_mult);
            if(x<0) value=-value;
        }
        else value=x;
    }
    void set_mult(int i) {
        unit_mult=i;
        if(unit_mult==0) dim_unit=false;
    }
    unit get_unit() const {
        return unidad;
    }
    bool can_operate_with(const variable &var2) const {
        bool b=true;
        bool un1=(*this).have_unit();
        bool un2=var2.have_unit();
        bool v1=(*this).have_value();
        bool v2=var2.have_value();
        if(!v1 || !v2) b=false; //if one of them dont have numeric_value
        else if((un1 && !un2) || (!un1 && un2)) b=false; //if one of them has unit but the other dont
        else if(un1 && un2) { //if both have units, it has to be the same magnitude
            if((((*this).unidad).mag_id())!=((var2.unidad).mag_id())) b=false;
        }
        return b;
    }
    void write_variable(ofstream &out) const {
        binary_write(name,out);
        binary_write(numeric_value,out);
        if(numeric_value) binary_write(value,out);
        binary_write(dim_unit,out);
        if(dim_unit) {
            unidad.write_unit(out);
            binary_write(unit_mult,out);
        }
    }
    void read_variable(ifstream &input) {
        binary_read(name,input);
        binary_read(numeric_value,input);
        if(numeric_value) binary_read(value,input);
        binary_read(dim_unit,input);
        if(dim_unit) {
            unidad.read_unit(input);
            binary_read(unit_mult,input);
        }
    }

    //OPERATORS
    //operator==
    bool operator==(const variable &var2) const { //check if the value of variables are equal
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
                if((*this).magnitude_id()==var2.magnitude_id()) {
                    x=(*this).get_standard_value();
                    y=var2.get_standard_value();
                    if(x==y && (*this).get_mult()==var2.get_mult()) eq=true;
                }
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
            (*this).name=var2.name; //CHANGE¿?
            (*this).value=var2.value;
            (*this).unidad=var2.unidad;
            (*this).dim_unit=var2.dim_unit;
            (*this).numeric_value=var2.numeric_value;
            (*this).unit_mult=var2.unit_mult;
        }
        return (*this);
    }


    //operator+:adds two variables if they have a value and are the same magnitude (or dont have magnitude)
    const variable operator+(const variable &other) const {
        variable result(*this);
        if(result.can_operate_with(other)) {
            double x=result.get_standard_value();
            double y=other.get_standard_value();
            x=x+y;
            result.set_value_from_standard(x);
        }
        else cout<<"ERROR OPERATING"<<endl;
        result.erase_name(); //CHANGE¿?
        return result;
    }
    //operator -
    const variable operator-(const variable &other) const {
        variable result(*this);
        if(result.can_operate_with(other)) {
            double x=result.get_standard_value();
            double y=other.get_standard_value();
            x=x-y;
            result.set_value_from_standard(x);
        }
        else cout<<"ERROR OPERATING"<<endl;
        result.erase_name(); //CHANGE?
        return result;
    }
    //operator *
    const variable operator*(const variable &other) const {
        variable result(*this);
        if(result.can_operate_with(other)) {
            int m1=result.get_mult();
            int m2=other.get_mult();
            double x=result.get_standard_value();
            double y=other.get_standard_value();
            x=x*y;
            result.set_value_from_standard(x);
            result.set_mult(m1+m2);
        }
        else cout<<"ERROR OPERATING"<<endl;
        result.erase_name(); //CHANGE?
        return result;
    }
    //operator /
    const variable operator/(const variable &other) const {
        variable result(*this);
        if(result.can_operate_with(other)) {
            int m1=result.get_mult();
            int m2=other.get_mult();
            double x=result.get_standard_value();
            double y=other.get_standard_value();
            x=x/y;
            result.set_value_from_standard(x);
            result.set_mult(m1-m2);
        }
        else cout<<"ERROR OPERATING"<<endl;
        result.erase_name(); //CHANGE?
        return result;
    }
    //operator +=
    variable operator+=(const variable &var) {
        (*this)=(*this)+var;
        return *this;
    }
    //operator -=
    variable operator-=(const variable &var) {
        (*this)=(*this)-var;
        return *this;
    }
    //operator *=
    variable operator*=(const variable &var) {
        (*this)=(*this)*var;
        return *this;
    }
    //operator /=
    variable operator/=(const variable &var) {
        (*this)=(*this)/var;
        return *this;
    }
    //operator unary -:return the negative value of the unit
    variable operator-() const {
        variable result=(*this);
        if(result.have_value()) result.value=-result.value;
        return result;
    }
private:
    //operator <<, show the variable on the standard output
    friend ostream  &operator<< (ostream &out, const variable &var) {
        if(var.have_name()) out<<var.name<<":";
        if(var.have_value()) out<<var.value<<" ";
        if(var.have_unit()) {
            out<<var.unidad.get_symbol();
            if(var.unit_mult>1 || var.unit_mult<0) out<<"^"<<var.unit_mult;
        }
        return out;
    }
};
