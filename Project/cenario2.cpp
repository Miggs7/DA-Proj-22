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
    int peso;
    int vol;
    int valor;
public:
    //! Cria um elemento do tipo EstafetaouPedido
    //! \param pe-peso do elemento
    //! \param v-volume do elemento
    //! \param money-valor monetário do elemento
    EstafetaouPedido(int pe,int v,int money){
        peso=pe;
        vol=v;
        valor=money;
    }

    int const getVol(){
        return vol;
    }
    int const getPeso(){
        return peso;
    }
    int const getValor(){
        return valor;
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
    return ((a.getVolMax()+a.getPesoMax())>=(b.getVolMax()+b.getPesoMax()) && (a.getCusto()<=b.getCusto()));
}


int preenchertruck2(Carrinha& truck,vector<Encomenda>& encos,vector<EstafetaouPedido>& pedidos){


    if(encos.empty()){
        cout<<"\n Is empty\n";
        return 0;
    }

    vector<vector<vector<int>>> B(encos.size()+1,vector<vector<int>>(truck.getPesoMax()+1,vector<int>(truck.getVolMax()+1,0)));


    for(int i=1;i<=encos.size();i++){
        for(int peso=0; peso<=truck.getPesoMax();peso++){
            for (int vol = 0; vol <=truck.getVolMax() ; vol++) {
                B[i][peso][vol]=B[i-1][peso][vol];

                if((peso>=encos.at(i-1).getPeso()) && (vol>=encos.at(i-1).getVol()) && (B[i][peso][vol]<B[i-1][peso-encos.at(i-1).getPeso()][vol-encos.at(i-1).getVol()]+encos.at(i-1).getRecomp())){
                    B[i][peso][vol]=B[i-1][peso-encos.at(i-1).getPeso()][vol-encos.at(i-1).getVol()]+encos.at(i-1).getRecomp();
                }
            }
        }
    }

    int n=encos.size();
    int M=truck.getPesoMax();
    int V=truck.getVolMax();
    //vecto indice(n,0);
    int indiceencomenda[n]={0}; //Serve para guardar os índices das encomendas usadas
    int valorencomendas=0;  //serve para calcular o valor total das encomendas
    int i=0;
    //Usado para descobrir os indices das encomendas usadas
    int pso=0;
    int vol=0;
    while(n!=0){
        if(B[n][M][V]!=B[n-1][M][V]){
            valorencomendas+=encos.at(n-1).getRecomp();
            M=M-encos.at(n-1).getPeso();
            V=V-encos.at(n-1).getVol();
            pso+=encos.at(n-1).getPeso();
            vol+=encos.at(n-1).getVol();
          //  cout<<"Encomenda:"<<n-1<<" Peso:"<<encos.at(n-1).getPeso()<<" Vol:"<<encos.at(n-1).getVol()<<endl;
            indiceencomenda[i]=n-1;
         //  cout<<"Indicie encomenda:"<<indiceencomenda[i]<<"\n"<<endl;
            i++;
        }
        n--;
    }
   // cout<<"\nApos knapsack: Numero encomendas:"<<i<<" Peso total:"<<pso<<" Volume total:"<<vol<<endl;
    // Só vão ser guardadas as encomendas que façam com que o lucro seja positivo
    if(valorencomendas-truck.getCusto()>0){
        for(int t=0; t<encos.size();t++){
            if(indiceencomenda[t]!=0){

             //   cout<<"Dentro for Indicie encomenda:"<<indiceencomenda[t]<<"\n"<<endl;
                EstafetaouPedido encomendas(encos.at(indiceencomenda[t]).getPeso(),encos.at(indiceencomenda[t]).getVol(),encos.at(indiceencomenda[t]).getRecomp());
                pedidos.push_back(encomendas);
                encos.erase(encos.begin()+indiceencomenda[t]);
                for(int k=0;k<encos.size();k++){
                    if(indiceencomenda[k]>indiceencomenda[t])
                        indiceencomenda[k]--;
                }
            }
        }

        //cout<<"Lucro="<<valorencomendas-truck.getCusto()<<endl;
        return valorencomendas-truck.getCusto();
    }



    return 0;
}

int main() {

    string encomendasfile("encomendas.txt");
    string carrinhasfile("carrinhas.txt");
    string line;

    vector<Encomenda> encos;
    vector<Carrinha> trucks;

    //leitura encomendas
    ifstream input_file(encomendasfile);
    if(!input_file.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<encomendasfile<<endl;
    }
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
    cout<<"Total="<<TotalEncomendas<<" Encos.size():"<<encos.size()<<endl;

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

    //Ordenar as carrinhas de forma decrescente de Capacidade(Peso+Volume)
    std::sort(trucks.begin(),trucks.end(), compararCarrinhas);

    vector<EstafetaouPedido> Estafetas; //Vetor para guardar as carrinhas usadas
    vector<EstafetaouPedido> Pedidos; //Vetor para guardar as encomendas usadas


    for(auto truck : trucks){
        if (encos.empty())
            break;
        int temp=preenchertruck2(truck,encos,Pedidos);
        if(temp!=0){
            EstafetaouPedido carrinha(truck.getPesoMax(),truck.getVolMax(),truck.getCusto());//Serve só para inserir nos Estafetas
            Estafetas.push_back(carrinha);
        }
       // cout<<"Peso Carrinha:"<<truck.getPesoMax()<<" Volume carrinha:"<<truck.getVolMax()<<endl;

    }


    int pp=0;
    int vv=0;
    int ra=0;
    int custo=0;
    for (int i=0; i<Estafetas.size();i++){
        pp+=Estafetas.at(i).getPeso();
        vv+=Estafetas.at(i).getVol();
        ra++;
        custo+=Estafetas.at(i).getValor();
    }
    cout<<"Nº Estafetas: "<<ra<<" PesoTotal " <<pp<<" Vol total:"<<vv<<" Custo total:"<<custo<<endl;
    int te=0;
    pp=0;
    vv=0;
    int recom=0;

    for (int i = 0; i < Pedidos.size(); i++) {
        pp+=Pedidos.at(i).getPeso();
        vv+=Pedidos.at(i).getVol();
        te++;
        //cout<<"Pedido:"<<i+1<<" PEso:"<<Pedidos.at(i).getPeso()<<" Vol"<< Pedidos.at(i).getVol()<<endl;
        recom+=Pedidos.at(i).getValor();

    }
    cout<<"Nº Pedidos: "<<Pedidos.size()<<" Peso total:"<<pp<<" Vol total:"<<vv<<" Recompensa total:"<<recom<<endl;
    cout<<"Lucro="<<recom-custo<<endl;
    cout<<"Eficiencia="<<(Pedidos.size()/(float)TotalEncomendas)*100<<"%"<<endl;
    return 0;
}

