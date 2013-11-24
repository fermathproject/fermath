/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Conversion Class
Version:0.2
*/

//Para realizar operaciones
class operations {
private:
    vector<int> op;
    vector<double> data;
public:
    //CONSTRUCTORS
    operations() {
    }
    operations(int op2,double dat) {
        add_operation(op2,dat);
    }
    operations(int op2) {
        add_operation(op2);
    }
    operations(vector <int> &op2,vector<double> &dat) {
        op=op2;
        data=dat;
    }
    //add a new binary operation and data for conversion
    void add_operation(int op2,double dat) {
        op.push_back(op2);
        data.push_back(dat);
    }
    //add a new unary operation for conversion
    void add_operation(int op2) {
        op.push_back(op2+100);
    }
    //convert d1 using the operations and data provided (conversion from unit)
    double operate(double d1) {
        int tam=op.size();
        for(int i=0; i<tam; i++) {
            if(op[i]<=100)   d1=calc(op[i],d1,data[i]); //binary operation
            if(op[i]>100) d1=calc(op[i]-100,d1); //unary operation
        }
        return d1;
    }
    //Inverse conversion, this do the operation in the inverse order and changing operation when needed (conversion to unit)
    double inverse_operate(double d1) {
        int op2;
        for(int i=op.size()-1; i>=0; i--) {
            op2=op[i];
            if(op2%2==0) op2--;
            else op2++;
            if(op[i]<=100) d1=calc(op2,d1,data[i]);
            if(op[i]>100) d1=calc(op2-100,d1);
        }
        return d1;
    }
    //if there is no conversion (the unit is the standard unit of magnitude)
    bool null_operation() {
        if(op.size()==0) return true;
        return false;
    }
    //erase all operations
    void clear() {
        op.clear();
        data.clear();
    }
};
