#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

typedef struct{
    char nome[50];
    int populacao;
    char periculosidade[10];
    char funcao[50];
}cidadela;

int ordenar(const void *a, const void *b){
    cidadela *ca = (cidadela *)a;
    cidadela *cb = (cidadela *)b;

    //ordena por habitante
    if(ca->populacao != cb->populacao) return cb->populacao - ca->populacao;

    //ordena por perigo
    int pA = strlen(ca->periculosidade);
    int pB = strlen(cb->periculosidade);
    if(pA != pB) return pB - pA;

    //ordem lexografica
    return strcmp(ca->nome, cb->nome);
}
void formatar(char palavra[], int tamanho){
    for(int i = 0; i<tamanho; i++){
        if(i == 0)palavra[0] = toupper(palavra[0]);
        else palavra[i] = tolower(palavra[i]);
    }
}

int main(){
    cidadela lista[100];
    char linha[220];
    int zark_lugar = -1, qnt_cidadela = 0;

    while(fgets(linha, sizeof(linha), stdin)){
        linha[strcspn(linha, "\n")] = 0;//limita o input para apenas uma linha e adiciona o \0
        //caso a linha seja vazia
        if(strlen(linha) == 0)continue;
        
        int ha_chave = -1, qnt_asteristico = 0, qnt_nome = 0, qnt_num = 0, qnt_funcao = 0;
        char nome_cidade[30], num_str[30], funcao_cidade[30], asteristico_str[10];
        //ler a linha
        for(int c = 0; c<strlen(linha); c++){
            //verifica se ha exclamação
            if(linha[c] == 33) ha_chave = 1;
            
            //conta os asteristicos
            if(linha[c] == 42){
                asteristico_str[qnt_asteristico] = 42;
                qnt_asteristico++;
            }
            
            //verifica se é letra maiuscula
            if(isupper(linha[c])){
                nome_cidade[qnt_nome] = linha[c];
                qnt_nome++;
            }
            //verifica se é número
            if(isdigit(linha[c])){
                num_str[qnt_num++] = linha[c];
            }
            //identifica se ha espaços duplos
            if(linha[c] == ' ' && linha[c+1] == ' '){
                int i = c + 2;
                //pula o que não for letra
                while(!isalpha(linha[i])) i++;
                funcao_cidade[qnt_funcao] = linha[i];
                qnt_funcao++;
            }
        }
        //adiciona o /0
        nome_cidade[qnt_nome] = '\0';
        funcao_cidade[qnt_funcao] = '\0';
        asteristico_str[qnt_asteristico] = '\0';
        num_str[qnt_num] = '\0';
        
        int num = atoi(num_str);
        
        //formatar a funçõa e o nome
        formatar(nome_cidade, qnt_nome);
        formatar(funcao_cidade, qnt_funcao);
        
        //verifica se é uma mensagem especial
        if(ha_chave == 1) zark_lugar = num;
        else{
            strcpy(lista[qnt_cidadela].periculosidade, asteristico_str);
            strcpy(lista[qnt_cidadela].funcao, funcao_cidade);
            strcpy(lista[qnt_cidadela].nome, nome_cidade);
            lista[qnt_cidadela].populacao = num;
            qnt_cidadela++;
        }
    }
    //ordenar a lista
    qsort(lista, qnt_cidadela, sizeof(cidadela), ordenar);

    //verifica se zark mandou a sua localização
    if(zark_lugar == -1)puts("Gingrey ainda não foi achada, vamos esperar mais um pouco.");
    else{
        cidadela local = lista[zark_lugar-1];
        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade %s. ", local.nome, local.populacao, local.funcao, local.periculosidade);
        if(local.populacao > 1000 && strlen(local.periculosidade) > 3)printf("Talvez seja melhor desistir...");
        else if(local.populacao >= 1000)printf("Um lugar denso, vai ser difícil achar ela.");
        else if(strlen(local.periculosidade) > 3)printf("Vai ser complicado entrar lá.");
        puts("");
    }
}