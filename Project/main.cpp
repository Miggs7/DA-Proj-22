#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>

class Encomendas{
    int volume;
    int peso;
    int recom;
    int durar;
    public:
        Encomendas(int v,int p,int r,int d){
            volume = v;
            peso = p;
            recom = r;
            durar = d;
        }
};

class Carrinhas{
    int volMax;
    int pesoMax;
    int custo;
    int volatual;
    int pesoatual;
    public:
        Carrinhas(int v,int p,int c){
            volMax = v;
            pesoMax = p;
            custo = c;
        }
};



/*bool comparaarvarrinhas(carrinhas a, carrinhas b){
    return(a.pesoMax>=b.pesoMax &&  a.volMax>=b.volMax);
}*/


int main() {

    std::string encomendasfile("encomendas.txt");
    std::string line;
    int vol;
    int peso;
    int duracao;
    int custo;
    int recompensa;
    //std::vector<carrinhas> carr;
    std::ifstream input_file(encomendasfile);
    if(!input_file.is_open()){
        std::cout<<"Erro ao abrir o ficheiro "<<encomendasfile<<std::endl;
    }
    while(std::getline(input_file,line)){
        char *dup = strdup(line.c_str());
        vol = atoi(strtok(dup," "));
        peso = atoi(strtok(NULL," "));
        duracao = atoi(strtok(NULL," "));
        free(dup);
        std::cout << vol << " " << peso << " " <<  duracao <<std::endl;
        //Carrinhas temp = new Carrinhas(vol,peso,duracao);

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
}*/
