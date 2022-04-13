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

//! Class para guardar os parâmetros de uma carrinha
class Carrinha{
    //!Volume máximo da carrinha
    int volMax;
    //!Peso máximo da carrinha
    int pesoMax;
    //!Custo da carrinha
    int custo;
    //!Volume disponível da carrinha
    int volatual;
    //!Peso disponível da carrinha
    int pesoatual;
public:
    Carrinha(int v,int p,int c){
        volMax = v;
        pesoMax = p;
        custo = c;
        volatual=v;
        pesoatual=p;
    }
    //! Devolve o volume máximo da carrinha
    //! \return volume máximo da carrinha
    int getVolMax(){
        return volMax;
    }
    //! Devolve o peso máximo da carrinha
    //! \return peso máximo da carrinha
    int getPesoMax(){
        return pesoMax;
    }
    //! Devolve o custo da carrinha
    //! \return custo da carrinha
    int getCusto(){
        return custo;
    }
    //! Devolve o Volume disponível da carrinha
    //! \return Volume disponível da carrinha
    int getVolatual(){
        return volatual;
    }
    //! Devolve o Peso disponível da carrinha
    //! \return Peso disponível da carrinha
    int getPesoAtual(){
        return pesoatual;
    }

    //! Retira ao peso disponível o valor indicado
    //! \param addedpeso-Peso a retirar ao peso disponível da carrinha
    void setPesoAtual(int addedpeso){
        pesoatual=pesoatual-addedpeso;
    }

    //! Retira ao volume disponível o valor indicado
    //! \param addedvol-Vol a retirar ao volume disponível da carrinha
    void setVolAtual(int addedvol){
        volatual=volatual-addedvol;
    }
};

//! Ordena as carrinhas de forma decrescente de capacidade(peso+volume)
//! \param a- carrinha A
//! \param b- carrinha B
//! \return true se  capacidadeA>=capacidadeB
bool compararCarrinhas(Carrinha a, Carrinha b){
    return (a.getVolMax()+a.getPesoMax())>=(b.getVolMax()+b.getPesoMax());
}

//! Ordena as encomendas de forma decrescente de capacidade(peso+volume)
//! \param a- encomenda A
//! \param b- encomenda B
//! \return true se capacidadeA>=capacidadeB
bool compararEnc(Encomenda a, Encomenda b){
    return((a.getPeso()+a.getVol())>=(b.getPeso()+b.getVol()));
}

//! Verifica se é possível colocar a encomenda "enco" na carrinha "truck"
//! \param truck-carrinha escolhida
//! \param encos-encomenda escolhida
//! \return 0-se não couber na carrinha
//! \return 1-se couber na carrinha
int FitsInTruck(Carrinha& truck,Encomenda& enco){
    int tempV = enco.getVol();
    int tempW = enco.getPeso();

    if((truck.getVolatual()-tempV)>=0 && (truck.getPesoAtual()-tempW)>=0){
        truck.setPesoAtual(tempW);
        truck.setVolAtual(tempV);
        return 1;
    }


    return 0;
}

//! Preenche as carrinhas dadas por "trucks" com as encomendas "encos" colocando as carrinhas
//! usadas em "estafetas" e as encomendas usadas em "pedidos"
//! \param encos-todas as encomendas
//! \param trucks-todas as carrinhas
//! \param pedidos-Vetor para guardar as encomendas legíveis
//! \param estafetas-Vetor para guardas as carrinhas utilizadas para guardas as encomendas
void escolhertruck(vector<Encomenda>& encos, vector<Carrinha>& trucks,vector<EstafetaouPedido>& pedidos,vector<EstafetaouPedido>& estafetas ){


    int flag=0; // Flag para indicar se uma carrinha foi usada para guardar encomendas

    for(auto truck : trucks) {
       flag=0;
        if(encos.empty())
            break;
        for(int i = 0; i < (int) encos.size(); i++){
                if(FitsInTruck(truck,encos.at(i)) == 1){
                   EstafetaouPedido encomendausada(encos.at(i).getPeso(),encos.at(i).getVol()); //Serve para inserir nos pedidos
                    pedidos.push_back(encomendausada);

                    encos.erase(encos.begin()+i);
                    i--;

                    flag=1;  //Flag fica a 1 se foi intruduzida uma encomenda na carrinha atual
                }
            }

        if(flag==1){
            EstafetaouPedido temp(truck.getPesoMax(),truck.getVolMax()); //Serve para inserir nas estafetas
            estafetas.push_back(temp);
            //continue;
        }
    }
    return;
}

int main() {

    string encomendasfile("encomendas.txt");
    string carrinhasfile("carrinhas.txt");
    string line;

    vector<Encomenda> encos;   // Vetor para guardar as encomendas
    vector<Carrinha> trucks;   //Vetor para guardar as carrinhas


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

    //leitura carrinhas
    std::ifstream input_file2(carrinhasfile);
    if(!input_file2.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<carrinhasfile<<endl;
    }
    while(std::getline(input_file2,line)){
        char *dup = strdup(line.c_str());
        int volMax = atoi(strtok(dup," "));
        int pesoMax = atoi(strtok(NULL," "));
        int custo  = atoi(strtok(NULL," "));
        free(dup);
        Carrinha temp2(volMax,pesoMax,custo);
        trucks.push_back(temp2);
    }

    //Ordenar as carrinhas de forma decrescente de Capacidade(Peso+Vol)
    std::sort(trucks.begin(),trucks.end(), compararCarrinhas);

    //Ordenar as encomendas de forma decrescente de Capacidade(Peso+Vol)
    std::sort(encos.begin(),encos.end(), compararEnc);

    vector<EstafetaouPedido> Estafetas; //Vetor para guardar as carrinhas usadas
    vector<EstafetaouPedido> Pedidos;   //Vetor para guardar as encomendas guardadas

    //Chamar função
   escolhertruck(encos,trucks,Pedidos,Estafetas);

    int pp=0;   //Variáveis para contar o Peso e Volume total
    int vv=0;   // das carrinhas usadas e encomendas guardadas

    for (int i=0; i<Estafetas.size();i++){
        pp+=Estafetas.at(i).getPeso();
        vv+=Estafetas.at(i).getVol();

    }
    cout<<"Nº Estafetas: "<<Estafetas.size()<<" PesoTotal: " <<pp<<" Vol total:"<<vv<<endl;

    pp=0;
    vv=0;

   for (int i = 0; i < Pedidos.size(); i++) {
       pp+=Pedidos.at(i).getPeso();
       vv+=Pedidos.at(i).getVol();
    }
    cout<<"Nº Pedidos: "<<Pedidos.size()<<" Peso total:"<<pp<<" Vol total:"<<vv<<endl;
    cout<<"Eficiencia="<<(Pedidos.size()/(float)TotalEncomendas)*100<<"%"<<endl;
    return 0;
}
