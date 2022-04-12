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
    int valor;
public:
    EstafetaouPedido(int pe,int v,int money){
        vol=v;
        peso=pe;
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
    return (a.getVolMax()+a.getPesoMax())>=(b.getVolMax()+b.getPesoMax());
}

/*bool compararEnc(Encomenda a, Encomenda b){
    return((a.getPeso()+a.getVol())>=(b.getPeso()+b.getVol()));
}
*/
void preenchertruck2(Carrinha& truck,vector<Encomenda>& encos){

    std::cout<<"antes Tudo\n";
    if(encos.empty()){
        cout<<"\n Is empty\n";
        return;
    }
    std::cout<<"antes B\n";
    vector<vector<vector<int>>> B(encos.size()+1,vector<vector<int>>(truck.getPesoMax()+1,vector<int>(truck.getVolMax()+1,0)));

    std::cout<<"Criou B\n";
    for(int i=1;i<=encos.size();i++){
        for(int peso=0; peso<=truck.getPesoMax();peso++){
            for (int vol = 0; vol <=truck.getVolMax() ; vol++) {
                B[i][peso][vol]=B[i-1][peso][vol];

                if((peso>=encos.at(i-1).getPeso()) && (vol>=encos.at(i-1).getVol()) && (B[i][peso][vol]<B[i-1][peso-encos.at(i-1).getPeso()][vol-encos.at(i-1).getVol()]+encos.at(i-1).getRecomp())){
                    B[i][peso][vol]=B[i-1][peso-encos.at(i-1).getPeso()][vol-encos.at(i-1).getVol()]+encos.at(i-1).getRecomp();
                }
              /*  if(peso<encos.at(i).getPeso() || vol<encos.at(i).getVol()){
                    B[i][peso][vol]=B[i-1][peso][vol];
                }
                else{
                    B[i][peso][vol]= max(B[i-1][peso][vol],B[i-1][peso-encos.at(i).getPeso()][vol-encos.at(i).getVol()]+encos.at(i).getDurar());
                } */
                // cout<< "Valor do B "<<B[i][peso][vol]<<" ";
            }
            //cout<<"\n";
        }

    }
    cout<<"MAx dur: "<<B[encos.size()][truck.getPesoMax()][truck.getVolMax()];
    int n=encos.size();
    int M=truck.getPesoMax();
    int V=truck.getVolMax();
    while(n!=0){
        if(B[n][M][V]!=B[n-1][M][V]){
            cout<<"Encomenda: "<<n<<" with Peso= "<<encos.at(n-1).getPeso()<<" and vol"<<encos.at(n-1).getVol()<<" and recom= "<<encos.at(n-1).getRecomp()<<endl;

            M=M-encos.at(n-1).getPeso();
            V=V-encos.at(n-1).getVol();
        }
        n--;
    }

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
    //Ordenar as carrinhas de forma decrescente de Peso+Volume
    std::sort(trucks.begin(),trucks.end(), compararCarrinhas);

    for(auto truck : trucks){
        preenchertruck2(truck,encos);
        break;
    }

/*
    vector<EstafetaouPedido> Estafetas;
    vector<EstafetaouPedido> Pedidos;
    cout << escolhertruck(encos,trucks,Pedidos,Estafetas) << endl;
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
    cout<<"Estafetas "<<ra<<" PesoTotal " <<pp<<" Vol total:"<<vv<<" Custo total:"<<custo<<endl;
    int te=0;
    pp=0;
    vv=0;
    int recom=0;
    for (int i = 0; i < Pedidos.size(); i++) {
        pp+=Pedidos.at(i).getPeso();
        vv+=Pedidos.at(i).getVol();
        te++;
        recom+=Pedidos.at(i).getValor();;
    }
    cout<<"Nº Pedido "<<Pedidos.size()<<" Peso total:"<<pp<<" Vol total:"<<vv<<" Recompensa total:"<<recom<<endl;
    cout<<"Lucro="<<recom-custo<<endl;
    */
    return 0;
}

