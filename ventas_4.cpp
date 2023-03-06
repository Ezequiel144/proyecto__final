#include<iostream>
#include<fstream>
#include<array>
#include<vector>

using namespace std;

template<typename T>

ostream& writeblock(ostream& os,const T& block){

    return os.write(reinterpret_cast<const char*>(&block),sizeof(block));
}

// - Estructuras - //
struct Venta{
    unsigned mes, importe;
};
vector<Venta> ventasVendedor1;


// - Prototypos - //
void promedio(array<array<array<unsigned,12>,3>,4>);
unsigned mayor(array<array<array<unsigned,12>,3>,4>);
void mayorVendedores(array<array<unsigned,12>,3>);
//unsigned mayor(array<array<array<unsigned,12>,3>,4>, array<unsigned,3> &);
array<unsigned,3> ordenamiendo_asc(array<array<array<unsigned,12>,3>,4>);

int main(){
    array<string,3> vendedores{"vendedor 1","vendedor 2","vendedor 3"};
    array<array<array<unsigned,12>,3>,4> total{};
    array<std::array<unsigned,12>,3> totalDos{};
    
    fstream archivo;
    archivo.open("datos_entrada.txt",ios::in);
    if(archivo){
        cout<<"Leyendo archivo\n";
        for(unsigned vent,mes,reg,cant; archivo >> reg >> vent >> mes >> cant ;){
        total.at(reg-1).at(vent-1).at(mes-1) += cant;
        totalDos.at(vent-1).at(mes-1) += cant;
        if(vent==1){
                ventasVendedor1.push_back({mes, cant});
            }
        }
    }

    /*ofstream out("ventas",std::ios::binary);*/
    ofstream outVend1("vendedor1", ios::binary);

    //Mostrando datos//
    for(int i=0; i<4 ; i++){
        cout<<"\n - Region "<<i+1<<" -\n";
        for(int j=0; j<3 ; j++){
            cout<<"\n"<<"Vendedor "<<j+1<<"\n\n";
            for(int k=0; k<12 ; k++){
                cout<<"mes "<<k+1<<"->cant: "<<total[i][j][k]<<"\n";
            }
        }
    }
    
    ofstream out("ventas",std::ios::binary);
    writeblock(out,total);
     for(auto i: ventasVendedor1)
        writeblock(outVend1, i);

    cout<<" \n- Promedio de vendedores - ";
    promedio(total);

    /*cout<<"\n\n- El vendedor con la mayor venta es "<<vendedores.at(mayor(total));*/

    // - otra manera del mayor - //
    
    /*cout<<"\nvendedor  1 ---> cant: "<<cantidades[0];
    cout<<"\nvendedor  2 ---> cant: "<<cantidades[1];
    cout<<"\nvendedor  3 ---> cant: "<<cantidades[2];*/
    cout<<"\n - ordenamiento ascendente de los vendedores con mayor cant. de ventas - ";
    for(unsigned i{0}; i < 3;i++){
        cout<<"\n"<<i+1<<")"<<ordenamiendo_asc(total).at(i);
    }
    cout<<"\n- El vendedor con la mayor ventas es -> "<<vendedores.at(mayor(total))<<" con la cantidad de "<<ordenamiendo_asc(total).at(0);

    cout<<"\n\n - Mayores ventas por mes - \n";
    mayorVendedores(totalDos);

}


void promedio(array<array<array<unsigned,12>,3>,4> total){
    //array<unsigned,3> promed{0,0,0};
    unsigned prom_ven_1{0};
    unsigned cont_1 = 0;
    unsigned prom_ven_2{0};
    unsigned cont_2 = 0;
    unsigned prom_ven_3{0};
    unsigned cont_3 = 0;
    for(unsigned i{0};i<4;i++){
        for(unsigned j{0};j<3;j++){
            for(unsigned k{0};k<12;k++){
                if(total[i][j][k] != 0 and total[i][j][k] == total[i][0][k]){
                    //promed.at(0) += total[i][j][k];
                    prom_ven_1 += total[i][j][k];
                    cont_1++;
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][1][k]){
                    //promed.at(1) += total[i][j][k];
                    prom_ven_2 += total[i][j][k];
                    cont_2++;
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][2][k]){
                    //promed.at(2) += total[i][j][k];
                    prom_ven_3 += total[i][j][k];
                    cont_3++;
                }
            }
        }
    }
    
    //cout<<"\nPromedio del vendedor 1: "<<(promed[0]/*/cont_1*/);
    //cout<<"\nPromedio del vendedor 2: "<<(promed[1]/*/cont_2*/);
    //cout<<"\nPromedio del vendedor 3: "<<(promed[2]/*/cont_3*/);
    
    
    cout<<"\nPromedio del vendedor 1: "<<prom_ven_1/cont_1;
    cout<<"\nPromedio del vendedor 2: "<<prom_ven_2/cont_2;
    cout<<"\nPromedio del vendedor 3: "<<prom_ven_3/cont_3;
}
unsigned mayor(array<array<array<unsigned,12>,3>,4> total){
    array<unsigned,3> mayor_vect{0,0,0};
    unsigned cont_1 {0};
    unsigned cont_2 {0};
    unsigned cont_3 {0};
    for(unsigned i{0};i<4;i++){
        for(unsigned j{0};j<3;j++){
            for(unsigned k{0};k<12;k++){
                if(total[i][j][k] != 0 and total[i][j][k] == total[i][0][k]){
                    mayor_vect.at(0) += total[i][j][k];
                    cont_1++;
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][1][k]){
                    mayor_vect.at(1) += total[i][j][k];
                    cont_2++;
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][2][k]){
                    mayor_vect.at(2) += total[i][j][k];
                    cont_3++;
                }
            }
        }
    }

    unsigned aux{0};

    for(unsigned i{1};i<=2;i++){
       if (mayor_vect[i] > mayor_vect[aux]){
            aux=i;
       }
    }
    return aux;
} 

