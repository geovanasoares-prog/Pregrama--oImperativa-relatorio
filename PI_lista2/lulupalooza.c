#include <stdio.h>
#include <stdlib.h>
int main(){
    int n_xupenio, n_canais;
    scanf("%d %d", &n_xupenio, &n_canais);
    
    int f_mais_proximo = -1;
    int canal = -1;
    int min = -1;
    int menor_dif = -1;

    for(int i = 1; i <= n_canais; i++){
        int num1, num2;
        scanf("%d %d", &num1, &num2);
        //loop da sequencia (tive bastante dificuldade nessa parte, principalmente na implementação das condições de quando as diferenças eram iguais. Então, usei o gemini para me ajudar)
        int f_ultimo = num2;
        int f_penultimo = num1;
        int f_atual = 0;
        for(int j = 1; f_atual < n_xupenio + menor_dif; j++){
            if(1 == j) f_atual = num1;
            else if(2 == j) f_atual = num2;
            else{
                f_atual = f_penultimo + f_ultimo;
                f_penultimo = f_ultimo;
                f_ultimo = f_atual;
            }
            int diff_atual = abs(f_atual - n_xupenio);

            if (-1 == canal || diff_atual < menor_dif || (diff_atual == menor_dif && i > canal)){
                menor_dif = diff_atual;
                canal = i;
                min = j;
                f_mais_proximo = f_atual;
            }
        }
    }
    printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d", canal, min);
    //verifica se pode comprar o ingresso vip
    int n = f_mais_proximo;
    int soma_n = 0;
    while(n > 0){
        soma_n += n % 10;
        n /= 10;
    }if (soma_n > 10){
        puts(" e com o VIP garantido!!!");
    }else{
        puts(", mas o ingresso VIP não vai rolar :(");
    }
    return 0;
}