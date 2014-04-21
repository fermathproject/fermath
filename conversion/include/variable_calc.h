/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca*/
/*
Fermath Project:Variable Calculus
Version:0.9.4
*/

//Operations with variables
#include "variable.h"
//Binary operations
variable calc_add(const variable &var1,const variable &var2,const data_src &src) {
    variable result;
    result=var1.add(var2,src);
    return result;
}
variable calc_substract(const variable &var1,const variable &var2,const data_src &src) {
    variable result;
    result=var1.deduct(var2,src);
    return result;
}
variable calc_multiply(const variable &var1,const variable &var2,const data_src &src) {
    variable result;
    result=var1.multiply(var2,src);
    return result;
}
variable calc_divide(const variable &var1,const variable &var2,const data_src &src) {
    variable result;
    result=var1.divide(var2,src);
    return result;
}

//WARNING, only with no dimensional variables!!!
variable calc_pow(const variable &var1,const variable &var2,const data_src &src) {
    data_type d1,d2,res;
    if(var2.have_unit()==true || var1.have_unit()==true) error_report(user_error,"pow not posibble with units (discarting units)",1,1); //FIXME ¿?
    d1=var1.get_value();
    d2=var2.get_value();
    res=pow(d1,d2);
    variable result(res);
    return result;
}
//var1^(1/var1)
//WARNING, only with no dimensional variables!!!
variable calc_root(const variable &var1,const variable &var2) {
    data_type d1,d2,res;
    if(var2.have_unit()==true || var1.have_unit()==true) error_report(user_error,"root not posibble with units (discarting units)",1,1); //FIXME ¿?
    d1=var1.get_value();
    d2=var2.get_value();
    res=pow(d1,1.0/d2);
    variable result(res);
    return result;
}
//Unary operations
//var^2
variable calc_square(const variable &var1,const data_src &src) {
    return var1.add(var1,src);
}

//WARNING, only with no dimensional variables!!!
variable calc_square_root(const variable &var1) {
    if(var1.have_unit()==true) error_report(user_error,"square root not possible with units (discarting units)",1,1); //FIXME¿?
    data_type d1,res;
    d1=var1.get_value();
    res=sqrt(d1);
    variable result(res);
    return result;
}

variable calculate(const variable &var1,const variable &var2,operation_id oper,const data_src &src) {
    variable var;
    if(oper==0 || oper>binary_max) error_report(user_error,"operation id not valid",1,1);
    else {
        switch(oper) {
        case 1:
            var=calc_add(var1,var2,src);
            break;
        case 2:
            var=calc_substract(var1,var2,src);
            break;
        case 3:
            var=calc_multiply(var1,var2,src);
            break;
        case 4:
            var=calc_divide(var1,var2,src);
            break;
        case 5:
            var=calc_pow(var1,var2,src);
            break;
        case 6:
            var=calc_root(var1,var2);
            break;
        }
    }
    return var;
}
variable calculate(const variable &var,operation_id oper,const data_src &src) {
    variable res;
    if(oper==0 || oper>unary_max) error_report(user_error,"operation id not valid",1,1);
    else {
        switch(oper) {
        case 1:
            res=calc_square(var,src);
            break;
        case 2:
            res=calc_square_root(var);
            break;
        }
    }
    return res;
}
