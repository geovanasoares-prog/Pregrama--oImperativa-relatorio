#include <stdio.h>
#include <string.h>

void simulacao(char matriz[1000][1000], int x, int y, int valido);

int main(){
    int x, y;
    scanf("%d %d", &x, &y);

    char goteira[1000][1000];
    for(int i = 0; i < x; i++){
        scanf("%s", &goteira[i]);
    }
    
    int ha_goteria = 0;//não ha goteira
    simulacao(goteira, x, y, ha_goteria);

    if(ha_goteria = 1){
        for(int k = 0; k < x; k++){
        printf("%s\n", goteira[k]);
        }
    }
    return 0;
}

void simulacao(char matriz[1000][1000], int x, int y, int valido){
    int molhou = 0;
    for(int m = 0; m < x; m++){
        //verifica se há goteira
        if(m >= 1 && valido == 0) break;
        for(int n = 0; n < y; n++){
            //quando achar a primeira gota
            if(matriz[m][n] == 'o'){
                valido = 1;
                break;
            }
            //caso a estante esteja molhada
            if(molhou == 1){
                matriz[m][n] = 'o';
                if(matriz[m+1][n] != '#' || n + 1 == y){ 
                molhou = 0;//a gua para de escorrer quando a estante acaba ou nao tem mais espaço
                continue;
                }
            }
            //replica a gota na horizontal
            if(matriz[m-1][n] == 'o' && matriz[m][n] != '#'){
                matriz[m][n] = 'o';

                //caso a prateleira molhe
                if(matriz[m+1][n] == '#'){
                    molhou = 1;
                    if(n == y - 1) molhou = 0;

                    //loop da água escorrer para a esquerda
                    int esq = n;
                    while(matriz[m+1][esq] == '#'){//o loop deve continuar até uma casa antes do começo da estante
                        //verifica se ha espaço na esquerda
                        if(esq - 1 < 0) break;
                        --esq; //já desloca para a esquerda, pois ja foi colocada a primeira gota encima da prateleira
                        matriz[m][esq] = 'o';
                    }
                }
            }
        }
    }
}