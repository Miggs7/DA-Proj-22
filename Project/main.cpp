#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>
#include <map>

using namespace std;

//!Class para guardar os parâmetros de um Encomenda
class Encomenda{
    //!Volume da encomenda
    int volume;
    //!Peso da encomenda
    int peso;
    //!Recompensa da encomenda
    int recom;
    //!Duração da entrega da encomenda
    int durar;
public:
    //! Cria uma nova Encomenda
    //! \param v-volume da encomenda
    //! \param p-peso da encomenda
    //! \param r-recompensa da encomenda
    //! \param d-duração da encomenda
    Encomenda(int v,int p,int r,int d){
        volume = v;
        peso = p;
        recom = r;
        durar = d;
    }
    //! Consegue o volume da encomenda
    //! \return valor do volume da encomenda
    int getVol(){
        return volume;
    }
    //! Consegue o Peso da encomenda
    //! \return valor do peso da encomenda
    int getPeso(){
        return peso;
    }
    //! Consegue a Recompensa da encomenda
    //! \return valor da recompensa da encomenda
    int getRecomp(){
        return recom;
    }
    //! Consegue a Duração da encomenda
    //! \return valor da recompensa da encomenda
    int getDurar(){
        return durar;
    }
};
//!Class para guardar um Estafeta ou um Pedido
class EstafetaouPedido{
    //!Volume do Estafeta/Pedido
    int vol;
    //!Peso do Estafeta/Pedido
    int peso;
public:
    //! Cria um elemento do tipo EstafetaouPedido
    //! \param pe-peso do elemento
    //! \param v-volume do elemento
    EstafetaouPedido(int pe,int v){
        vol=v;
        peso=pe;

    }
    //! Consegue o Volume do elemento EstafetaouPedido
    //! \return valor do atributo vol do elemento
    int const getVol(){
        return vol;
    }
    //! Consegue o Peso do elemento EstafetaouPedido
    //! \return valor do atributo peso do elemento
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
    //! Cria uma nova Carrinha
    //! \param v-volume da carrinha
    //! \param p-peso da carrinha
    //! \param c-custo da carrinha
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
    //! \param addedvol-Volume a retirar ao volume disponível da carrinha
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

    //Indica se a carrinha escolhida tem espaço disponível para a encomenda escolhida
    if((truck.getVolatual()-tempV)>=0 && (truck.getPesoAtual()-tempW)>=0){
        truck.setPesoAtual(tempW);//Diminuir a capacidade disponivel da carrinha
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
        //Ver se foi inserida uma encomenda na carrinha atual
        //Se for, quer dizer que a carrinha é usada para encomendas
        if(flag==1){
            EstafetaouPedido temp(truck.getPesoMax(),truck.getVolMax()); //Serve para inserir nas estafetas
            estafetas.push_back(temp);
        }
    }
    return;
}

int main() {
    vector<Encomenda> encos;// Vetor para guardar as encomendas
    vector<Carrinha> trucks;//Vetor para guardar as carrinhas


    string encomendasfile("encomendas.txt");//Ficheiro onde se encontram os dados das encomendas
    string carrinhasfile("carrinhas.txt");//Ficheiro onde se encontram os dados das carrinhas
    string line;



    ifstream input_file(encomendasfile);
    //Verificar se a stream está associada a um ficheiro
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


    std::ifstream input_file2(carrinhasfile);
    //Verificar se a stream está associada a um ficheiro
    if(!input_file2.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<carrinhasfile<<endl;
    }
    //leitura carrinhas
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
    <<<<<<< Updated upstream
    escolhertruck(encos,trucks,Pedidos,Estafetas);
    =======
    // escolhertruck(encos,trucks,Pedidos,Estafetas);
    std::map<string,string> guardarcarrinhas;
    int breakflag=0;
    for (int i = 0; i < encos.size(); i++) {
        for(auto truck : trucks){
            //cout<<"Id:"<<truck.getId()<<endl;
            breakflag=0;
            if(FitsInTruck(truck,encos.at(i))==1){
                EstafetaouPedido encomendausada(encos.at(i).getPeso(),encos.at(i).getVol()); //Serve para inserir nos pedidos
                Pedidos.push_back(encomendausada);
                cout<<"Id:"<<truck.getId()<<endl;
                if(guardarcarrinhas.find(""+truck.getId())==guardarcarrinhas.end()){
                    //cout<<"ENtrou no if"<<endl;
                    guardarcarrinhas.insert({""+truck.getId(),"in"});
                    EstafetaouPedido temp(truck.getPesoMax(),truck.getVolMax()); //Serve para inserir nas estafetas
                    Estafetas.push_back(temp);
                }
                //  encos.erase(encos.begin()+i);
                //   cout<<"I antes"<<i<<endl;
                // i--;
                // cout<<"I depois"<<i<<endl;
                breakflag=1;
            }
            if(breakflag==1){
                // cout<<"Antes break"<<endl;
                break;
            }
        }
    }
    >>>>>>> Stashed changes


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