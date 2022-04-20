#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>
#include <map>
//#include "info.hpp"

using namespace std;


//! Ordena as carrinhas de forma decrescente de capacidade(peso+volume)
//! \param a- carrinha A
//! \param b- carrinha B
//! \return true se  capacidadeA>=capacidadeB
bool compararCarrinhas(Carrinha a, Carrinha b){
    return (a.getVolMax()+a.getPesoMax())>=(b.getVolMax()+b.getPesoMax());
}

//! Ordena as encomendas de forma decrescente de capacidade(peso+volume)
//! \param a- encomenda A
//! \param b- encomenda B
//! \return true se capacidadeA>=capacidadeB
bool compararEnc(Encomenda a, Encomenda b){
    return((a.getPeso()+a.getVol())>=(b.getPeso()+b.getVol()));
}

//! Verifica se é possível colocar a encomenda "enco" na carrinha "truck"
//! \param truck-carrinha escolhida
//! \param encos-encomenda escolhida
//! \return 0-se não couber na carrinha
//! \return 1-se couber na carrinha
int FitsInTruck(Carrinha& truck,Encomenda& enco){
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

void escolhertruck(vector<Encomenda>& encos, vector<Carrinha>& trucks,vector<Encomenda>& pedidos,vector<Carrinha>& estafetas );
