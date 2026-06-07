#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NOME 50
#define MAX_LINHA 200

typedef struct{
    int codigo;
    char nome[MAX_NOME];
    int qnt;
    double preco;
}produto;

typedef struct {
    int codigo;
    char tipo;
    int qnt;
    char problema[MAX_NOME];
}incosistencias;

int main(){
    FILE *f_prod = fopen("produtos.txt", "r");
    FILE *f_mov = fopen("movimentos.txt", "r");

    if(f_prod == NULL || f_mov == NULL){
        puts("erro ao abrir os arquivos");
        if(f_prod != NULL)fclose(f_prod);
        if(f_mov != NULL)fclose(f_mov);
        exit(1);
    }
    int qnt_produto = 0;
    produto *produtos = NULL;
    char linha[MAX_LINHA];

    produto temp;
    while(fscanf(f_prod, "%d %s %d %lf", &temp.codigo, temp.nome, &temp.qnt, &temp.preco) == 4){
        produtos = realloc(produtos, (qnt_produto + 1)*sizeof(produto));
        if(produtos == NULL)exit(1);
        produtos[qnt_produto] = temp;
        qnt_produto++;
    }
    fclose(f_prod);

    int valido_mov = 0, saidas_recusadas = 0, sem_cadastro = 0, erros = 0;
    incosistencias *erro = NULL;

    int codigo_m, qnt_m;
    char tipo;

    while(fscanf(f_mov, "%d %c %d", &codigo_m, &tipo, &qnt_m) == 4){
        int encontraddo = 0;
        for(int i = 0; i<qnt_produto; i++){
            if(codigo_m == produtos[i].codigo){
                encontraddo = 1;
                if(tipo == 'E'){
                    produtos[i].qnt+=qnt_m;
                    valido_mov++;
                }else{
                    if(produtos[i].qnt - qnt_m < 0){
                        erro = realloc(erro, (erros + 1)*sizeof(incosistencias));
                        erro[erros] = (incosistencias){codigo_m, tipo, qnt_m, "ESTOQUE_INSUFICIENTE"};
                        saidas_recusadas++;
                        erros++;
                    }else{
                        produtos[i].qnt-=qnt_m;
                        valido_mov++;
                    }
                }
            }
        }
        if(!encontraddo){
            sem_cadastro++;
            erro = realloc(erro, (erros + 1)*sizeof(incosistencias));
            erro[erros] = (incosistencias){codigo_m, tipo, qnt_m, "PRODUTO_INEXISTENTE"};
            erros++;
        }
    }
    fclose(f_mov);

    FILE *f_estoque_atualizado = fopen("estoque_atualizado.txt", "w");
    FILE *f_relatorio = fopen("relatorio.txt", "w");

    if (f_estoque_atualizado == NULL || f_relatorio == NULL) {
        printf("Erro ao criar os arquivos de saida.\n");
        free(produtos);
        free(erro);
        exit(1);
    }

    // Gerando estoque_atualizado.txt (Mantendo a ordem original)
    for (int i = 0; i < qnt_produto; i++) {
        fprintf(f_estoque_atualizado, "%d %s %d %.2f\n", 
                produtos[i].codigo, produtos[i].nome, produtos[i].qnt, produtos[i].preco);
    }
    fclose(f_estoque_atualizado);

    // Gerando relatorio.txt
    fprintf(f_relatorio, "PRODUTOS PROCESSADOS: %d\n", qnt_produto);
    fprintf(f_relatorio, "MOVIMENTOS APLICADOS: %d\n", valido_mov);
    fprintf(f_relatorio, "SAIDAS RECUSADAS: %d\n", saidas_recusadas);
    fprintf(f_relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", sem_cadastro);
    
    // Lista de Estoque Baixo (<= 5)
    fprintf(f_relatorio, "ESTOQUE BAIXO:\n");
    for (int i = 0; i < qnt_produto; i++) {
        if (produtos[i].qnt <= 5) {
            fprintf(f_relatorio, "%d %s %d\n", produtos[i].codigo, produtos[i].nome, produtos[i].qnt);
        }
    }

    // Lista de Inconsistências salvas na memória
    fprintf(f_relatorio, "INCONSISTENCIAS:\n");
    for (int i = 0; i < erros; i++) {
        fprintf(f_relatorio, "%d %c %d %s\n", erro[i].codigo, erro[i].tipo, erro[i].qnt, erro[i].problema);
    }
    fclose(f_relatorio);

    free(produtos);
    free(erro);

    return 0;
}