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
    //! \param addedvol-Vol a retirar ao volume disponível da carrinha
    void setVolAtual(int addedvol){
        volatual=volatual-addedvol;
    }
};