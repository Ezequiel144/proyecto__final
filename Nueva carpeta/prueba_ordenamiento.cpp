#include<iostream>
#include<array>

using namespace std;

// - Prototype - //

void ordenamiento_ascend(array<unsigned,5>&);

int main(){
    array<unsigned,5> vect{4,1,6,3,9};

    cout<<" - Array sin ordenar ->\t";

    for(unsigned i{0};i < 5;i++){
        cout<<"\t"<<vect[i];
    }

    ordenamiento_ascend(vect);

    cout<<"\n - Array ordenado ascendente ->";

    for(unsigned i{0};i < 5;i++){
        cout<<"\t"<<vect[i];
    }
    

}  

void ordenamiento_ascend(array<unsigned,5> &vect){
    unsigned aux;
    unsigned min;

    for(unsigned i{0};i < 5-1;i++){
        min = i;
        for(unsigned j{i+1}; j < 5;j++){
            if(vect.at(j) < vect.at(min)){
                min = j;
            }
        }
        aux = vect[i];
        vect[i] = vect[min];
        vect[min] = aux;
    }
}

