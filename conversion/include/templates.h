/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Templates
Version:0.9.2
*/
//Some templates for write/reading with vectors, neccesary for the classes of Fermeth

typedef unsigned short max_size;

//Writes a vector on out ostream, if not osteam provided, v is written on standard output cout
template <typename T>
void write_vector(const vector<T> &v,ostream &out=cout) {
    max_size siz=v.size();
    for(int i=0; i<siz-1; i++) {
        out<<v[i]<<" ";
    }
    out<<v[siz-1];
}

//Writes an element in a binary file
template <typename T>
void binary_write(const T &element,ofstream &out) {
    out.write((char *)&element,sizeof(T));
}
//Reads an element from a binary file
template <typename T>
void binary_read(const T &element,ifstream &input) {
    input.read((char *) &element,sizeof(T));
}
//Writes a vector in a binary file, it writes the size of the vector first (unsigned)
template <typename T>
void binary_write_vector(const vector<T> &v,ofstream &out) {
    max_size siz=v.size();
    T elem;
    binary_write(siz,out); //writes vector size
    for(max_size i=0; i<siz; i++) {
        elem=v[i];
        binary_write(elem,out); //writes each element
    }
    //  out.write(reinterpret_cast<char *>(&v[0]),sizeof(T)*siz);//writes all the vector
}
//Reads a vector from a binary file
template <typename T>
void binary_read_vector(vector<T> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read vector size
    T elem;
    v.clear();
    v.reserve(siz); //so its not necessary to change vector capacity later
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        v.push_back(elem);
    }
}
//Read/Write string cases (usign a write as a vector)
void binary_write(const string &element,ofstream &out) {
    vector<char> data(element.begin(), element.end());
    binary_write_vector(data,out);
}

void binary_read(string &element,ifstream &input) {
    vector<char> data;
    binary_read_vector(data,input);
    element.clear();
    string str(data.begin(),data.end());
    element=str;
}

//Writes an element in a binary file
template <typename T,typename P>
void binary_write(const pair<T,P> &element,ofstream &out) {
    binary_write(element.first,out);
    binary_write(element.second,out);
}
//Reads an element from a binary file
template <typename T,typename P>
void binary_read(const pair<T,P> &element,ifstream &input) {
    binary_read(element.first,input);
    binary_read(element.second,input);
}
//read/write versions for vector<string>
void binary_write_vector(const vector<string> &v,ofstream &out) {
    max_size siz=v.size();
    string elem;
    binary_write(siz,out); //writes vector size
    for(max_size i=0; i<siz; i++) {
        elem=v[i];
        binary_write(elem,out); //writes each element
    }
}

void binary_read_vector(vector<string> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read vector size
    string elem;
    v.clear();
    v.reserve(siz); //so its not necessary to change vector capacity later
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        v.push_back(elem);
    }
}

template <typename T>
void add_vector(vector<T> &v1,const vector<T> &v2) { //add the elements of the second vector that are not in the first
    max_size size=v2.size();
    bool is=false;
    T elem;
    for(max_size i=0; i<size; i++) {
        elem=v2[i];
        for(max_size j=0; (j<v1.size()) && (is==false); j++) {
            if(elem==v1[j]) is=true; //check if an element is on the vector 1
        }
        if(!is) v1.push_back(elem);
        is=false;
    }
}


//erase one element of the vector<T> if it is equal to x, return true if the element has be erased
template <typename T>
bool erase(vector<T> &v1,const T &x) {
    bool b=false;
    typename vector<T>::iterator it1=v1.begin();
    typename vector<T>::iterator aux1=v1.end();
    while(it1!=aux1 && !b) {
        if((*it1)==x) {
            b=true;
            it1=v1.erase(it1);
        }
        else {
            it1++;
        }
    }
    return b;
}
//same as erase, but comparing an element with a vector of pointers
template <typename T>
bool erase(vector<const T *> &v1,const T &x) {
    bool b=false;
    typename vector<const T *>::iterator it1=v1.begin();
    typename vector<const T *>::iterator aux1=v1.end();
    while(it1!=aux1 && !b) {
        if((*(*it1))==x) {
            b=true;
            it1=v1.erase(it1);
        }
        else {
            it1++;
        }
    }
    return b;
}
//erases a repeated element from each vector
template <typename T>
void simplify_vectors(vector<T> &v1,vector<T> &v2) {
    bool is=false;
    typename vector<T>::iterator it1=v1.begin();
    typename vector<T>::iterator it2=v2.begin();
    while(it1!=v1.end()) {
        while(it2!=v2.end() && !is) {
            if((*it1)==(*it2)) {
                is=true;
                it2=v2.erase(it2);
            }
            it2++;
        }
        if(is==true) {
            it1=v1.erase(it1);
            is=false;
        }
        else {
            it1++;
        }
        it2=v2.begin();
    }
}


//checks that both vectors have the same elements (including repeated) with any order
template <typename T>
bool compare_vector_elements(const vector<T> &v1,const vector<T> &v2) {
    if(v1.size()!=v2.size()) return false;
    bool eq=true;
    bool found;
    vector<bool> checked(v2.size(),false);
    for(max_size i=0; i<v1.size() && eq; i++) {
        found=false;
        for(max_size j=0; j<v2.size() && found==false; j++) {
            if(checked[j]==false) {
                if(v1[i]==v2[j]) { //only checks if it havent been checked yet
                    found=true;
                    checked[j]=true;
                }
            }
        }
        if(found==false) eq=false;
    }
    return eq;
}
template <typename T>
bool compare_vector_elements(const vector<const T *> &v1,const vector<const T *> &v2) {
    if(v1.size()!=v2.size()) return false;
    bool eq=true;
    bool found;
    vector<bool> checked(v2.size(),false);
    for(max_size i=0; i<v1.size() && eq; i++) {
        found=false;
        for(max_size j=0; j<v2.size() && found==false; j++) {
            if(checked[j]==false) {
                if(*v1[i]==*v2[j]) { //only checks if it havent been checked yet
                    found=true;
                    checked[j]=true;
                }
            }
        }
        if(found==false) eq=false;
    }
    return eq;
}


template <typename T>
void show_stack(stack<T> s) {
    while(!s.empty()) {
        cout<<s.top()<<" ";
        s.pop();
    }
    cout << '\n';
}

//format the string to the need of names
string format_string(string s) {
    unsigned int siz=s.size();
    for(unsigned int i=0; i<siz; i++) {
        if(s[i]>'A' && s[i]<'Z') s[i]=s[i]+32; //A..Z -> a..z
        else if(s[i]==165) s[i]=164; //Ñ -> ñ
    }
    return s;
}
