//Tive muitos problemas para otimizar meu código, então me apoiei bastante no gemini
#include<stdio.h>
#define max 80
int menor_distancia = 1000;

void fuga(int menord_xy[max][max], char mapa[max][max], int distancia_atual, int x_atual, int y_atual, int linha, int coluna);

int main(){
    int lin, col;
    scanf("%dx%d", &lin, &col);
    
    char mapa[max][max];
    for(int i = 0; i < lin; i++){
        scanf("%s", mapa[i]);
    }
    //loop para achar onde rebeka começa
    int x_inicio, y_inicio;
    for(int m = 0; m < lin; m++){
        for(int n = 0; n < col; n++){
            if(mapa[m][n] == 'o'){
                x_inicio = m;
                y_inicio = n;
            }
        }
    }
    int menord_xy[max][max];
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            menord_xy[i][j] = 1000;
        }
    }
    int distancia = 0;
    if(lin > 0 && col > 0) fuga(menord_xy, mapa, distancia, x_inicio, y_inicio, lin, col);

    if(menor_distancia == 1000) puts("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir");
    else printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", menor_distancia);
    return 0;
}
void fuga(int menord_xy[max][max], char mapa[max][max], int distancia_atual, int x_atual, int y_atual, int linha, int coluna){

    //condições paro o caminho ser invalido
    if(mapa[x_atual][y_atual] == '#') return;
    
    //caso a distancia naquela posição seja maior nesse caminho
    if(menord_xy[x_atual][y_atual] <= distancia_atual) return;

    menord_xy[x_atual][y_atual] = distancia_atual; // guarda a menor distancia naquela posição

    // se achou a saída
    if(mapa[x_atual][y_atual] == 'd'){
        if(distancia_atual <= menor_distancia) menor_distancia = distancia_atual;
        return;
    }
    if (distancia_atual+1 > menor_distancia) return;
    //marca que esse lugar ja foi visitado
    mapa[x_atual][y_atual] = '#';
    
    //move na horizontal e vertical para achar o caminho 
    if(x_atual+1 < linha) fuga(menord_xy, mapa, distancia_atual+1, x_atual+1, y_atual, linha, coluna);
    if(x_atual-1 >= 0) fuga(menord_xy, mapa, distancia_atual+1, x_atual-1, y_atual, linha, coluna);
    if(y_atual+1 < coluna)fuga(menord_xy, mapa, distancia_atual+1, x_atual, y_atual+1, linha, coluna);
    if(y_atual-1 >= 0) fuga(menord_xy, mapa, distancia_atual+1, x_atual, y_atual-1, linha, coluna);
    
    //desmarca quando estiver voltando
    mapa[x_atual][y_atual] = '_';
}