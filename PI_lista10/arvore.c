#include<stdio.h>
#include<stdlib.h>

typedef struct No {
    int valor;
    struct No* menor;
    struct No* maior;
} No;

void inserir(No **arvore, int valor, int *qnt){
    if(*arvore == NULL){//se o no estiver vazio
        (*qnt)++;
        *arvore = (No*)malloc(sizeof(No));
        if(*arvore != NULL){
            (*arvore)->valor = valor;
            (*arvore)->menor = NULL;
            (*arvore)->maior = NULL;
        }else exit(1);
    }else{
        if(valor < (*arvore)->valor){
            inserir(&(*arvore)->menor, valor, qnt);
        }else if(valor > (*arvore)->valor){
            inserir(&(*arvore)->maior, valor, qnt);
        }
    }
}

void emordem(No *arvore, int *qnt_folhas){
    if(arvore != NULL){
        emordem(arvore->menor, qnt_folhas);
        printf(" %d", arvore->valor);
        emordem(arvore->maior, qnt_folhas);

        //conta as folhas quando o for o ultimo no
        if(arvore->menor == NULL && arvore->maior == NULL){
            (*qnt_folhas)++;
        }
    }
}

void preordem(No *arvore){
    if(arvore != NULL){
        printf(" %d", arvore->valor);
        preordem(arvore->menor);
        preordem(arvore->maior);
    }
}

void posordem(No *arvore){
    if(arvore != NULL){
        posordem(arvore->menor);
        posordem(arvore->maior);
        printf(" %d", arvore->valor);
    }
}
int calcular_altura(No *arvore) {
    if (arvore == NULL) return -1; // Convenção: árvore vazia tem altura -1 (ou 0 se preferir)
    
    int alt_esquerda = calcular_altura(arvore->menor);
    int alt_direita = calcular_altura(arvore->maior);
    
    if (alt_esquerda > alt_direita) {
        return alt_esquerda + 1;
    } else {
        return alt_direita + 1;
    }
}

int main(){
    int qnt = 0, valor, menor = 0, maior = 0, qnt_folhas = 0;
    No *arvore = NULL;
    while(scanf("%d", &valor) == 1 && valor != -1){
        //caso seja o primeiro valor, ele é o menor e o maior
        if(qnt == 0){
            menor = valor;
            maior = valor;
        }
        //descobre se é o menor
        if(valor < menor){
            menor = valor;
        }
        //descobre se é o maior
        if(valor > maior){
            maior = valor;
        }
        inserir(&arvore, valor, &qnt);
    }

    if(qnt == 0){
        printf("ARVORE VAZIA\n");
        return 0;
    }
    //imprime preorde
    printf("PREORDEM:");
    preordem(arvore);
    puts("");

    //imprime emordem
    printf("EMORDEM:");
    emordem(arvore, &qnt_folhas);
    puts("");

    //imprime posordem
    printf("POSORDEM:");
    posordem(arvore);
    puts("");

    //impreme quantidade de nos
    printf("NOS: %d\n", qnt);

    //imprime folhas
    printf("FOLHAS: %d\n", qnt_folhas);

    //imprime altura
    printf("ALTURA: %d\n", calcular_altura(arvore));

    //imprime menor
    printf("MENOR: %d\n", menor);

    //imprime maior
    printf("MAIOR: %d\n", maior);

    return 0;
}