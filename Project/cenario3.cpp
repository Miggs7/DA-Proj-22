#include <iostream>
#include <vector>
#include<algorithm>
#include <fstream>
#include <cstring>

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
    //! \return valor do atributo volume da encomenda
    int getVol(){
        return volume;
    }
    //! Consegue o Peso da encomenda
    //! \return valor do atributo peso da encomenda
    int getPeso(){
        return peso;
    }
    //! Consegue a Recompensa da encomenda
    //! \return valor do atributo recomda encomenda
    int getRecomp(){
        return recom;
    }
    //! Consegue a Duração da encomenda
    //! \return valor do atributo durar da encomenda
    int getDurar(){
        return durar;
    }
};
//!Class para guardar um Pedido
class Pedido{
    //!Volume do Pedido
    int vol;
    //!Peso do Pedido
    int peso;
    //!Duração da entrega do Pedido
    int duracao;
public:
    //! Cria um novo Pedido
    //! \param pe-peso do pedido
    //! \param v-volume do pedido
    //! \param dur-duração do pedido
    Pedido(int pe,int v,int dur){
        vol=v;
        peso=pe;
        duracao=dur;
    }
    //! Consegue o volume do Pedido
    //! \return valor do atributo vol do pedido
    int const getVol(){
        return vol;
    }
    //! Consegue o peso do Pedido
    //! \return valor do atributo peso do pedido
    int const getPeso(){
        return peso;
    }
    //! Consegue a duração do Pedido
    //! \return o valor do atributo duração do pedido
    int const getDur(){
        return duracao;
    }

};
//! Compara a duração das encomendas
//! \param a- 1º encomenda
//! \param b- 2º encomenda
//! \return true- se duração de "a" menor ou igual à duração de "b"
//! \return false- se duração de "a" maior que duração de "b"
bool compararEnc(Encomenda a, Encomenda b){
    return(a.getDurar()<=b.getDurar());
}
int main() {
    vector<Encomenda> encos;//vetor para armazenar as encomendas

    string encomendasfile("encomendas.txt"); //Ficheiro onde se encontram os dados
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

    int TotalEncomendas=encos.size(); // Guarda o número de encomendas total

    //Ordenar as encomendas por ordem crescente de duração
    std::sort(encos.begin(),encos.end(), compararEnc);

    vector<Pedido> Pedidos;//Vetor para armazenar os Pedidos a realizar

    int temp=28800; // Segundos do periodo 9-17
    float totaltemp=0; //Guarda o tempo total usado pelas encomendas

    //Descobrir as encomendas para entrega
    for(int i=0;i<encos.size();i++){
        if(temp-encos.at(i).getDurar()>0){
            temp-=encos.at(i).getDurar();
            Pedido encomenda(encos.at(i).getPeso(),encos.at(i).getVol(),encos.at(i).getDurar());//Serve só para guardar no vetor Pedido
            Pedidos.push_back(encomenda);
            totaltemp+=encos.at(i).getDurar();
        }
    }

    cout<<"Média:"<<(totaltemp/(float)Pedidos.size())<<endl;

    int pp=0;//Serve só pare ver o Peso total dos Pedidos
    int vv=0;//Serve só para ver o Volume total dos Pedidos
    for (int i = 0; i < Pedidos.size(); i++) {
        pp+=Pedidos.at(i).getPeso();
        vv+=Pedidos.at(i).getVol();
    }
    cout<<"Nº Pedidos: "<<Pedidos.size()<<" Peso total:"<<pp<<" Vol total:"<<vv<<endl;
    cout<<"Eficiencia="<<(Pedidos.size()/(float)TotalEncomendas)*100<<"%"<<endl;
    return 0;
}