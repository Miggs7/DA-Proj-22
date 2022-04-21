#ifndef cenario3H
#define cenario3H

#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>
//#include "info.hpp"

using namespace std;

//! funções usadas em cenario3
class cenario3{
    public:
    //! Compara a duração das encomendas
    //! \param a- 1º encomenda
    //! \param b- 2º encomenda
    //! \return true- se duração de "a" menor ou igual à duração de "b"
    //! \return false- se duração de "a" maior que duração de "b"
    static bool compararEnc(Encomenda a, Encomenda b){
        return(a.getDurar()<=b.getDurar());
    }

    //! Descobrir as encomendas para entrega
    //! \param Estafetas- vetor para armazenar todas as carrinhas
    //! \param encos- vetor para armazenar todas as encomendas
    //! \param Pedidos - Vetor para armazenar os Pedidos a realizar
    //! \return totaltemp - Guarda o tempo total usado pelas encomendas
    //! Complexidade temporal:O(n); Complexidade espacial: O(n)
    static int encomendasEntrega(vector<Carrinha>& Estafetas, vector<Encomenda>& encos, vector<Encomenda>& Pedidos){
        int temp = 28800;    // Segundos do periodo 9-17
        float totaltemp = 0; // Guarda o tempo total usado pelas encomendas
        int sum = 0;

        for (int i = 0; i < encos.size(); i++){
                if (temp - encos.at(i).getDurar() >= 0){
                    temp -= encos.at(i).getDurar();
                    Encomenda encomenda(encos.at(i).getVol(), encos.at(i).getPeso(), 0, encos.at(i).getDurar()); // Serve só para guardar no vetor Pedido(recompensa nao necessaria)
                    Pedidos.push_back(encomenda);
                    sum += encos.at(i).getDurar();
                    totaltemp += sum;
                }
            }
        return totaltemp;
    }
};
#endif