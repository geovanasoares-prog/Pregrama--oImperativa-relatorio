#include <stdio.h>
#include <stdlib.h>

void ordenar(int *num, int tam);

void ordenar(int *num, int tam){
    //criar dois vetores para numeros pares e impares
    int par[300], impar[300], ind_par = 0, ind_impar = 0;

    for(int i = 0; i < tam; i++){
        if(*(num + i) % 2 != 0){
            impar[ind_impar] = *(num + i);
            ind_impar++;
        }else{
            par[ind_par] = *(num + i);
            ind_par++;
        }
    }
    //adicionar os impares
    for(int m = 0; m < ind_impar; m++){
        *(num + m) = impar[m];
    }
    //adiciona os pares
    int j = 0;
    for(int n = ind_impar; n < ind_impar + ind_par; n++){
        *(num + n) = par[j];
        j++;
    }
}
int main(){
    int num, i = 0;
    int *todos_num = (int*)malloc(300 * sizeof(int));
    if(todos_num == NULL) return 0;

    while(scanf("%d", &num) == 1){
        todos_num[i] = num;
        i++;
    }
    int *num_ordenados = todos_num;
    ordenar(num_ordenados, i);

    puts("Mais um bom dia de trabalho!");

    for(int k = 0; k<i; k++) printf("%d\n", *(num_ordenados+k));

    puts("Vou visitar esses lugares de novo... algum dia.");
    
    free(todos_num);
    return 0;
}