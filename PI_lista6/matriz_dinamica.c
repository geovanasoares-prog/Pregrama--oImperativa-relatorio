#include <stdio.h>
#include <stdlib.h>

int dobrar(int a);
int quadrado(int a);
int absoluto(int a);
void liberar(int **matriz, int linha);

void liberar(int **matriz, int linha){
    for(int i = 0; i < linha; i++){
        free(matriz[i]);
    }
    free(matriz);
}
int dobrar(int a){
    a = a * 2;
    return a;
}
int quadrado(int a){
    a = a * a;
    return a;
}
int absoluto(int a){
    a = abs(a);
    return a;
}

int main(){
    int l, c;
    scanf("%d %d", &l, &c);

    int **matriz = (int**)malloc(l * sizeof(int*));
    if(matriz == NULL)exit(1);

    for(int i = 0; i < l; i++){
        matriz[i] = (int*)malloc(c * sizeof(int));
        if(matriz[i] == NULL){
            liberar(matriz, i); 
            exit(1);}
            
        for(int j = 0; j<c; j++){
            scanf(" %d", &matriz[i][j]);
        }
    }
    //responsável por selecionar qual operação vai ser realizada
    int(*operacoes[])(int) = {dobrar, quadrado, absoluto};

    int op;
    scanf("%d", &op);
    op -= 1;//arruma para coincidir com o indice certo

    //alteração da matriz
    for(int m = 0; m<l; m++){
        for(int n = 0; n<c; n++){
           matriz[m][n] = operacoes[op](matriz[m][n]);
        }
    }

    for(int lin = 0; lin<l; lin++){
        for(int col = 0; col<c; col++){
            printf("%d ", matriz[lin][col]);
        }
        puts("");
    }
    liberar(matriz, l);
    return 0;
}