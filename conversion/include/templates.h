/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
/*
Fermath Project:Templates
Version:0.4
*/
//Some templates for write/reading with vectors, neccesary for the classes of Fermeth


//Writes a vector on out ostream, if not osteam provided, v is written on standard output cout
template <typename T>
void write_vector(const vector<T> &v,ostream &out=cout) {
    int siz=v.size();
    for(int i=0; i<siz-1; i++) {
        out<<v[i]<<" ";
    }
    out<<v[siz-1];
}


//Writes an element in a binary file
template <typename T>
void binary_write(T &element,ofstream &out) {
    out.write(reinterpret_cast<char *>(&element),sizeof(T));
}
//Reads an element from a binary file
template <typename T>
void binary_read(T &element,ifstream &input) {
    input.read(reinterpret_cast<char *>(&element),sizeof(T));
}
//Writes a vector in a binary file, it writes the size of the vector first (unsigned)
template <typename T>
void binary_write_vector(vector<T> &v,ofstream &out) {
    unsigned siz=v.size();
    T elem;
    binary_write(siz,out); //writes vector size
    for(int i=0; i<siz; i++) {
        elem=v[i];
        binary_write(elem,out); //writes each element
    }
    //  out.write(reinterpret_cast<char *>(&v[0]),sizeof(T)*siz);//writes all the vector
}
//Reads a vector from a binary file
template <typename T>
void binary_read_vector(vector<T> &v,ifstream &input) {
    unsigned siz;
    binary_read(siz,input);//read vector size
    T elem;
    v.clear();
    v.reserve(siz); //so its not necessary to change vector capacity later
    for(int i=0; i<siz; i++) {
        binary_read(elem,input);
        v.push_back(elem);
    }
}
//Read/Write string cases (usign a write as a vector)
void binary_write(string &element,ofstream &out) {
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
//read/write versions for vector<string>
void binary_write_vector(vector<string> &v,ofstream &out) {
    unsigned siz=v.size();
    string elem;
    binary_write(siz,out); //writes vector size
    for(int i=0; i<siz; i++) {
        elem=v[i];
        binary_write(elem,out); //writes each element
    }
}

void binary_read_vector(vector<string> &v,ifstream &input) {
    unsigned siz;
    binary_read(siz,input);//read vector size
    string elem;
    v.clear();
    v.reserve(siz); //so its not necessary to change vector capacity later
    for(int i=0; i<siz; i++) {
        binary_read(elem,input);
        v.push_back(elem);
    }
}


