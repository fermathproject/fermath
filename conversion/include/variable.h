/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Variable Class
Version:0.7
*/

//this class stores and operate with a variable, it can have an unit or not, also operates with undefined variables (variables without a value)
typedef unsigned short base;
#define DEC_BASE 10
#define HEX_BASE 16
#define OCT_BASE 8
#define BIN_BASE 2
class variable {
private:
    double value;
    unit variable_unit;
    string name;
    bool dim_unit; //if variable has an unit
    bool numeric_value; //if variable has a value
    base variable_base; //decimal,hexadecimal.... (deafult is dec)
public:

    //TODO:some public methods should be private (set and get from standard)
    variable() {//a null variable
        dim_unit=false;
        numeric_value=false;
        set_base();
        check();
    }
    variable(string name2,double val2,unit &uni,base vb=DEC_BASE) {//a variable with name, value and unit
        value=val2;
        name=name2;
        if(uni.null_unit()==false) dim_unit=true;
        variable_unit=uni;
        set_base(vb);
        set_value(val2);
        check();
    }
    variable(double n,base vb=DEC_BASE) { //a variable with no dimension
        value=n;
        numeric_value=true;
        dim_unit=false;
        set_base(vb);
        check();
    }
    variable(string name2,double val2,base vb=DEC_BASE) { //a variable with name and value
        numeric_value=true;
        dim_unit=false;
        name=name2;
        set_base(vb);
        set_value(val2);
        check();
    }
    variable(double val2,unit &uni,base vb=DEC_BASE) { //a variable with no name
        if(uni.null_unit()==false) dim_unit=true;
        numeric_value=true;
        variable_unit=uni;
        set_base(vb);
        set_value(val2);
        check();
    }
    variable(string name2,base vb=DEC_BASE) { //a variable with only a name
        dim_unit=false;
        numeric_value=false;
        name=name2;
        set_base(vb);
        check();
    }
    variable(const variable &var) { //copy constructor
        (*this)=var;
        check();
    }
    //MODIFICATORS
    void erase_name() {
        name.clear();
    }
    void set_value(double x) {
        if(standard_base()==false) error_report("Warning, non standard base, value may change",0,1);
        value=x;
        numeric_value=true;
        check();
    }
    void set_value(string s) {
        value=to_dec(s,variable_base);
        numeric_value=true;
        check();
    }
    //sets variable base (if is an incorrect base, it uses decimal base
    void set_base(base vb=DEC_BASE) {
        if(vb<BIN_BASE || vb>36) {
            error_report("ERROR, base not allowed",0,1);
            vb=DEC_BASE;
        }
        else if(vb>HEX_BASE) error_report("WARNING, base>16",0,1);
        variable_base=vb;
    }
    //set new unit (changing or not value)
    void set_unit(const unit &uni,bool change_value=true) { //if change_unit==true, the value change according to the unit if possible
        if(uni.null_unit()==false) {
            if(standard_base()==false) error_report("Warning, non standard base, value may change",0,1);
            if(!dim_unit) {
                change_value=false;
                dim_unit=true;
            }
            else if(change_value==true && uni.same_magnitude(variable_unit)==false) {
                change_value=false;
                error_report("ERROR, changing a not suitable unit in variable(not same magnitude)",1,1);
            }
            if(change_value==false) {
                variable_unit=uni;
            }
            else {
                double x;
                x=get_standard_value();
                variable_unit=uni;
                set_value_from_standard(x);
            }
        }
        check();
    }
    void trunc_var() {
        value=(int) value;
    }
    void round_off_var(unsigned int prec=0) {
        if(is_int()==false && standard_base()==true) {
            unsigned int prec2=pow(10,prec);
            value=floor(value*prec2+0.5)/prec2;
        }
        else if(standard_base()==false) {
            error_report("Warning, not possible to round a not dec variable",1,0);
            //change to standard base and round¿?
        }
    }
    void clear_unit() {
        dim_unit=false;
        variable_unit.clear();
    }
    void clear_value() {
        numeric_value=false;
    }
    void clear() {
        clear_unit();
        erase_name();
        set_base();
        clear_value();
    }
    //ACCESS
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
    magnitude_id mag_id() const {
        int m=-1;
        if(dim_unit==true) m=variable_unit.mag_id();
        return m;
    }

    unit get_unit() const {
        return variable_unit;
    }
    //return true if are the same magnitude
    bool same_magnitude(const variable &other)const {
        return variable_unit.same_magnitude(other.variable_unit);
    }
    double get_value() const {
        if(standard_base()==false) error_report("Warning,non standard base",1,1);
        if(have_value()==true) return value;
        else {
            error_report("ERROR, not value to return",1,1);
            return 0;
        }
    }

    base get_base() const {
        return variable_base;
    }
    bool standard_base() const {
        if(variable_base==DEC_BASE) return true;
        else return false;
    }
    bool is_int() const {
        int val2=value;
        if(val2==value) return true;
        else return false;
    }
    bool is_positive() const {
        if(value>=0) return true;
        else return false;
    }
    bool is_zero() const {
        if(value==0) return true;
        else return false;
    }
    string show_value() const {
        string val;
        if(have_value()==true)        val=to_base(value,variable_base);
        else        error_report("ERROR,not value to return",1,1);
        return val;
    }

