#include<stdio.h>
#include<stdlib.h>

int calibracao(int a);
int saturacao(int a);
int amplificador(int a);
int (*comando[])(int) = {calibracao, saturacao,amplificador};
void modificar(int **matriz, int l, int c, int cmd[], int qnt);
void liberara(int **matriz, int i);
void imprimir(int **matriz, int x, int y);
void achar_critico(int **matriz, int x, int y);

void achar_critico(int **matriz, int x, int y){
    int maior = 0, x_maior, y_maior;

    for(int i = 0; i<x; i++){
        for(int j = 0; j<y; j++){
            if(matriz[i][j] > maior){
                maior = matriz[i][j];
                x_maior = i;
                y_maior = j;
            }
        }
    }
    printf("Sensor critico: %d\n", maior);
    printf("Posicao: (%d,%d)\n", x_maior, y_maior);
}

void imprimir(int **matriz, int x, int y){
    for(int i = 0; i<x; i++){
        for(int j = 0; j<y; j++){
            printf("%d ", matriz[i][j]);
        }
        puts("");
    }
    puts("");
}

void liberara(int **matriz, int i){
    for(int a = 0; a<i; a++){
        free(matriz[a]);
    }
    free(matriz);
}

void modificar(int **matriz, int l, int c, int *cmd, int qnt){
  
    //executa os filtros
    for(int r = 0; r<qnt; r++){
        for(int i = 0; i<l; i++){
            for(int j = 0; j<c; j++){
                matriz[i][j] = comando[cmd[r]](matriz[i][j]);
            }
        }
    }   
}

int calibracao(int a){
    return a+5;
}

int saturacao(int a){
    if(a>80)return 80;
    return a;
}

int amplificador(int a){
    return a * 2;
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);

    int **matriz = (int**)malloc(m * sizeof(int*));
    for(int i = 0; i<m; i++){
        matriz[i] = (int*)malloc(n * sizeof(int));
        if(matriz[i] == 0){
            liberara(matriz, i);
            exit(1);
        }
        for(int j = 0; j<n; j++){
            scanf(" %d", &matriz[i][j]);
        }
    }
    int cmd;
    while(scanf("%d", &cmd) == 1 && cmd != 0){
        int lista[1];
        if(cmd <4){
            lista[0] = cmd - 1;
            modificar(matriz, m, n, lista, 1);
        }
        else if(cmd == 4){
            int k;
            scanf("%d", &k);
            int *list = (int*)malloc(k * sizeof(int));
            for(int s = 0; s<k; s++){
                int ind;
                scanf("%d", &ind);
                list[s] = ind -1;
            }
            modificar(matriz, m, n, list, k);
        }
    }
    puts("Matriz processada:");
    imprimir(matriz, m, n);
    achar_critico(matriz, m, n);
    liberara(matriz, m);
}