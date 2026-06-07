#include <stdio.h>
//Eu criei minha lógica primeiro e depois verifiquei com o gemini, mas o resultado não foi como eu gostaria. Então resolvi manter a minha lógica.
void andar(int matriz[4][4], char direcao[20]);
void pior_escolha(int matriz[4][4]);

int main(){
    char comandos[20];
    for(int i = 0; i < 20; i++){
        scanf(" %c", &comandos[i]);
    }
    comandos[20] = '\0';

    int cidade[4][4] = {0};
    andar(cidade, comandos);

    pior_escolha(cidade);

    return 0;
}

void andar(int matriz[4][4], char direcao[20]){
    int x_atual = 0, y_atual = 0;
    for(int k = 0; k < 20; k++){
        if(direcao[k] == 'c') x_atual--;
        else if(direcao[k] == 'b') x_atual++;
        else if(direcao[k] == 'e') y_atual--;
        else y_atual++;
        
        //caso ele saia na matriz
        if(x_atual < 0 || x_atual >= 4 || y_atual < 0 || y_atual >= 4) break;
        
        matriz[x_atual][y_atual]++;
    }
}

void pior_escolha(int matriz[4][4]){
    int pior_lugar = 0, x_pior = 0, y_pior = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(matriz[i][j] > pior_lugar){
                x_pior = i;
                y_pior = j;
                pior_lugar = matriz[i][j];
            }
        }
    }
    printf("Coordenada X:%d, Y:%d", y_pior, x_pior);// acabei trocando as variaveis de lugar na construção do código e fica mais fácil so inverter agora
}