    //READ/WRITE
    /*  void write_variable(ofstream &out) const {
          binary_write(name,out);
          binary_write(numeric_value,out);
          if(numeric_value) binary_write(value,out);
          binary_write(dim_unit,out);
          if(dim_unit) {
              variable_unit.write_unit(out);
              binary_write(unit_mult,out);
          }
      }
      void read_variable(ifstream &input) {
          binary_read(name,input);
          binary_read(numeric_value,input);
          if(numeric_value) binary_read(value,input);
          binary_read(dim_unit,input);
          if(dim_unit) {
              variable_unit.read_unit(input);
              binary_read(unit_mult,input);
          }
      }*/

    //OPERATORS
    //TODO:check operators
    //operator==
    bool operator==(const variable &var2) const { //check if the value of variables are equal
        bool eq=false;
        bool v1,v2,d1,d2;
        v1=(*this).numeric_value;
        v2=var2.numeric_value;
        if(v1 && v2) {
            double x=(*this).value;
            double y=var2.value;
            if(same_magnitude(var2)) {
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
            (*this).variable_unit=var2.variable_unit;
            (*this).dim_unit=var2.dim_unit;
            (*this).numeric_value=var2.numeric_value;
            (*this).variable_base=var2.variable_base;
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
        else error_report("ERROR OPERATING",1,1);
        result.erase_name();
        result.check();
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
        else error_report("ERROR OPERATING",1,1);
        result.erase_name(); //CHANGE?
        result.check();
        return result;
    }

    //operator *
    const variable operator*(const variable &other) const { //FIXME
        variable result(*this);
        if(result.have_value() && other.have_value()) {
            if(result.have_unit() && other.have_unit()) { //if both have units
                if(result.same_magnitude(other)) { //if the same magnitude, it changes the value to same unit (kg*g -> kg*kg)
                    double x=result.get_standard_value();
                    double y=other.get_standard_value();
                    x=x*y;
                    result.set_value_from_standard(x);
                    unit unid2=result.variable_unit;
                    unid2=unid2*result.variable_unit;
                    result.set_unit(unid2,false);
                }
                else { //if its no the same magnitude, just multiply value and units
                    double x=result.get_value();
                    double y=other.get_value();
                    x=x*y;
                    result.set_value(x);
                    result.set_unit((result.variable_unit*other.variable_unit),false);
                }
            }
            else { //if one of them (or both) are adimensional variables
                if(result.have_unit()==false && other.have_unit()==false) {
                    double x;
                    x=other.value*result.value;
                    result.set_value(x);
                    result.dim_unit=false;
                }
                else if(result.have_unit()==true && other.have_unit()==false) {
                    double x;
                    x=other.value*result.value;
                    result.set_value(x);
                }
                else if(result.have_unit()==false && other.have_unit()==true) {
                    result.set_unit(other.get_unit());
                    double x;
                    x=other.value*result.value;
                    result.set_value(x);
                }
            }
        }
        else error_report("ERROR OPERATING",1,1);
        result.erase_name(); //CHANGE?
        return result;
    }
    //operator /
    const variable operator/(const variable &other) const {//FIXME
        variable result(*this);
        if(result.have_value() && other.have_value()) {
            if(result.same_magnitude(other)) { //if the same magnitude, it changes the value to same unit (kg*g -> kg*kg)
                double x=result.get_standard_value();
                double y=other.get_standard_value();
                x=x/y;
                result.set_unit((result.variable_unit/result.variable_unit),false);
                result.set_value_from_standard(x);
            }
            else { //if its no the same magnitude, just multiply value and units
                double x=result.get_value();
                double y=other.get_value();
                x=x/y;
                result.set_value(x);
                result.set_unit((result.variable_unit/other.variable_unit),false);
            }
        }
        else error_report("ERROR OPERATING",1,1);
        result.erase_name(); //CHANGE?
        result.check();
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
        if(var.have_value()) {
            if(var.standard_base()==false) {
                string val;
                val=var.show_value();
                out<<val;
                out<<")"<<" "<<var.get_base();
            }
            else out<<var.value;
        }
        if(var.have_unit()) {
            out<<" "<<var.variable_unit;
        }
        return out;
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
            if(same_magnitude(var2)==false) b=false;
        }
        return b;
    }

    string to_base(int v, base b=DEC_BASE)const {
        bool neg=false;
        string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string result;
        if(b<=1 || b>36) {
            error_report("ERROR, variable base not allowed",1,1);
            b=DEC_BASE;
        }
        if(v<0) {
            neg=true;
            v=-v;
        }
        do {
            result = digits[v % b] + result;
            v /= b;
        }
        while(v);
        if(neg==true) result="-"+result;
        return result;
    }

    long int to_dec(string s,base b) const {
        if(b<=1 || b>36) {
            error_report("ERROR, variable base not allowed",1,1);
            b=DEC_BASE;
        }
        return strtol(s.c_str(),NULL,b);
    }
    void set_value_from_standard(double x) { //set the value of x to the variable according to the unit
        if(standard_base()==false) error_report("Warning, non standard base, value may change",0,1);
        if(!dim_unit) {
            set_value(x);
        }
        else {
            x=variable_unit.value_from_standard_unit(x);
            set_value(x);
        }
        check();
    }
    double get_standard_value() const { //get standard value of unit
        if(!numeric_value) error_report("ERROR, not numric value",1,1);
        if(standard_base()==false) error_report("Warning,non standard base",1,1);
        if(dim_unit) {
            double v=variable_unit.standard_unit_value(value);
            return v;
        }
        else return value;
    }

    void check() const {
        bool b=true;
        if(variable_base<2 || variable_base>36)     b=false;
        // if(variable_unit.null_unit()==true && dim_unit==false) b=false;
        if(b==false) error_report("error checking variable",1,1);
    }

};
