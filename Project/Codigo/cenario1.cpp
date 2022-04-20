#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>
#include <map>
#include "info.hpp"
#include "cenario1.hpp"

using namespace std;

void escolhertruck(vector<Encomenda>& encos, vector<Carrinha>& trucks,vector<Encomenda>& pedidos,vector<Carrinha>& estafetas ){


    int flag=0; // Flag para indicar se uma carrinha foi usada para guardar encomendas

    for(auto truck : trucks) {
       flag=0;
        if(encos.empty())
            break;
        for(int i = 0; i < (int) encos.size(); i++){
                if(FitsInTruck(truck,encos.at(i)) == 1){
                    Encomenda encomendausada(encos.at(i).getVol(),encos.at(i).getPeso(),0,0); //Serve para inserir nos pedidos (duracao e valor nao necessarios)
                    pedidos.push_back(encomendausada);
                    encos.erase(encos.begin()+i);
                    i--;
                    flag=1;  //Flag fica a 1 se foi intruduzida uma encomenda na carrinha atual
                }
            }
        //Ver se foi inserida uma encomenda na carrinha atual
        //Se for, quer dizer que a carrinha é usada para encomendas
        if(flag==1){
            Carrinha temp(truck.getVolMax(),truck.getPesoMax(),0); //Serve para inserir nas estafetas(valor do custo nao interessa para problema)
            estafetas.push_back(temp);
        }
    }
    return;
}

int main() {

    vector<Encomenda> encos;// Vetor para guardar as encomendas
    vector<Carrinha> trucks;//Vetor para guardar as carrinhas

    string encomendasfile("encomendas.txt");//Ficheiro onde se encontram os dados das encomendas
    string carrinhasfile("carrinhas.txt");//Ficheiro onde se encontram os dados das carrinhas
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
    int TotalEncomendas=encos.size();

    std::ifstream input_file2(carrinhasfile);
    //Verificar se a stream está associada a um ficheiro
    if(!input_file2.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<carrinhasfile<<endl;
    }
    //leitura carrinhas
    while(std::getline(input_file2,line)){
        char *dup = strdup(line.c_str());
        int volMax = atoi(strtok(dup," "));
        int pesoMax = atoi(strtok(NULL," "));
        int custo  = atoi(strtok(NULL," "));
        free(dup);
        Carrinha temp2(volMax,pesoMax,custo);
        trucks.push_back(temp2);
    }

    //Ordenar as carrinhas de forma decrescente de Capacidade(Peso+Vol)
    std::sort(trucks.begin(),trucks.end(), compararCarrinhas);

    //Ordenar as encomendas de forma decrescente de Capacidade(Peso+Vol)
    std::sort(encos.begin(),encos.end(), compararEnc);

    vector<Carrinha> Estafetas; //Vetor para guardar as carrinhas usadas
    vector<Encomenda> Pedidos;   //Vetor para guardar as encomendas guardadas

    //Chamar função
    escolhertruck(encos,trucks,Pedidos,Estafetas);


    int pp=0;   //Variáveis para contar o Peso e Volume total
    int vv=0;   // das carrinhas usadas e encomendas guardadas

    for (int i=0; i<Estafetas.size();i++){
        pp+=Estafetas.at(i).getPesoMax();
        vv+=Estafetas.at(i).getVolMax();

    }

    cout<<"Nº Estafetas: "<<Estafetas.size()<<" PesoTotal: " <<pp<<" Vol total:"<<vv<<endl;

    pp=0;
    vv=0;

   for (int i = 0; i < Pedidos.size(); i++) {
       pp+=Pedidos.at(i).getPeso();
       vv+=Pedidos.at(i).getVol();
    }

    cout<<"Nº Pedidos: "<<Pedidos.size()<<" Peso total:"<<pp<<" Vol total:"<<vv<<endl;
    cout<<"Eficiencia="<<(Pedidos.size()/(float)TotalEncomendas)*100<<"%"<<endl;
    return 0;
}
