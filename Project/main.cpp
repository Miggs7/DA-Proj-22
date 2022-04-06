#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>

using namespace std;

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
        int getVol(){
            return volume;
        }
        int getPeso(){
            return peso;
        }
        int getRecomp(){
            return recom;
        }
        int getDurar(){
            return durar;
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
        int getVolMax(){
            return volMax;
        }
        int getPesoMax(){
            return pesoMax;
        }
        int getCusto(){
            return custo;
        }
        int getVolatual(){
            return volatual;
        }
        int getPesoAtual(){
            return pesoatual;
        }
};

void maxEstafeta(vector<Encomendas> enco, vector<Carrinhas> truck){
    vector<int> weight;
    vector<int> volume;
    vector<int> volumeTruck;
    vector<int> weightTruck;

    for(auto x: enco){
        weight.push_back(x.getPeso());
        volume.push_back(x.getVol());
    }

    for(auto y: truck){
        volumeTruck.push_back(y.getVolMax());
        weightTruck.push_back(y.getPesoAtual());
    }


}

/*bool comparaarvarrinhas(carrinhas a, carrinhas b){
    return(a.pesoMax>=b.pesoMax &&  a.volMax>=b.volMax);
}*/


int main() {

    string encomendasfile("encomendas.txt");
    string carrinhasfile("carrinhas.txt");
    string line;
    int n = 0;
    //std::vector<carrinhas> carr;
    vector<Encomendas> enco;
    vector<Carrinhas> truck;
    ifstream input_file(encomendasfile);

    if(!input_file.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<encomendasfile<<endl;
    }

    //leitura encomendas
    while(std::getline(input_file,line)){
        if(n != 0){
            char *dup = strdup(line.c_str());
            int vol = atoi(strtok(dup," "));
            int peso = atoi(strtok(NULL," "));
            int recompensa = atoi(strtok(NULL," "));
            int duracao = atoi(strtok(NULL," "));
            free(dup);
            //std::cout << vol << " " << peso << " " << recompensa << " " << duracao <<std::endl;
            Encomendas temp(vol,peso,recompensa,duracao);
            enco.push_back(temp);
        }
        n++;
    }

    //leitura carrinhas
    std::ifstream input_file2(carrinhasfile);
    n = 0;

    while(std::getline(input_file2,line)){
        if(n != 0){
            char *dup = strdup(line.c_str());
            int volMax = atoi(strtok(dup," "));
            int pesoMax = atoi(strtok(NULL," "));
            int custo  = atoi(strtok(NULL," "));
            free(dup);
            //std::cout << volMax << " " << pesoMax << " " << custo << " " <<std::endl;
            Carrinhas temp2(volMax,pesoMax,custo);
            truck.push_back(temp2);
        }
        n++;

        maxEstafeta(enco,truck);
    }

    return 0;
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
