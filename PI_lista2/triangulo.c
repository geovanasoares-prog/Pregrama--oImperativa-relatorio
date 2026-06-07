#include <stdio.h>
int main(){
    char letra;
    scanf("%c", &letra);

    // usei uma logica parecida com a questão de xupenio na lista 1, mas para letras maiuscúlas
    int num_letra = letra - 64;

    for(int linha = 1; linha <= num_letra; ++linha){
        char ponto = '.';
        for (int rep_ponto = 1; rep_ponto <= num_letra - linha; ++rep_ponto){
            printf("%c", ponto);
        }
        
        /* Para o próximo loop, eu usei o gemini e apesar de não ter me 
        retornado um código com o output correto foi de grande ajuda para eu conseguir formular esse loop*/
        for(int i = 1; i <= linha; ++i){
            printf("%c", i + 64);
        }
        for(int j = linha - 1; j >= 1; --j){
            printf("%c", j + 64);
        }

        for (int rep_ponto = 1; rep_ponto <= num_letra - linha; ++rep_ponto){
            printf("%c", ponto);
        }
        printf("\n", ponto);
    }
    return 0;
}