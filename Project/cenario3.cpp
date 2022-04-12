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
    int duracao;
public:
    EstafetaouPedido(int pe,int v,int dur){
        vol=v;
        peso=pe;
        duracao=dur;
    }

    int const getVol(){
        return vol;
    }
    int const getPeso(){
        return peso;
    }
    int const getDur(){
        return duracao;
    }

};
bool compararEnc(Encomenda a, Encomenda b){
    return(a.getDurar()<=b.getDurar());
}
int main() {

    string encomendasfile("encomendas.txt");
    string line;

    vector<Encomenda> encos;

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


    std::sort(encos.begin(),encos.end(), compararEnc);
    vector<EstafetaouPedido> Pedidos;

    int temp=28800;
    float totaltemp=0;
    for(int i=0;i<encos.size();i++){
        if(temp-encos.at(i).getDurar()>0){
            temp-=encos.at(i).getDurar();
            EstafetaouPedido encomenda(encos.at(i).getPeso(),encos.at(i).getVol(),encos.at(i).getDurar());
            Pedidos.push_back(encomenda);
            totaltemp+=encos.at(i).getDurar();
        }
    }
    cout<<"Medio:"<<(totaltemp/(float)Pedidos.size())<<endl;

    int pp=0;
    int vv=0;
    int ra=0;
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

