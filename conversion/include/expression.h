/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Expression Class
Version:0.6
*/

//This class stores and process an expression with variables using stacks


//(5-3)*3+(2*2)  //inffix notation
//5 3 - 3 * 2 2 * + //suffix notation

//the suffix notation can be represented as:
//5 3 3 2 2
//- * * +
//0 0 1 0 1 0 0 1 1
class expression { //TODO:use variable operators in calc
private:
    string name;
    stack<unsigned> operations;
    stack<variable> data;
    stack<bool> selection; //0=data 1=operation
public:
    //CONSTRUCTORS
    expression() {
    }
    expression(const string &name2,const stack<unsigned> &operations2,const stack<variable> &data2,const stack<bool> &selec) {
        name=name2;
        operations=operations2;
        data=data2;
        selection=selec;
    }
    expression(const stack<unsigned> &operations2,const stack<variable> &data2,const stack<bool> &selec) {
        operations=operations2;
        data=data2;
        selection=selec;
    }

    expression(unsigned op,const variable &var1,const variable &var2) {
        add_data(var1);
        add_data(var2);
        add_operation(op);
    }
    expression(unsigned op,const variable &var) {
        add_data(var);
        add_operation(op);
    }
    void add_data(variable var) {
        data.push(var);
        selection.push(false);
    }
    void add_operation(unsigned op) {
        operations.push(op);
        selection.push(true);
    }
    bool have_name() const {
        return !name.empty();
    }
    string get_name() const {
        return name;
    }
    variable solve_expression()const { //TODO: checking if operation have solution and segmentation fail
        stack<variable> dat=data;
        stack<bool> selec=selection;
        stack<unsigned> op=operations;
        stack<variable> result;
        bool b;
        unsigned o;
        while(selec.empty()==false) {
            b=selec.top();
            selec.pop();
            if(b==false) {
                result.push(dat.top());
                dat.pop();
            }
            if(b==true) {
                o=op.top();
                op.pop();
                solve_operation(result,o); //solve one operation
            }
        }
        return result.top();
    }

    //solve one operation
    void solve_operation(stack<variable> &result,unsigned op) const { //TODO:solve non-numeric operations and check if the operation can be done
        if(op>100) {
            op-=100;
            variable a=result.top();
            result.pop();
            double x=a.get_standard_value();
            x=calc(op,x);
            a.set_value_from_standard(x);
            result.push(a);
        }
        else {
            variable a=result.top();
            result.pop();
            variable b=result.top();
            result.pop();
            //if(a.can_operate_with(b)==false) cout<<"ERROR OPERATING IN EXPRESSION"<<endl;
            double x=a.get_standard_value();
            double y=b.get_standard_value();
            x=calc(op,x,y);
            a.set_value_from_standard(x);
            result.push(a);
        }
    }

private:
    friend ostream  &operator<< (ostream &out, const expression &exp) {
        if(exp.have_name()) out<<exp.name<<"=";
        stack<variable> dat=exp.data;
        stack<bool> selec=exp.selection;
        stack<unsigned> op=exp.operations;
        bool b;
        while(selec.empty()==false) {
            b=selec.top();
            selec.pop();
            if(b==false) {
                out<<dat.top()<<" ";
                dat.pop();
            }
            if(b==true) {
                out<<op.top()<<" ";
                op.pop();
            }
        }
        return out;
    }
    double calc(unsigned cal, double n1,double n2) const { //binary operations
        double r=0;
        switch(cal) {
        case 1:
            r=n1+n2;
            break;
        case 2:
            r=n1-n2;
            break;
        case 3:
            r=n1*n2;
            break;
        case 4:
            if(n2==0) cout<<"error in division(fix this)";
            r=n1/n2;
            break;
        case 5:
            r=pow(n1,n2);
            break;
        case 6:
            if(n2==0) cout<<"error en raiz(fix this)";
            r=pow(n1,1/n2);
            break;
        }
        return r;
    }
    double calc(unsigned cal,double n) const { //unary operations
        double r=0;
        switch(cal) {
        case 1:
            if(n<0) cout<<"error en raiz cuadrada(arreglar esto)";
            r=sqrt(n);
            break;
        case 2:
            r=n*n;
            break;
        case 3:
            r=sin(n);
            break;
        case 4:
            r=asin(n);
            break;
        case 5:
            r=cos(n);
            break;
        case 6:
            r=acos(n);
            break;
        case 7:
            r=tan(n);
            break;
        case 8:
            r=atan(n);
            break;
        case 9:
            r=exp(n);
            break;
        case 10:
            r=log(n);
            break;
            /*case 11:
                r=fabs(n);
                break;*/
        }
        return r;
    }

};
