#ifndef cenario2H
#define cenario2H
#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>
#include "info.hpp"

using namespace std;

//! funções usadas em cenario2
class cenario2{
    public:
    //! Compara a capacidade(peso+volume) e o custo de duas carrinhas
    //! \param a- 1º carrinha
    //! \param b - 2º carrinha
    //! \return true- se capacidade de "a" maior ou igual à de "b" e se custo de "a" menor ou igual ao custo de "b"
    //! \return false- se capacidade de "a" menor que capacidade de "b" e se custo de "a" maior que o custo de "b"
    static bool compararCarrinhas(Carrinha a, Carrinha b){
        return ((a.getVolMax()+a.getPesoMax())>=(b.getVolMax()+b.getPesoMax()) && (a.getCusto()<=b.getCusto()));

    }

    //! Preeche a carrinha dada com encomendas de forma em que a soma da recompensa de todas as encomendas seja a máxima
    //! \param truck- carrinha a preencher
    //! \param encos- vetor com as encomendas para preencher
    //! \param pedidos- vetor para guardar as encomendas usadas
    //! \return 0- Em caso de não haver mais encomendas ou caso o Lucro da carrinha não seja positivo
    //! \return Lucro( (soma das recompensas de todas as encomendas)-custo da carrinha)- Caso Lucro seja positivo
    static int preenchertruck(Carrinha& truck,vector<Encomenda>& encos,vector<Encomenda>& pedidos){

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
    int valorencomendas=0;  //serve para calcular o valor total da recompensa das encomendas
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

    // Só vão ser guardadas encomendas se o Lucro for positivo
    if(valorencomendas-truck.getCusto()>0){
        for(int t=0; t<encos.size();t++){
            if(indiceencomenda[t]!=0){
                Encomenda encomendas(encos.at(indiceencomenda[t]).getVol(),encos.at(indiceencomenda[t]).getPeso(),encos.at(indiceencomenda[t]).getRecomp(),0);//serve só para guardar em pedidos
                pedidos.push_back(encomendas);
                encos.erase(encos.begin()+indiceencomenda[t]);

                //Reduzir o indice das encomendas com um indice superior ao indiceencomenda[t] por 1
                for(int k=0;k<encos.size();k++){
                    if(indiceencomenda[k]>indiceencomenda[t])
                        indiceencomenda[k]--;
                }
            }
        }

        return valorencomendas-truck.getCusto();//return do Lucro quando é positivo
    }

    return 0;
}


};
#endif