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
class EstafetaouPedido{
    int vol;
    int peso;
public:
    EstafetaouPedido(int pe,int v){
        vol=v;
        peso=pe;
    }
    int const getVol(){
        return vol;
    }
    int const getPeso(){
        return peso;
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
    return((a.getPeso()+a.getVol()+a.getDurar())<=(b.getPeso()+b.getVol()+b.getDurar()));
}

int preenchertruck(Carrinha truck,Encomenda encos,int time){
    int tempV = encos.getVol();
    int tempW = encos.getPeso();

    if((tempV+truck.getVolatual() > truck.getVolMax() && tempW+truck.getPesoAtual() > truck.getPesoMax()) || time > 86400 ){ // casos base
        return 0;
    }

    if(tempV+truck.getVolatual()<= truck.getVolMax() && tempW+truck.getPesoAtual() <= truck.getPesoMax() && time < 86400){
        truck.setPesoAtual(tempW+truck.getPesoAtual());
        truck.setVolAtual(tempV+truck.getVolatual());
    }

    return 1;
}


int escolhertruck(vector<Encomenda>& encos, vector<Carrinha>& trucks,vector<EstafetaouPedido>& pedidos,vector<EstafetaouPedido>& estafeta ){
    int count = 0;
    int t = 0;
    for(auto truck : trucks) {
       // t=0;
        if(encos.empty()) break;
        if(t>=86400)
            break;
        for(int i = 0; i < (int) encos.size(); i++){
            if(preenchertruck(truck,encos.at(i),t) == 1){
                t += encos.at(i).getDurar();
                EstafetaouPedido encomendausada(encos.at(i).getPeso(),encos.at(i).getVol());
                pedidos.push_back(encomendausada);
                encos.erase(encos.begin()+i);
                i--;
            }
        }
        EstafetaouPedido temp(truck.getPesoMax(),truck.getVolMax());
        estafeta.push_back(temp);
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
    int sum=0;
    for (int i = 0; i < enco.size(); i++) {
        sum+=enco.at(i).getDurar();
        }
    cout<<"TEmpo total: "<<sum<<endl;
    vector<EstafetaouPedido> Estafetas;
    vector<EstafetaouPedido> Pedidos;
    cout<<"Encos "<<enco[0].getPeso()<<endl;
    cout << escolhertruck(enco,truck,Pedidos,Estafetas) << endl;
    for (int i=0; i<Estafetas.size();i++){
        cout<<"Estafeta "<<i+1<<" Peso:"<<Estafetas.at(i).getPeso()<<" Vol:"<<Estafetas.at(i).getVol()<<endl;
    }
    int te=0;
   for (int i = 0; i < Pedidos.size(); i++) {
        te++;
    }
    cout<<"Pedido "<<te<<endl;
    return 0;
}
