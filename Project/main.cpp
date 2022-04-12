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
        volatual=v;
        pesoatual=p;
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
        pesoatual=pesoatual-addedpeso;
    }
    void setVolAtual(int addedvol){
        volatual=volatual-addedvol;
    }
};

bool compararCarrinhas(Carrinha a, Carrinha b){
    return (a.getVolMax()+a.getPesoMax())>=(b.getVolMax()+b.getPesoMax());
}

bool compararEnc(Encomenda a, Encomenda b){
    return((a.getPeso()+a.getVol())>=(b.getPeso()+b.getVol()));
}

int preenchertruck(Carrinha& truck,Encomenda& encos){
    int tempV = encos.getVol();
    int tempW = encos.getPeso();

    if((truck.getVolatual()-tempV)>=0 && (truck.getPesoAtual()-tempW)>=0){
        truck.setPesoAtual(tempW);
        truck.setVolAtual(tempV);
        return 1;
    }


    return 0;
}


int escolhertruck(vector<Encomenda>& encos, vector<Carrinha>& trucks,vector<EstafetaouPedido>& pedidos,vector<EstafetaouPedido>& estafetas ){
    int count = 0;
    int t = 0;
    int flag=0;

    for(auto truck : trucks) {
       flag=0;
        if(encos.empty())
            break;
        for(int i = 0; i < (int) encos.size(); i++){
                if(preenchertruck(truck,encos.at(i)) == 1){
                   EstafetaouPedido encomendausada(encos.at(i).getPeso(),encos.at(i).getVol()); //Serve para inserir nos pedidos
                    pedidos.push_back(encomendausada);
                    encos.erase(encos.begin()+i);
                    i--;
                    flag=1;
                }
            }

        if(flag==1){
            EstafetaouPedido temp(truck.getPesoMax(),truck.getVolMax()); //Serve para inserir nas estafetas
            estafetas.push_back(temp);
            count++;
            continue;
        }
    }
    return count;
}

int main() {

    string encomendasfile("encomendas.txt");
    string carrinhasfile("carrinhas.txt");
    string line;

    vector<Encomenda> encos;
    vector<Carrinha> trucks;
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
        encos.push_back(temp);
    }
    int TotalEncomendas=encos.size();
    //leitura carrinhas
    std::ifstream input_file2(carrinhasfile);


    while(std::getline(input_file2,line)){
        char *dup = strdup(line.c_str());
        int volMax = atoi(strtok(dup," "));
        int pesoMax = atoi(strtok(NULL," "));
        int custo  = atoi(strtok(NULL," "));
        free(dup);
        Carrinha temp2(volMax,pesoMax,custo);
        trucks.push_back(temp2);
    }

    std::sort(trucks.begin(),trucks.end(), compararCarrinhas);
    std::sort(encos.begin(),encos.end(), compararEnc);

    vector<EstafetaouPedido> Estafetas;
    vector<EstafetaouPedido> Pedidos;
    cout << escolhertruck(encos,trucks,Pedidos,Estafetas) << endl;
    int pp=0;
    int vv=0;
    int ra=0;
    for (int i=0; i<Estafetas.size();i++){
        pp+=Estafetas.at(i).getPeso();
        vv+=Estafetas.at(i).getVol();
        ra++;
    }
    cout<<"Estafetas "<<ra<<" PesoTotal " <<pp<<" Vol total:"<<vv<<endl;
    int te=0;
    pp=0;
    vv=0;

   for (int i = 0; i < Pedidos.size(); i++) {
       pp+=Pedidos.at(i).getPeso();
       vv+=Pedidos.at(i).getVol();
       te++;
    }
    cout<<"Nº Pedido "<<Pedidos.size()<<" Peso total:"<<pp<<" Vol total:"<<vv<<endl;
    cout<<"Eficiencia="<<(Pedidos.size()/(float)TotalEncomendas)*100<<"%"<<endl;
    return 0;
}
