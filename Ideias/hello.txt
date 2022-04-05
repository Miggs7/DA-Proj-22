int minCoins(int i, int k){
    // C[]={1  ,2  ,5]}
    //  i=0,i=1,i=2,i=3 --- Representa a iteração, se i=2 só chegamos ao espaço 2 do vetor
    //Se i=0 não há solução porque não tem moedas logo o resultado é INFINITO para a condicao de baixo dar verdade
    //Se k=0 não há troco logo é preciso 0 moedas
    //1(uma moeda do tipo C[i])+minCoins(i,k-C[i]; Se C[i]<=k && 1+minCoins(i,k-C[i])<minCoins(i-1,k)
    //                                                           -new value          - old value
    //return minCoins(i-1,k); restantes casos


}

int lastCoin(int i, int k){
    //retorna o indice da moeda usada para atingir o valor de k
    //INFINITO; se i=0;
    //0; se k=0;
    // C[i]; se C[i]<=K && 1+minCoins(i,k-C[i])<minCoins(i-1,k)
    //lastCoin(i-1,k); restantes casos
}
bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {

    unsigned int min[T+1]={99999};
    unsigned int last[T+1]={0};     //Inicialização

    for (int i = 0; i < n; i++) {
        for (int k = C[i]; k <=T ; k++) {
            if(1+ minCoins(i,k-C[i])<minCoins(i-1,k)){
                min[k]=1+ minCoins(i,k-C[i]);
                last[k]=C[i];
            }
        }
    }
    if(min[T]==99999) // min[T]==(valor inicializado)
        return false;

    for(int i=0;i<n;i++){
        usedCoins[i]=0;
    }

    int remainingT=T;
    while(remainingT>0){
        usedCoins[last[remainingT]];
        remainingT-=C[last[remainingT]];
    }

    return remainingT<=0;
}


/*
 * m=minCOins number of coins needed to reach the value with the available coins
 * l=lastCoin valor da moeda used to reach the value (é suposto ser o indice)
 *
          |k=0   1  2  3  4  5  6  7  8  9
i=0 Ci=-- |m=---------------(nada)--------
 _________|l=-----------------------------
i=1 Ci=1  |m=0   1  2  3  4  5  6  7  8  9
_________ |l=0   1  1  1  1  1  1  1  1  1
___________________________________________
i=2 Ci=2  |m=0   1  1  2  2  3  3  4  4  5
_________ |l=0   1  2  2  2  2  2  2  2  2
___________________________________________
i=3 Ci=3  |m=0   1  1  2  2  1  2  2  3  3   ---> Resultado final= {2,2,5}
_________ |l=0   1  2  2  2  5  5  5  5  5

 */

