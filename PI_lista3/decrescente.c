#include <stdio.h>
int main(){
    int n_teste;
    scanf("%d", &n_teste);

    //loop dos testes
    for (int teste = 0; teste < n_teste; ++teste){
        int tamanho;
        scanf("%d", &tamanho);
        //loop da sequencia
        int n_atual = 0, n_melhor = 0, seq_atual[tamanho], seq_melhor[tamanho];
        int num_anterior = -1000;
        int num;
        for(int i = 0; i < tamanho; i++){
            scanf("%d", &num);
            if(num_anterior > num){
                //caso seja detectado o inicio de uma sequencia, precisa pegar o número anterior
                if (n_atual == 0){
                    seq_atual[n_atual] = num_anterior;
                }
                ++n_atual;
                seq_atual[n_atual] = num;
            }
            if(num_anterior<num || (i == tamanho-1 && n_melhor == 0) || i == tamanho -1){
                // atualiza a sequencia decres anterior caso a atual seja maior
                if (n_melhor < n_atual){
                    n_melhor = n_atual;
                    n_atual = 0;
                    for(int i = 0; i < tamanho; i++){
                        seq_melhor[i] = seq_atual[i]; 
                    }
                }else{
                    n_atual = 0;
                    
                }
            }num_anterior = num;

        }
        if(n_melhor > 0){
            printf("%d\n", n_melhor+1);
            for(int j = 0; j<=n_melhor; j++){
                printf("%d ", seq_melhor[j]);
            }puts("");
        }else{
            puts("0");
        }
    }return 0;
}