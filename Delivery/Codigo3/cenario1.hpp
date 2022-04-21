#ifndef cenario1H
#define cenario1H

#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>
#include <map>
//#include "info.hpp"

using namespace std;

//! funções usadas em cenario1
class cenario1{
    public:
    //! Ordena as carrinhas de forma decrescente de capacidade(peso+volume)
    //! \param a- carrinha A
    //! \param b- carrinha B
    //! \return true se  capacidadeA>=capacidadeB
    static bool compararCarrinhas(Carrinha a, Carrinha b){
        return (a.getVolMax()+a.getPesoMax())>=(b.getVolMax()+b.getPesoMax());
    }

    //! Ordena as encomendas de forma decrescente de capacidade(peso+volume)
    //! \param a- encomenda A
    //! \param b- encomenda B
    //! \return true se capacidadeA>=capacidadeB
    static bool compararEnc(Encomenda a, Encomenda b){
        return((a.getPeso()+a.getVol())>=(b.getPeso()+b.getVol()));
    }

    //! Verifica se é possível colocar a encomenda "enco" na carrinha "truck"
    //! \param truck-carrinha escolhida
    //! \param encos-encomenda escolhida
    //! \return 0-se não couber na carrinha
    //! \return 1-se couber na carrinha
    static int FitsInTruck(Carrinha& truck,Encomenda& enco){
        int tempV = enco.getVol();
        int tempW = enco.getPeso();

        //Indica se a carrinha escolhida tem espaço disponível para a encomenda escolhida
        if((truck.getVolatual()-tempV)>=0 && (truck.getPesoAtual()-tempW)>=0){
            truck.setPesoAtual(tempW);//Diminuir a capacidade disponivel da carrinha
            truck.setVolAtual(tempV);
            return 1;
        }


    return 0;
    }

//! Preenche as carrinhas dadas por "trucks" com as encomendas "encos" colocando as carrinhas
//! usadas em "estafetas" e as encomendas usadas em "pedidos"
//! \param encos-todas as encomendas
//! \param trucks-todas as carrinhas
//! \param pedidos-Vetor para guardar as encomendas legíveis
//! \param estafetas-Vetor para guardas as carrinhas utilizadas para guardas as encomendas
static void escolhertruck(vector<Encomenda>& encos, vector<Carrinha>& trucks,vector<Encomenda>& pedidos,vector<Carrinha>& estafetas ){

    int flag=0; // Flag para indicar se uma carrinha foi usada para guardar encomendas

    for(auto truck : trucks) {
       flag=0;
        if(encos.empty())
            break;
        for(int i = 0; i < (int) encos.size(); i++){
                if(cenario1::FitsInTruck(truck,encos.at(i)) == 1){
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
};

#endif