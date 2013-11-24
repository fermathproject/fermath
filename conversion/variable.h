/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Magnitude Class
Version:0.2
*/
class variable {
private:
    float val;
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

    int magnitude() {
        int m=-1;
        if(dim_unit==true) m=unidad->get_id();
        return m;
    }


};
