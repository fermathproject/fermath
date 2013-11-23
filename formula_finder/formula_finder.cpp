// *************************************************************************************** //
// Test del algoritmo para la búsqueda y enlazamiento de distintas fórmulas
//
// Cada fórmula se representa como una relación entre distintas magnitudes cada magnitud
// posee un numero identificador, por tanto, cada fórmula es representada en este programa
// como un vector de enteros, en los que no importa el orden de estos.
// Ejemplo:
// la formula F=M*A se podria representar como {1,2,3} (siendo la id de F 1, de M 2 y
// de A 3), también se puede representar como {2,1,3}, pues el orden no importa.
//
// En este programa, tenemos un vector de formulas (esto se representa como un
// vector<vector<int> >),unos datos iniciales y una magnitud objetivo, el algoritmo
// buscará entre la lista de fórmulas aquellas que son necesarias para relacionar los
// datos con la magnitud buscada
//
//
// (C) Programmed by:
// Antonio Jimenez Martínez
// Andrés Ortiz Corrales
// Mariano Palomo Villafranca
// *************************************************************************************** //
#include <iostream>
#include <vector>
using namespace std;

/*********************************************************************/
// Mostrar un vector de vectores de int
void out_forms(const vector<vector<int> > &forms) {
    vector<vector<int> >:: const_iterator it1;
    vector<int>::  const_iterator it2;
    for(it1=forms.begin(); it1!=forms.end(); ++it1) {
        for(it2=(*it1).begin(); it2!=(*it1).end(); ++it2) {
            cout<<*it2<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
/*********************************************************************/
// Mostrar un vector de int
void out_forms(const vector<int>   &forms) {
    vector<int>::  const_iterator it1;
    for(it1=forms.begin(); it1!=forms.end(); ++it1) {
        cout<<*it1<<" ";
    }
    cout<<endl;
}
/*********************************************************************/
// Comprueba si el elemento n esta en el vector v
bool in_vector(const int &n,const vector<int> &v) {
    vector<int>::  const_iterator it;
    for(it=v.begin(); it!=v.end(); ++it) {
        if(*it==n)return true;
    }
    return false;
}
/*********************************************************************/
// Comprueba si la formula da resultado inmediato con los datos
bool form_with_solution(const int &resultado,const vector<int> &data,const vector<int> &formula) {
    if(in_vector(resultado,formula)) { //comprueba que resultado esté en formula
        vector<int>::  const_iterator it;
        for(it=formula.begin(); it!=formula.end(); ++it) { //comprueba que todas las magnitudes de formula esten en los datos
            if((*it!=resultado) && (!in_vector(*it,data))) return false;
        }
        return true;
    }
    return false;
}
/*********************************************************************/
// Devuelve los elementos de la formula que no esten en datos ni son resultado
vector<int> not_in_data(const int &resultado,const vector<int> &data,const vector<int> &formula) {
    vector<int> v;
    vector<int>:: const_iterator it;
    for(it=formula.begin(); it!=formula.end(); ++it) {
        if((*it!=resultado) && (!in_vector(*it,data))) v.push_back(*it);
    }
    return v;
}
/*********************************************************************/
// Comprueba si con los datos que tiene se puede solucionar
bool puede(const int &res,vector<int> datos,vector< vector <int > > formulas) {
    vector< vector<int> > formulas_aux;
    vector<int> aux;
    vector< vector<int> >::iterator it1=formulas.begin();
    for(; it1!=formulas.end();) {
        if(in_vector(res,*it1)) {
            formulas_aux.push_back(*it1);
            it1=formulas.erase(it1);
        }
        else ++it1;
    }
    for(it1=formulas_aux.begin(); it1!=formulas_aux.end(); ++it1) {
        if(form_with_solution(res,datos,*it1)) {
            return true;
        }
    }
    vector< int> ::iterator it2;
    bool puedentodos;
    for(it1=formulas_aux.begin(); it1!=formulas_aux.end(); ++it1) {
        aux=not_in_data(res,datos,*it1);
        puedentodos=false;
        for(it2=aux.begin(); it2!=aux.end() && !puedentodos; ++it2) {
            if(puede(*it2,datos,formulas)) datos.push_back(*it2);
            else puedentodos=true;
        }
        if(!puedentodos)return true;
    }
    return false;
}
/*********************************************************************/
// Calcula la relacion de fórmulas  con los resultados y datos de forma recursiva
vector< vector<int> > calcular_formulas(const int &res,vector<int> datos,vector< vector<int> > formulas) {
    vector< vector<int> > salida;
    vector< vector<int> > formulas_aux;
    vector<int> aux;
    vector< vector<int> >::iterator it1=formulas.begin();
    for(; it1!=formulas.end();) {
        if(in_vector(res,*it1)) {
            formulas_aux.push_back(*it1);
            it1=formulas.erase(it1);
        }
        else ++it1;
    }
    for(it1=formulas_aux.begin(); it1!=formulas_aux.end(); ++it1) {
        if(form_with_solution(res,datos,*it1)) {
            salida.push_back(*it1);
            datos.push_back(res);
            return salida;
        }
    }
    for(it1=formulas_aux.begin(); it1!=formulas_aux.end(); ++it1) {
        aux=not_in_data(res,datos,*it1);
        for(int j=0; j<aux.size(); j++) {
            vector<vector <int> > v2;
            v2=calcular_formulas(aux[j],datos,formulas);
            if(v2.size()>0) {
                datos.push_back(aux[j]);
                if((form_with_solution(res,datos,*it1)) || ((j+1)<aux.size() && puede(aux[j+1],datos,formulas))) {
                    salida.insert(salida.end(),v2.begin(),v2.end());
                }
            }
        }
        if(salida.size()>0) {
            salida.push_back(*it1);
            return salida;
        }
    }
    return salida;
}
/*********************************************************************/
// Test para la lectura de fórmulas y datos
main() {
    vector<int> data;
    vector< vector<int> > formulas;
    vector<int> a;
    int n,n2=1,res;
    cin>>res;
    cin>>n2;
    do {
        data.push_back(n2);
        cin>>n2;   // out_forms(formulas);
    }
    while(n2>0);
    n2=1;
    cin>>n; //numero de formulas
    for(int i=0; i<n; i++) {
        a.clear();
        cin>>n2;
        do {
            a.push_back(n2);
            cin>>n2;
        }
        while(n2>0);
        n2=1;
        formulas.push_back(a);
    }
    for(int i=0; i<data.size(); i++) {
        cout<<data[i]<<" ";
    }
    cout<<endl<<res<<endl;
    cout<<"----\n";
    // out_forms(formulas);
    cout<<"-----\n";
    vector<vector<int> > formres;
    formres=calcular_formulas(res,data,formulas);
    out_forms(formres);
}
