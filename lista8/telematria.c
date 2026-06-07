#include <stdio.h>
#include <stdlib.h>

typedef union{
    unsigned int dadoBruto;
    struct{
        unsigned int id : 10;
        unsigned int status : 3;
        unsigned int bateria : 1;
        int temperatura : 12;
        unsigned int controle : 6;
    }campo;
}pacote;

void imprimir(pacote *vetor, int total){
    for(int i = 0; i<total; i++){
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i + 1, vetor[i].dadoBruto);
        printf("ID do Sensor : %u\n", vetor[i].campo.id);
        printf("Status       : %u\n", vetor[i].campo.status);
        printf("Bateria Baixa: %s\n", vetor[i].campo.bateria ? "SIM (ALERTA)" : "Nao");
        printf("Temperatura  : %d graus\n", vetor[i].campo.temperatura);
        printf("-------------------------------------------------\n");
    }
}
int main(){
    int tam_vetor = 2;
    int total_pacotes = 0;
    
    //vetor dinamico para guardar os dados
    pacote *vetor = (pacote*)malloc(tam_vetor * sizeof(pacote));
    if(vetor == NULL)exit (1);

    //loop para receber os pacotes
    unsigned int entrada;
    while(scanf("%x", &entrada) == 1 && entrada != 0){
        if(tam_vetor == total_pacotes){
            tam_vetor *= 2;
            pacote *temp = (pacote*)realloc(vetor, tam_vetor * sizeof(pacote));
            if(temp == NULL){
                free(vetor);
                exit(1);
            }
            vetor = temp;
        }
        vetor[total_pacotes].dadoBruto = entrada;
        total_pacotes++;
    }
    if(total_pacotes > 0){
        imprimir(vetor, total_pacotes);
    }
    free(vetor);
    return 0;
}