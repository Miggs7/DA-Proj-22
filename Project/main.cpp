#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>

using namespace std;

class Encomenda{
    int volume;
    int peso;
    int recom;
    int durar;
    public:
        Encomenda(int v,int p,int r,int d){
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

class Carrinha{
    int volMax;
    int pesoMax;
    int custo;
    int volatual;
    int pesoatual;
    public:
        Carrinha(int v,int p,int c){
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
        void setPesoAtual(int addedpeso){
            this->pesoatual+=addedpeso;
        }
        void setVolAtual(int addedvol){
            this->volatual+=addedvol;
        }
};

bool compararCarrinhas(Carrinha a, Carrinha b){
    return(a.getPesoMax()>=b.getPesoMax() &&  a.getVolMax()>=b.getVolMax());
}

bool compararEnc(Encomenda a, Encomenda b){
    return(a.getPeso()>=b.getPeso() &&  a.getVol()>=b.getVol());
}

int preenchertruck(Carrinha truck,Encomenda encos,int time){
    int tempV = encos.getVol();
    int tempW = encos.getPeso();

    if((tempV+truck.getVolatual() > truck.getVolMax() && tempW+truck.getPesoAtual() > truck.getPesoMax()) || time > 86400 ){ // casos base
        return 0;
    }

    if(tempV+truck.getVolatual()<= truck.getVolMax() && tempW+truck.getPesoAtual() <= truck.getPesoMax() && time < 86400){
            truck.setPesoAtual(encos.getPeso());
            truck.setVolAtual(encos.getVol());
            time += encos.getDurar();
        }

    return 1;
}


int escolhertruck(vector<Encomenda>& encos, vector<Carrinha>& trucks){
   int count = 0;

    for(auto truck : trucks) {
       int t = 0;
       //cout << encos.size() << endl;
       if(encos.size() == 0) break;
       for(int i = 1; i <= (int) encos.size(); i++){
        preenchertruck(truck,encos[i],t);
            if(preenchertruck(truck,encos[i],t) == 1){
                t += encos[i].getDurar();
                encos.erase(encos.begin()+i-1);
                --i;
            }
        }
        count++;
    }
    return count;
}

int main() {

    string encomendasfile("encomendas.txt");
    string carrinhasfile("carrinhas.txt");
    string line;

    vector<Encomenda> enco;
    vector<Carrinha> truck;
    ifstream input_file(encomendasfile);

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
            enco.push_back(temp);
    }

    //leitura carrinhas
    std::ifstream input_file2(carrinhasfile);


    while(std::getline(input_file2,line)){
            char *dup = strdup(line.c_str());
            int volMax = atoi(strtok(dup," "));
            int pesoMax = atoi(strtok(NULL," "));
            int custo  = atoi(strtok(NULL," "));
            free(dup);
            Carrinha temp2(volMax,pesoMax,custo);
            truck.push_back(temp2);
    }

    std::sort(truck.begin(),truck.end(), compararCarrinhas);
    std::sort(enco.begin(),enco.end(), compararEnc);

    cout << escolhertruck(enco,truck) << endl;


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
