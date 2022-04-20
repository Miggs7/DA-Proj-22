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
int preenchertruck(Carrinha& truck,vector<Encomenda>& encos,vector<Encomenda>& pedidos);