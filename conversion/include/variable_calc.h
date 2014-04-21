/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca*/
/*
Fermath Project:Variable Calculus
Version:0.9.3
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

//variable calculate(const variable &var1,const variable &var2,operation_id oper)
