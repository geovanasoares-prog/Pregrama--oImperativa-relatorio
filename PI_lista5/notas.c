#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void relatorio(float *notas, int tam);
void media(float *notas, int qnt);
void mediana(float *notas, int qnt);
void moda(float *notas, int qnt);

void moda(float *notas, int qnt){
    int max_freq = 0, frequencia = 1, modas_count = 0;
    float moda_val = -1;
    float *copia = (float*)malloc(qnt * sizeof(float));
    for(int i = 0; i < qnt; i++) copia[i] = notas[i];

    for(int i = 0; i<qnt-1; i++){
        for(int j = 0; j<qnt-i-1; j++){
            if(*(copia + j) > *(copia + j + 1)){
                float temp = *(copia + j);
                *(copia + j) = *(copia + j + 1);
                *(copia + j + 1) = temp;
            }
        }
    }
    for (int i = 0; i < qnt; i++) {
        // Verifica repetição com o próximo elemento
        if (i < qnt - 1 && copia[i] == copia[i+1]) {
            frequencia++;
        } else {
            // Fim de uma sequência de números iguais
            if (frequencia > max_freq) {
                max_freq = frequencia;
                moda_val = copia[i];
                modas_count = 1;
            } else if (frequencia == max_freq && frequencia > 1) {
                modas_count++;
            }
            frequencia = 1; // Reseta para a próxima sequência
        }
    }

    if (max_freq > 1 && modas_count == 1) printf("Moda: %.2f\n", moda_val);
    else puts("Moda: Nao ha moda unica");
}

void mediana(float *notas, int qnt){
    float *copia = (float*)malloc(qnt * sizeof(float));
    for(int i = 0; i < qnt; i++) copia[i] = notas[i];

    for(int i = 0; i<qnt-1; i++){
        for(int j = 0; j<qnt-i-1; j++){
            if(*(copia + j) > *(copia + j + 1)){
                float temp = *(copia + j);
                *(copia + j) = *(copia + j + 1);
                *(copia + j + 1) = temp;
            }
        }
    }
    float med;
    if(qnt % 2 != 0){
        med = *(copia + qnt/2);
    }else{
        med = (*(copia + qnt/2-1) + *(copia + qnt/2))/2;
    }
    printf("Mediana: %.2f\n", med);
    free(copia);
}

void media(float *notas, int qnt){
    float soma = 0;
    float maior_n = notas[0], menor_n = notas[0];
    int melhor_ind = 0, pior_ind = 0;
    for(int i = 0; i < qnt; i++){
        soma += *(notas + i);
        //procura a melhor nota
        if(*(notas + i) > maior_n){
            maior_n = *(notas + i);
            melhor_ind = i;
        }
        //procura pior nota
        if(*(notas + i) < menor_n){
            menor_n = *(notas + i);
            pior_ind = i;
        }
    }
    float media = soma / qnt;

    int acima_m = 0;
    //loop para saber a quantidade de alunos acima da media
    for(int j = 0; j < qnt; j++){
        if(*(notas + j) > media) acima_m++;
    }

    printf("Media: %.2f\n", media);
    printf("Maior nota: %.2f (aluno %d)\n", maior_n, melhor_ind+1);
    printf("Menor nota: %.2f (aluno %d)\n", menor_n, pior_ind+1);
    printf("Acima da media: %d\n", acima_m);
}

void relatorio(float *notas, int tam){
    float *temp_mediana = notas;
    //essa função é responsável por calcular tudo que está relacionado a medias e a maior/menor nota
    media(notas, tam);
    mediana(temp_mediana, tam);
    moda(temp_mediana, tam);
}

int main(){
    int n;
    scanf("%d", &n);

    float *notas = (float*)malloc(n * sizeof(float));
    if(notas == NULL) return 0;

    for(int i = 0; i < n; i++){
        scanf("%f", (notas + i));
    }
    puts("Relatorio inicial");
    float *notas_copia = notas;
    relatorio(notas_copia, n);

    int k = 0;
    scanf("%d", &k);
    if(k > 0) {
        float *notas_novas = realloc(notas, (n+k) * sizeof(float));
        if(notas_novas == NULL) {
            free(notas);
            return 0;
        }
        notas = notas_novas;
        for(int i = n; i < n + k; i++) {
            scanf("%f", &notas[i]);
        }
    }
    n += k;

    float *novas_copia = notas;
    puts("");
    puts("Relatorio atualizado");
    relatorio(novas_copia, n);

    free(notas);
    return 0;
}