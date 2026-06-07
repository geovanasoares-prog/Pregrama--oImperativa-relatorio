#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mesclar(char *tudo, int *inicio, int *tam, char *mes, int n);

void fusao(char *mes, int tam_mes);

void fusao(char *mes, int tam_mes){
    int ha_fusao = 0;
    for(int i = 0; i < tam_mes -1; i++){
        //verifica se o char atual e o proximo são iguais
        if(*(mes + i) == *(mes+i+1)){
            ha_fusao += 1;
            //verifica se o char == 'z'
            if(*(mes + i) == 'z') *(mes + i) = 'a';
            else *(mes + i) = *(mes + i) + 1;

            //retrocede a string
            for(int m = i+1; m < tam_mes; m++){
                *(mes + m) = *(mes + m + 1);
            }
            //reduz o tamanho da string
            tam_mes--;
            *(mes + tam_mes) = '\0';//encerra a string
            
            //volta as 2 char para verificar se a novas fusões
            if(i > 0) i -= 2;
            else i--;
        }
    }
}

void mesclar(char *tudo, int *inicio, int *tam, char *mes, int n){
    int max = 0, ind_mes = 0;
    //determina a maior string
    for(int f = 0; f < n; f++)if(tam[f] > max) max = tam[f];

    //loop da posição de cada char das strings
    for(int i = 0; i < max; i++){
        //loop da posição de cada string
        for(int j = 0; j < n; j++){
            //verifica de a string ja terminou
            if(i < tam[j]){
                mes[ind_mes++] = tudo[inicio[j] + i];
            }
        }
    }
    mes[ind_mes] = '\0';
}

int main(){
    int N;
    scanf("%d", &N);

    char *todas_string = (char*)malloc(300 * sizeof(char));
    int *inicio_string = (int*)malloc(N * sizeof(int));
    int *tamanho = (int*)malloc(N * sizeof(int));

    //verificação de memoria
    if(todas_string == NULL || inicio_string == NULL || tamanho == NULL) return 0;

    int cursor = 0;
    for(int i = 0; i < N; i++){
        char str[300];
        scanf("%s", &str);
        tamanho[i] = strlen(str);
        inicio_string[i] = cursor;
        //adicionar a string_mesclar
        for(int j = 0; j < tamanho[i]; j++){
            todas_string[cursor + j] = str[j];
        }
        cursor+=tamanho[i];
    }
    char *mesclada = (char*)malloc(300 * sizeof(char));
    if(mesclada == NULL) return 0;

    mesclar(todas_string, inicio_string, tamanho, mesclada, N);

    printf("%s\n", mesclada);

    int tam_mes = strlen(mesclada);
    fusao(mesclada, tam_mes);

    printf("%s\n", mesclada);

    free(todas_string);
    free(inicio_string);
    free(tamanho);
    free(mesclada);

    return 0;
}