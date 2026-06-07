#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char titulo[20];
    char genero[20];
    char estudio[20];
    char console[20];
    int nota;
    int ano;
}info;

int main(){
    int n;
    scanf("%d", &n);

    info colecao[100];

    for(int l = 0; l<n; l++){
        scanf("%s %s %s %s %d %d", colecao[l].titulo, colecao[l].genero, colecao[l].estudio, colecao[l].console, &colecao[l].nota, &colecao[l].ano);

        //condiçoes das notas
        if(colecao[l].nota > 7)puts("AWESOME! Mais um GOTY pra minha coleção!");
        else if(colecao[l].nota < 4)puts("Era melhor jogar mais um jogo de Mahjong.");
    }

    //loop das funçoes
    char cmd[30];
    while(scanf("%s", cmd) != EOF){
        //condição printano
        if(strcmp(cmd, "printAno") == 0){
            int lancado;
            scanf(" %d", &lancado);

            //procura ano de lancamento
            int ano_qnt = 0;
            for(int a = 0; a<n; a++){
                if(colecao[a].ano == lancado){
                    ano_qnt++;
                    printf("%s\n", colecao[a].titulo);
                }
            }
            if(ano_qnt > 0)printf("Tenho %d jogos || %d.\n", ano_qnt, lancado);
            else puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
        }
        else if(strcmp(cmd, "printLetra") == 0){
            char letra;
            scanf(" %c", &letra);

            int qnt_letra = 0;
            for(int le = 0; le<n; le++){
                if(colecao[le].titulo[0] == letra){
                    qnt_letra++;
                    printf("%s\n", colecao[le].titulo);
                }
            }
            if(qnt_letra > 0)printf("Tenho %d jogos || %c.\n", qnt_letra, letra);
            else puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
        }
        else if(strcmp(cmd, "printStudio") == 0){
            char studio[20];
            scanf(" %s", studio);

            //procura o estudio
            int qnt_estudio = 0;
            for(int s = 0; s<n; s++){
                if(strcmp(colecao[s].estudio, studio) == 0){
                    qnt_estudio++;
                    printf("%s\n", colecao[s].titulo);
                }
            }
            if(qnt_estudio > 0)printf("Tenho %d jogos || %s.\n", qnt_estudio, studio);
            else puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
        }
        else if(strcmp(cmd, "printConsole") == 0){
            char console[20];
            scanf(" %s", console);

            //procura se esse console existe
            int qnt_console = 0;
            for(int c = 0; c<n; c++){
                if(strcmp(colecao[c].console, console) == 0){
                    qnt_console++;
                    printf("%s\n", colecao[c].titulo);
                }
            }
            if(qnt_console > 0)printf("Tenho %d jogos || %s.\n", qnt_console, console);
            else puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
        }
        else if(strcmp(cmd, "printColecao") == 0){
            for(int cn = 0; cn<n; cn++){
                printf("%s %d\n", colecao[cn].titulo, colecao[cn].nota);
            }
        }
    }
    puts("Enjoei de jogar, agora vou ver TV.");
    return 0;
}
