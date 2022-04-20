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
    return(a.getDurar()<=b.getDurar());
}