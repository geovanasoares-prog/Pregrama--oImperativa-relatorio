#include <stdio.h>

int main(){
    int q;
    scanf("%d", &q);
    //loop das instruções
    int posicao = 0;
    for(int comando = 1; comando <= q; comando++){
        int passos;
        char direcao;
        scanf("%d %c", &passos, &direcao);
        
        if(direcao == 'D'){
            //loop dos espaços em branco
            for (int j = 1; j <= posicao; j++) {
                printf(" ");
            }
            //como depois de mudar de linha, os comandos 'D' devem continuar na mesma linha para esse passo extra é do comando anterior
            if(comando > 1) passos++;
            //quantidade os pontos
            for (int j = 1; j <= passos; j++) {
                printf(".");
            }
            printf("\n");
            //para os pontos aparecerem logo abaixo da última coluna, foi necessário diminuir em 1 a posição
            posicao += passos-1;
        }else if(direcao == 'E'){
            //caso os passos a esquerda ultrapassem a coluna 0
            if(posicao - passos < 0){
                puts("Informacao invalida");
                break;
            }else{
                //movimento oposto a esquerda por isso a posição recua
                posicao-=passos;

                 for (int j = 1; j <= posicao; j++) {
                printf(" ");
                }
                //quantidade os pontos
                //passo adicionado para manter os pontos na mesma linha apos a "descida"
                for (int j = 1; j <= passos+1; j++) {
                    printf(".");
                }
                printf("\n");
            }
        }else{
            //quando 'B' for o último movimento não terá pontos 'extras' por isso precisei adicionar aqui
            if(comando == q) passos++;
            //um passo extra ja foi adicionado nas outras movimentações
            for (int j = 1; j <= passos-1; j++) {
                //espaçoes brancos
                for (int k = 1; k <= posicao; k++) {
                    printf(" ");
                }
                printf(".\n");
            }
        }
    }
    return 0;
}