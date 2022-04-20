#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>
#include "info.hpp"

using namespace std;

//! Compara a capacidade(peso+volume) e o custo de duas carrinhas
//! \param a- 1º carrinha
//! \param b - 2º carrinha
//! \return true- se capacidade de "a" maior ou igual à de "b" e se custo de "a" menor ou igual ao custo de "b"
//! \return false- se capacidade de "a" menor que capacidade de "b" e se custo de "a" maior que o custo de "b"
bool compararCarrinhas(Carrinha a, Carrinha b){
    return ((a.getVolMax()+a.getPesoMax())>=(b.getVolMax()+b.getPesoMax()) && (a.getCusto()<=b.getCusto()));
}

//! Preeche a carrinha dada com encomendas de forma em que a soma da recompensa de todas as encomendas seja a máxima
//! \param truck- carrinha a preencher
//! \param encos- vetor com as encomendas para preencher
//! \param pedidos- vetor para guardar as encomendas usadas
//! \return 0- Em caso de não haver mais encomendas ou caso o Lucro da carrinha não seja positivo
//! \return Lucro( (soma das recompensas de todas as encomendas)-custo da carrinha)- Caso Lucro seja positivo
int preenchertruck(Carrinha& truck,vector<Encomenda>& encos,vector<Encomenda>& pedidos){

    //Verificar se existem encomendas por usar
    if(encos.empty()){
        cout<<"\n Is empty\n";
        return 0;
    }

    vector<vector<vector<int>>> B(encos.size()+1,vector<vector<int>>(truck.getPesoMax()+1,vector<int>(truck.getVolMax()+1,0)));


    for(int i=1;i<= encos.size();i++){
        for(int peso=0; peso<=truck.getPesoMax();peso++){
            for (int vol = 0; vol <=truck.getVolMax() ; vol++) {
                B[i][peso][vol]=B[i-1][peso][vol];

                if((peso>=encos.at(i-1).getPeso()) && (vol>=encos.at(i-1).getVol()) && (B[i][peso][vol]<B[i-1][peso-encos.at(i-1).getPeso()][vol-encos.at(i-1).getVol()]+encos.at(i-1).getRecomp())){
                    B[i][peso][vol]=B[i-1][peso-encos.at(i-1).getPeso()][vol-encos.at(i-1).getVol()]+encos.at(i-1).getRecomp();
                }
            }
        }
    }

    int n=encos.size();
    int M=truck.getPesoMax();
    int V=truck.getVolMax();
    int indiceencomenda[n]={0}; //Serve para guardar os índices das encomendas usadas
    int valorencomendas=0;  //serve para calcular o valor total das encomendas
    int i=0;
    //Guardar a posição das melhores encomendas
    while(n!=0){
        if(B[n][M][V]!=B[n-1][M][V]){
            valorencomendas+=encos.at(n-1).getRecomp();
            M=M-encos.at(n-1).getPeso();
            V=V-encos.at(n-1).getVol();
            indiceencomenda[i]=n-1;
            i++;
        }
        n--;
    }

    // Só vão ser guardadas as encomendas que façam com que o lucro seja positivo
    if(valorencomendas-truck.getCusto()>0){
        for(int t=0; t<encos.size();t++){
            if(indiceencomenda[t]!=0){
                Encomenda encomendas(encos.at(indiceencomenda[t]).getVol(),encos.at(indiceencomenda[t]).getPeso(),encos.at(indiceencomenda[t]).getRecomp(),0);//serve só para guardas em pedidos
                pedidos.push_back(encomendas);
                encos.erase(encos.begin()+indiceencomenda[t]);
                //Reduzir a posição das encomendas com uma posição superior à encomenda indiceencomenda[t] por 1
                for(int k=0;k<encos.size();k++){
                    if(indiceencomenda[k]>indiceencomenda[t])
                        indiceencomenda[k]--;
                }
            }
        }

        return valorencomendas-truck.getCusto();
    }

    return 0;
}

int main() {
    vector<Encomenda> encos;//Vetor para guardar todas as encomendas
    vector<Carrinha> trucks;//Vetor para guardar todas as carrinhas

    string encomendasfile("encomendas3.txt");//Ficheiro com as encomendas
    string carrinhasfile("carrinhas3.txt");//Ficheiro com as carrinhas
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



    std::ifstream input_file2(carrinhasfile);
    //verifica se a stream está associada a um ficheiro
    if(!input_file2.is_open()){
        cout<<"Erro ao abrir o ficheiro:"<<carrinhasfile<<endl;
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

    //Ordenar as carrinhas de forma decrescente de Capacidade(Peso+Volume)
    std::sort(trucks.begin(),trucks.end(), compararCarrinhas);

    vector<Carrinha> Estafetas; //Vetor para guardar as carrinhas usadas
    vector<Encomenda> Pedidos; //Vetor para guardar as encomendas usadas

    //Preenher as carrinhas com as encomendas
    for(auto truck : trucks){
        if (encos.empty())
            break;
        int temp=preenchertruck(truck,encos,Pedidos);
        //Se temp!=0 quer dizer que Lucro foi positivo ou seja que foram guardadas encomendas na carrinha atual
        if(temp!=0){
            Carrinha carrinha(truck.getVolMax(),truck.getPesoMax(),truck.getCusto());//Serve só para inserir nos Estafetas
            Estafetas.push_back(carrinha);
        }
    }


    int pp=0;  //Guarda a soma do peso total
    int vv=0;  //Guarda a soma do volume total
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
    return 0;
}

