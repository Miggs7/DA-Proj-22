#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
struct encomendas{
    int vol;
    int peso;
    int recom;
    int dur;

}encomenda;


struct carrinhas{
    int volMax;
    int pesoMax;
    int custo;
    int volatual;
    int pesoatual;
}carrinha;



bool comparaarvarrinhas(carrinhas a, carrinhas b){
    return(a.pesoMax>=b.pesoMax &&  a.volMax>=b.volMax);
}


int main() {

    std::string encomendasfile("encomendas.txt");
    std::string line;
    char* vol;
    char* peso;
    char* duracao;
    char* custo;
    char** recompensa;
    std::vector<carrinhas> carr;
    std::ifstream input_file(encomendasfile);
    if(!input_file.is_open()){
        std::cout<<"Erro ao abrir o ficheiro "<<encomendasfile<<std::endl;
    }
    while(std::getline(input_file,line)){

    }
}
    //1)
    /*Minimizar estafetas: ordenar o vetor das carrinhas e tentar fazer a cenas da mochila para as encomendas
     *                      sendo o weight das encomendas o peso e volume delas e o value delas a sua duração
     *                      e tentamos diminuir a duração
     *
    */
    // 2)
    /*  Ordenar as encomendas de forma decrescente da recompensa e as carrinhas de forma crescente de custo
     *  https://www.geeksforgeeks.org/job-sequencing-problem/
     *
     *  3)
     *  Ordenar as encomendas de forma crescente/decrescente da duração e basta enviar essas encomendas no container pedido

    return 0;
}
