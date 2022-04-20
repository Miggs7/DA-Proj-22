#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>
#include "info.hpp"

using namespace std;

//! Compara a duração das encomendas
//! \param a- 1º encomenda
//! \param b- 2º encomenda
//! \return true- se duração de "a" menor ou igual à duração de "b"
//! \return false- se duração de "a" maior que duração de "b"
bool compararEnc(Encomenda a, Encomenda b){
    return(a.getDurar()>=b.getDurar());
}
int main() {
    vector<Encomenda> encos;//vetor para armazenar as encomendas

    string encomendasfile("encomendas.txt"); //Ficheiro onde se encontram os dados
    string line;
    ifstream input_file(encomendasfile);
    //Verificar se a stream está associada a um ficheiro
    if(!input_file.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<encomendasfile<<endl;
    }
    //leitura encomendas
    while(std::getline(input_file,line)){
        char *dup = strdup(line.c_str());
        int vol = atoi(strtok(dup," "));
        int peso = atoi(strtok(NULL," "));
        int recompensa = atoi(strtok(NULL," "));
        int duracao = atoi(strtok(NULL," "));
        free(dup);
        Encomenda temp(vol,peso,recompensa,duracao);
        encos.push_back(temp);
    }

    int TotalEncomendas=encos.size(); // Guarda o número de encomendas total

    //Ordenar as encomendas por ordem crescente de duração
    std::sort(encos.begin(),encos.end(), compararEnc);

    vector<Encomenda> Pedidos;//Vetor para armazenar os Pedidos a realizar

    int temp=28800; // Segundos do periodo 9-17
    float totaltemp=0; //Guarda o tempo total usado pelas encomendas
    int sum=0;
    //Descobrir as encomendas para entrega
    for(int i=0;i<encos.size();i++){
        if(temp-encos.at(i).getDurar()>=0){
            temp-=encos.at(i).getDurar();
            Encomenda encomenda(encos.at(i).getVol(),encos.at(i).getPeso(),0,encos.at(i).getDurar()); //Serve só para guardar no vetor Pedido(recompensa nao necessaria)
            Pedidos.push_back(encomenda);
           // totaltemp+=encos.at(i).getDurar();
           sum+=encos.at(i).getDurar();;
           totaltemp+=sum;

        }
    }

    cout<<"Média:"<<(totaltemp/(float)Pedidos.size())<<endl;

    int pp=0;//Serve só pare ver o Peso total dos Pedidos
    int vv=0;//Serve só para ver o Volume total dos Pedidos
    for (int i = 0; i < Pedidos.size(); i++) {
        pp+=Pedidos.at(i).getPeso();
        vv+=Pedidos.at(i).getVol();
    }
    cout<<"Nº Pedidos: "<<Pedidos.size()<<" Peso total:"<<pp<<" Vol total:"<<vv<<endl;
    cout<<"Eficiencia="<<(Pedidos.size()/(float)TotalEncomendas)*100<<"%"<<endl;
    return 0;
}