array<unsigned,3> ordenamiendo_asc(array<array<array<unsigned,12>,3>,4> total){
    array<unsigned,3> order{0,0,0};
    for(unsigned i{0};i<4;i++){
        for(unsigned j{0};j<3;j++){
            for(unsigned k{0};k<12;k++){
                if(total[i][j][k] != 0 and total[i][j][k] == total[i][0][k]){
                    order.at(0) += total[i][j][k];   
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][1][k]){
                    order.at(1) += total[i][j][k];
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][2][k]){
                    order.at(2) += total[i][j][k];
                }
            }
        }
    }

    /* ordenamiento acendente*/
    unsigned aux;
    unsigned min;

    for(unsigned i{0};i < 3-1;i++){
        min = i;
        for(unsigned j{i+1}; j < 3;j++){
            if(order.at(j) > order.at(min)){
                min = j;
            }
        }
        aux = order[i];
        order[i] = order[min];
        order[min] = aux;
    }
    return order;
}

void mayorVendedores(std::array<std::array<unsigned,12>,3> vect){
    unsigned aux {0};
    for(int i=0;i<3;++i){
        cout<<" \n- Vendedor "<<i+1<<" - \n";
        for(int j=1;j<12;++j){
            if(vect[i][j] > vect[i][aux]){
                aux = j;
            }
        }
        cout<<"mes con mayor venta es el mes "<<aux + 1<<"\n";    
        
    }
}
/*
unsigned mayor(array<array<array<unsigned,12>,3>,4> total, array<unsigned,3> &lista){
    
    unsigned cont_1 {0};
    unsigned cont_2 {0};
    unsigned cont_3 {0};
    for(unsigned i{0};i<4;i++){
        for(unsigned j{0};j<3;j++){
            for(unsigned k{0};k<12;k++){
                if(total[i][j][k] != 0 and total[i][j][k] == total[i][0][k]){
                    lista.at(0) += total[i][j][k];
                    cont_1++;
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][1][k]){
                    lista.at(1) += total[i][j][k];
                    cont_2++;
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][2][k]){
                    lista.at(2) += total[i][j][k];
                    cont_3++;
                }
            }
        }
    }

    unsigned aux{0};

    for(unsigned i{1};i<=2;i++){
       if (lista[i] > lista[aux]){
            aux=i;
       }
    }
    return aux;
} */
/*
array<unsigned,3> ordenamiendo_asc(array<array<array<unsigned,12>,3>,4> total,array<unsigned,3> &lista){
    array<unsigned,3> order{0,0,0};
    unsigned cont_1 = 0;
    unsigned cont_2 = 0;
    unsigned cont_3 = 0;
    for(unsigned i{0};i<4;i++){
        for(unsigned j{0};j<3;j++){
            for(unsigned k{0};k<12;k++){
                if(total[i][j][k] != 0 and total[i][j][k] == total[i][0][k]){
                    order.at(0) += total[i][j][k];
                    cont_1++;
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][1][k]){
                    order.at(1) += total[i][j][k];
                    cont_2++;
                }
                else if(total[i][j][k] != 0 and total[i][j][k] == total[i][2][k]){
                    order.at(2) += total[i][j][k];
                    cont_3++;
                }
            }
        }
    }

    lista[0] = order[0];
    lista[1] = order[1];
    lista[2] = order[2];

    unsigned aux;
    unsigned min;

    for(unsigned i{0};i < 3-1;i++){
        min = i;
        for(unsigned j{i+1}; j < 3;j++){
            if(order.at(j) > order.at(min)){
                min = j;
            }
        }
        aux = order[i];
        order[i] = order[min];
        order[min] = aux;
    }
    return order;
}*/