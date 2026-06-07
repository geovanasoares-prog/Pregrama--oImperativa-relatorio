#include <stdio.h>
/*usei o Gemini para resolver esse problema, pois o código que fiz sozinha não funcionou,
mas felizmente foram poucas as diferenças.*/
int main(){
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);

    // loop dos numeros no intervalo n,k
    int num1_valido = -1; //usei -1, pois 0 pode ser um numero valido
    int q = 0;

    for(int i = n; i < k; i++){
        int dividendo = i;
        int num_fatores = 0;
        int valido = 1; // numeros validos mas menores que 9 não passam pelo 2 for, por isso 'valido' começa com0 '1'

        // retira os fatores 2
        while (dividendo > 0 && dividendo % 2 == 0){
            dividendo /= 2;
        }

        // calcular os fatores
        for (int div = 3; div * div <= dividendo; div+=2){
            // verificar se o divisor é par
            if (dividendo % div == 0){
                dividendo /= div;
                num_fatores +=1;
                //verifica se possui fatores distintos
                if (dividendo % div == 0){
                    valido = 0;
                    break;
                }
            }
        }//verifica se restou um algo > 1, o ultimo fator primo
        if (dividendo > 1){
            num_fatores += 1;
        }
        //verifica a quantidade de fatores
        if(1 == valido && num_fatores == p){
            //verifica se é o primeiro numero que tem as condiçoes de dudinha
            if(-1 == num1_valido){
                num1_valido = i;
            }else{
                q+=1;
            }
        }
    }//verifica se existe um número válido
    if (-1 == num1_valido){
        puts("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.");
    }else{
        printf("%d %d\n", num1_valido, q);
    }
    return 0;
}