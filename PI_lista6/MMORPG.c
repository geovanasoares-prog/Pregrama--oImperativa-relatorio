#include <stdio.h>
#include<stdlib.h>
#include<string.h>

void nuvem(int **matrz, int x, int y, int m, int n);
int camada_atual(int x_atual, int y_atual, int x_centro, int y_centro);
void explosao(int **matrz, int x, int y, int m, int n);
int max(int a, int b);
void liberar(int **matriz, int linha);
int **copiar(int **matriz, int lin, int col);

void explosao(int **matrz, int x, int y, int m, int n){
    int **mapa = copiar(matrz, m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int camada = camada_atual(i, j, x, y);

            if(camada == 1){
                mapa[i][j] = max(0, mapa[i][j] - 50);
            }else if(camada == 2){
                mapa[i][j] = max(0, mapa[i][j] - 25);
            }
        }
    }
    imprimir(mapa, m ,n);
    liberar(mapa, m);
}
int max(int a, int b){
    if(a>b)return a;
    return b;
}

int camada_atual(int x_atual, int y_atual, int x_centro, int y_centro){
    int d_x = abs(x_atual - x_centro);
    int d_y = abs(y_atual - y_centro);

    //caso ele esteja na camada 1 a distancia do centro deve ser 1 ou 0
    if(d_x + d_y <= 1) return 1;

    //verifica se esta na 2 camada
    int x_dire[] = {0, -1, +1, 0, 0};
    int y_dire[] = {0, 0, 0, -1, +1};

    for(int i = 0; i<5; i++){
        //calcula o x e y de cada cedula da camada 1
        int li = x_centro + x_dire[i];
        int ci = y_centro + y_dire[i];

        //verifica se a cedula atual é vizinha nas 8 direções(se pertence a camada 2)
        if(abs(li - x_atual) <= 1 && abs(ci - y_atual) <= 1) return 2;
    }
    return 0;
}

void nuvem(int **matrz, int x_centro, int y_centro, int m, int n){
    int **mapa = copiar(matrz, m, n);

    //loop turnos
    for(int turno = 0; turno < 3; turno++){
        int ah_vivos = 0;
        int **novo_mapa = copiar(mapa, m, n);

        //passa a matriz
        for(int i = 0; i< m; i++){
            for(int j = 0; j<n; j++){
                //verifica qual a camada esta
                int camada = camada_atual(i, j, x_centro, y_centro);
                if(camada > 0){
                    //procura os vizinhos vivos
                    int cel_vivas = 0;
                    for(int dx = -1; dx<=1; dx++){
                        for(int dy = -1; dy<=1; dy++){
                            if(dx == 0 && dy == 0) continue;
                            int lin = dx + i;
                            int col = dy + j;
                            if(lin >= 0 && lin < m && col >= 0 && col < n){
                                if(mapa[lin][col] > 0)cel_vivas++;
                            }
                        }
                    }
                    //calculo de dano
                    int dano = 5 + (8 * cel_vivas);
                    novo_mapa[i][j] = max(0, mapa[i][j] - dano);
                    if(novo_mapa[i][j] > 0)ah_vivos = 1;
                }
            }
        }
        imprimir(novo_mapa, m, n);
        if(turno < 3)puts("");

        liberar(mapa, m);
        mapa = novo_mapa;
        
        //verifica se ainda ha vivos
        if(ah_vivos == 0)break;
    }
    liberar(mapa, m);
}
void liberar(int **matriz, int linha){
    for(int i = 0; i<linha; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void imprimir(int **matriz, int linha, int coluna){
    for(int i = 0; i<linha; i++){
        for(int j = 0; j<coluna; j++){
            printf("%d ", matriz[i][j]);
        }puts("");
    }
}

int **copiar(int **matriz, int lin, int col){
    int **copia = (int**)malloc(lin * sizeof(int*));
    if(copia == NULL)exit(1);
    for(int i = 0; i< lin; i++){
        copia[i] = (int*)malloc(col * sizeof(int));
        if(copia[i] == NULL){
            liberar(copia, i);
            exit(1);
        }
        for(int j = 0; j<col; j++){
            copia[i][j] = matriz[i][j];
        }
    }
    return copia;
}

void (*acao[])(int**, int, int, int, int) = {nuvem, explosao};

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int **mapa = (int**)malloc(m * sizeof(int*));
    if(mapa == NULL)exit(1);
    for(int i = 0; i<m; i++){
        mapa[i] = (int*)malloc(n * sizeof(int));
        if(mapa[i] == NULL){
            liberar(mapa, i);
            exit(1);
        }
        for(int j = 0; j<n; j++){
            scanf(" %d", &mapa[i][j]);
        }
    }
    int x, y;
    scanf("%d %d", &x, &y);

    char ordem[30];
    scanf("%s", ordem);

    puts("Estado inicial do mapa:");
    imprimir(mapa, m, n);
    puts("");

    //chama a função correta
    if(strcmp(ordem, "EXPLOSAO_ARCANA") == 0) {
        puts("Estado do mapa após usar a Explosão Arcana:");
        acao[1](mapa, x, y, m, n);
    }
    if(strcmp(ordem, "NUVEM_VENENOSA") == 0) {
        puts("Estado do mapa, por turno, após usar a Nuvem Venenosa:");
        acao[0](mapa, x, y, m, n);
    }

    return 0;
}