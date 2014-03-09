/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Variable Class
Version:0.8
*/

//this class stores and operate with a variable, it can have an unit or not, also operates with undefined variables (variables without a value)
typedef unsigned short base;
#define DEC_BASE 10
#define HEX_BASE 16
#define OCT_BASE 8
#define BIN_BASE 2
#define MAX_BASE 36
class variable {
private:
    unit variable_unit;
    string name;
    double value;
    base variable_base; //decimal,hexadecimal.... (deafult is dec)
    bool dim_unit; //if variable has an unit
    bool numeric_value; //if variable has a value
public:
    variable() {//a null variable
        dim_unit=false;
        numeric_value=false;
        set_base();
        check();
    }
    variable(string name2,double val2,const unit &uni,base vb=DEC_BASE) {//a variable with name, value and unit
        name=name2;
        dim_unit=false;
        set_unit(uni);
        set_base(vb);
        set_value(val2);
        check();
    }
    variable(double n,base vb=DEC_BASE) { //a variable with no dimension
        set_value(n);
        dim_unit=false;
        set_base(vb);
        check();
    }
    variable(string name2,double val2,base vb=DEC_BASE) { //a variable with name and value
        dim_unit=false;
        name=name2;
        set_base(vb);
        set_value(val2);
        check();
    }
    variable(double val2,unit &uni,base vb=DEC_BASE) { //a variable with no name
        dim_unit=false;
        set_unit(uni);
        numeric_value=true;
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
    //the value is set in dec
    void set_value(double x) {
        // if(standard_base()==false) error_report("Warning, non standard base, value may change",0,1);
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
        if(vb<BIN_BASE || vb>MAX_BASE) {
            error_report("ERROR, base not allowed",0,1);
            vb=DEC_BASE;
        }
        else if(vb>HEX_BASE) error_report("WARNING, base>16",0,1);
        variable_base=vb;
        check();
    }
    void set_unit(const unit &uni) {
        if(uni.null_unit()==false) {
            dim_unit=true;
            variable_unit=uni;
        }
        else error_report("Error,impossible set_unit",1,1);
    }
    //set new unit changing the value
    void change_unit(const unit &uni) {
        if(uni.null_unit()==false) {
            bool ch=true;
            if(dim_unit==false) {
                dim_unit=true;
                ch=false;
            }
            if(numeric_value==false) ch=false;
            if(same_magnitude(uni)==false) {
                ch=false;
                error_report("Warning, different magnitude in variable",1,1);
            }
            if(ch==true) {
                double x;
                x=get_standard_value();
                set_unit(uni);
                set_value_from_standard(x);
            }
            else set_unit(uni);
            check();
        }
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
        }
        if(numeric_value==false) {
            error_report("ERROR,rouding off a non numerica value",1,1);
        }
        check();
    }
    void clear_unit() {
        dim_unit=false;
        variable_unit.clear();
    }
    void clear_value() {
        numeric_value=false;
        value=0;
    }
    void clear() {
        clear_unit();
        erase_name();
        set_base();
        clear_value();
    }

    //ACCESS
    //returns the magnitude of the variable unit
    magnitude_id mag_id() const {
        magnitude_id m=0;
        if(dim_unit==true) m=variable_unit.mag_id();
        return m;
    }
    unit_id get_unit_id() const {
        unit_id i=0;
        if(dim_unit==true) i=variable_unit.get_id();
        return i;
    }
    unit get_unit() const {
        return variable_unit;
    }
    string get_name() const {
        return name;
    }
    double get_value() const {
        if(standard_base()==false) error_report("Warning,non standard base,returning value in DEC",1,1);
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
    bool have_unit() const {
        return dim_unit;
    }
    bool have_name() const {
        return !name.empty();
    }
    bool have_value() const {
        return numeric_value;
    }
    //return true if are the same magnitude
    bool same_magnitude(const variable &other)const {
        return variable_unit.same_magnitude(other.variable_unit);
    }
    bool same_magnitude(const unit &other) const {
        return variable_unit.same_magnitude(other);
    }
    //return true if has the same value (only checks value!!!)
    bool same_value(const variable &other) const {
        if(have_value()==false || other.have_value()==false) return false;
        else if(value==other.value) return true;
        else return false;
    }
    bool same_unit(const variable &other) const {
        return variable_unit.same_unit(other.variable_unit);
    }
    string show_value() const {
        string val;
        if(have_value()==true)        val=to_base(value,variable_base);
        else        error_report("ERROR,not value to return",1,1);
        return val;
    }

    void show(ostream &out=cout) {
        if(have_name()) out<<name<<":";
        if(have_value()) out<<value;
        if(have_unit()) out<<"   "<<variable_unit;
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
    //operator==
    bool operator==(const variable &var2) const { //check if the value of variables and magnitudes are equal
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
        result.erase_name();
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
                    result.set_unit(unid2);
                }
                else { //if its no the same magnitude, just multiply value and units
                    cout<<"here\n";
                    double x=result.get_value();
                    double y=other.get_value();
                    x=x*y;
                    result.set_value(x);
                    unit r;
                    r=result.variable_unit*other.variable_unit;
                    (result.variable_unit).show();
                    cout<<endl<<endl;
                    (other.variable_unit).show();
                    cout<<endl<<endl;
                    r.show();
                    cout<<endl;
                    result.set_unit(r); //problem with pointers!!!
                    cout<<"finish\n";
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
        else error_report("ERROR OPERATING (not value in var)",1,1);
        result.erase_name(); //CHANGE?
        result.check();
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
                result.set_unit((result.variable_unit/result.variable_unit));
                result.set_value_from_standard(x);
            }
            else { //if its no the same magnitude, just multiply value and units
                double x=result.get_value();
                double y=other.get_value();
                x=x/y;
                result.set_value(x);
                result.set_unit((result.variable_unit/other.variable_unit));
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
    //check if is possible to operate
    bool can_operate_with(const variable &var2) const {
        bool b=true;
        bool un1=(*this).have_unit();
        bool un2=var2.have_unit();
        bool v1=(*this).have_value();
        bool v2=var2.have_value();
        if(!v1 || !v2) b=false; //if one of them dont have numeric_value
        // else if((un1 && !un2) || (!un1 && un2)) b=false; //if one of them has unit but the other dont
        else if(un1 && un2) { //if both have units, it has to be the same magnitude
            if(same_magnitude(var2)==false) b=false;
        }
        return b;
    }

    string to_base(int v, base b)const {
        bool neg=false;
        string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string result;
        if(b<BIN_BASE || b>MAX_BASE) {
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
        if(b<BIN_BASE || b>MAX_BASE) {
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
