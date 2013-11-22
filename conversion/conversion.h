/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Conversion Class
Version:0.1
*/

class conversion {
private:
    vector<int> operations;
    vector<double> data;
public:
    //CONSTRUCTORS
    conversion() {
    }
    conversion(vector <int> &op,vector<double> &dat) {
        operations=op;
        data=dat;
    }
    //add a new binary operation and data for conversion
    void add_operation(int op,double dat) {
        operations.push_back(op);
        data.push_back(dat);
    }
    //add a new unary operation for conversion
    void add_operation(int op) {
        operations.push_back(op+100);
    }
    //convert d1 using the operations and data provided (conversion from unit)
    double convert(double d1) {
        int tam=operations.size();
        for(int i=0; i<tam; i++) {
            if(operations[i]<=100)   d1=calc(operations[i],d1,data[i]); //binary operation
            if(operations[i]>100) d1=calc(operations[i]-100,d1); //unary operation
        }
        return d1;
    }
    //Inverse conversion, this do the operation in the inverse order and changing operation when needed (conversion to unit)
    double inverse_convert(double d1) {
        int op;
        for(int i=operations.size()-1; i>=0; i--) {
            op=operations[i];
            if(op%2==0) op--;
            else op++;
            if(operations[i]<=100) d1=calc(op,d1,data[i]);
            if(operations[i]>100) d1=calc(op-100,d1);
        }
        return d1;
    }
    //if there is no conversion (the unit is the standard unit of magnitude)
    bool null_conversion() {
        if(operations.size()==0) return true;
        return false;
    }
    //erase all operations
    void clear() {
        operations.clear();
        data.clear();
    }
};
