#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>
#include "cenario2.hpp"
#include "cenario1.hpp"
#include "cenario3.hpp"


using namespace std;

//Complexidade temporal da função: O(n^3)
//Complexidade espacial da função: O(n^3)

int main(int argc, char * argv[]) {
    vector<Encomenda> encos;//Vetor para guardar todas as encomendas
    vector<Carrinha> trucks;//Vetor para guardar todas as carrinhas

    string encomendasfile(argv[1]);//Ficheiro com as encomendas
    string carrinhasfile(argv[2]);//Ficheiro com as carrinhas
    string line;

    ifstream input_file(encomendasfile);
    //Verificar se a stream está associada a um ficheiro
    if(!input_file.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<endl;
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



    std::ifstream input_file2(carrinhasfile);
    //verifica se a stream está associada a um ficheiro
    if(!input_file2.is_open()){
        cout<<"Erro ao abrir o ficheiro:"<<endl;
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

    vector<Carrinha> Estafetas; //Vetor para guardar as carrinhas usadas
    vector<Encomenda> Pedidos; //Vetor para guardar as encomendas usadas

    switch(atoi(argv[3])) {
        case 1:
        {
            //Ordenar as carrinhas de forma decrescente de Capacidade(Peso+Vol)
        std::sort(trucks.begin(),trucks.end(), cenario1::compararCarrinhas);

        //Ordenar as encomendas de forma decrescente de Capacidade(Peso+Vol)
        std::sort(encos.begin(),encos.end(), cenario1::compararEnc);

        //Chamar função
        cenario1::escolhertruck(encos,trucks,Pedidos,Estafetas);


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
  
        break;
        }
        case 2: 
        {
            //Ordenar as carrinhas de forma decrescente de Capacidade(Peso+Volume)
        std::sort(trucks.begin(),trucks.end(), cenario2::compararCarrinhas);

        //Preenher as carrinhas com as encomendas
        for(auto truck : trucks){
            if (encos.empty())
                break;
            int temp=cenario2::preenchertruck(truck,encos,Pedidos);
            //Se temp!=0 quer dizer que Lucro foi positivo ou seja que foram guardadas encomendas na carrinha atual
            if(temp!=0){
                Carrinha carrinha(truck.getVolMax(),truck.getPesoMax(),truck.getCusto());//Serve só para inserir nos Estafetas
                Estafetas.push_back(carrinha);
            }
        }

        int pp=0;
        int vv=0;
        int custo=0; // guarda a soma do custo total de todas as carrinhas usadas
        for (int i=0; i<Estafetas.size();i++){
            pp+=Estafetas.at(i).getPesoMax();
            vv+=Estafetas.at(i).getVolMax();
            custo+=Estafetas.at(i).getCusto();
        }
        cout<<"Nº Estafetas: "<<Estafetas.size()<<" PesoTotal " <<pp<<" Vol total:"<<vv<<" Custo total:"<<custo<<endl;

        pp=0;
        vv=0;
        int recom=0; //Guarda o valor total das recompensas dos Pedidos
        for (int i = 0; i < Pedidos.size(); i++) {
            pp+=Pedidos.at(i).getPeso();
            vv+=Pedidos.at(i).getVol();
            recom+=Pedidos.at(i).getRecomp();
        }

        cout<<"Nº Pedidos: "<<Pedidos.size()<<" Peso total:"<<pp<<" Vol total:"<<vv<<" Recompensa total:"<<recom<<endl;
        cout<<"Lucro Total="<<recom-custo<<endl;
        cout<<"Eficiencia="<<(Pedidos.size()/(float)TotalEncomendas)*100<<"%"<<endl;
        }
        break;
        case 3:
        {
            // Ordenar as encomendas por ordem crescente de duração
            std::sort(encos.begin(), encos.end(), cenario3::compararEnc);

            vector<Encomenda> Pedidos; // Vetor para armazenar os Pedidos a realizar

            cout << "Média:" << (cenario3::encomendasEntrega(Estafetas, encos, Pedidos) / (float)Pedidos.size()) << endl;

            int pp = 0; // Serve só pare ver o Peso total dos Pedidos
            int vv = 0; // Serve só para ver o Volume total dos Pedidos
            for (int i = 0; i < Pedidos.size(); i++)
            {
                pp += Pedidos.at(i).getPeso();
                vv += Pedidos.at(i).getVol();
            }
            cout << "Nº Pedidos: " << Pedidos.size() << " Peso total:" << pp << " Vol total:" << vv << endl;
            cout << "Eficiencia=" << (Pedidos.size() / (float)TotalEncomendas) * 100 << "%" << endl;
            break;
        }
        default:
        break;
        }

    return 0;
}

