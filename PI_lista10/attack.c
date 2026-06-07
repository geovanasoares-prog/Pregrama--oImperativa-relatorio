#include <stdio.h>
#include <stdlib.h>

// Definição do nó da Pilha (Lista Encadeada)
typedef struct Bloco {
    char cor;
    struct Bloco* abaixo;
} Bloco;

// Função para inserir no topo da pilha (Push)
void push(Bloco** topo, char cor) {
    Bloco* novo = (Bloco*)malloc(sizeof(Bloco));
    novo->cor = cor;
    novo->abaixo = *topo;
    *topo = novo;
}

// Função para remover do topo da pilha (Pop)
char pop(Bloco** topo) {
    if (*topo == NULL) return '\0';
    Bloco* temp = *topo;
    char cor = temp->cor;
    *topo = temp->abaixo;
    free(temp);
    return cor;
}

// Função auxiliar para determinar o resultado da fusão de duas cores
char verificar_fusao(char c1, char c2) {
    if ((c1 == 'g' && c2 == 'b') || (c1 == 'b' && c2 == 'g')) return 'c'; // Verde + Azul = Ciano
    if ((c1 == 'r' && c2 == 'b') || (c1 == 'b' && c2 == 'r')) return 'm'; // Vermelho + Azul = Magenta
    if ((c1 == 'r' && c2 == 'g') || (c1 == 'g' && c2 == 'r')) return 'y'; // Vermelho + Verde = Amarelo
    return '\0'; // Nenhuma fusão possível
}

// Função principal da lógica do jogo: processa o bloco atual na pilha
void processar_bloco(Bloco** topo, char X) {
    // O loop continua enquanto o bloco atual 'X' precisar ser testado
    while (X != '\0') {
        // Cenário 1: Pilha vazia, o bloco apenas entra
        if (*topo == NULL) {
            push(topo, X);
            X = '\0'; // Bloco processado com sucesso
        } 
        else {
            char fusao = verificar_fusao((*topo)->cor, X);
            
            // Cenário 2: O bloco atual reage com o bloco do topo
            if (fusao != '\0') {
                pop(topo); // Remove o antigo topo que reagiu
                X = fusao; // O bloco atual se transforma na nova cor e o loop continua!
            } 
            // Cenário 3: Destruição de 3 blocos iguais
            // Se o bloco atual for igual ao topo E o elemento abaixo do topo também for igual
            else if ((*topo)->cor == X && (*topo)->abaixo != NULL && (*topo)->abaixo->cor == X) {
                pop(topo); // Remove o primeiro do topo
                pop(topo); // Remove o segundo do topo
                X = '\0';  // O terceiro bloco (X) é descartado/destruído. Fim do processamento.
            } 
            // Cenário 4: Não funde e não destrói, apenas empilha
            else {
                push(topo, X);
                X = '\0'; // Bloco processado com sucesso
            }
        }
    }
}

// Função recursiva para imprimir a pilha do fundo (base) até o topo
void imprimir_pilha_recursiva(Bloco* topo) {
    if (topo == NULL) return;
    printf("%c\n", topo->cor); 
    imprimir_pilha_recursiva(topo->abaixo);
}

// Controla a exibição da pilha e a formatação das linhas
void exibir_resultado(Bloco* topo) {
    if (topo == NULL) {
        printf("Pilha vazia!\n");
    } else {
        imprimir_pilha_recursiva(topo);
    }
    printf("\n");
}

// Função para liberar a memória da pilha no fim do programa
void limpar_pilha(Bloco** topo) {
    while (*topo != NULL) {
        pop(topo);
    }
}

int main() {
    Bloco* pilha = NULL;
    char novo_bloco;

    // Lê os caracteres até o Fim do Arquivo (EOF)
    // O espaço antes de %c serve para ignorar quebras de linha (\n) do input
    while (scanf(" %c", &novo_bloco) != EOF) {
        
        processar_bloco(&pilha, novo_bloco);
        
        exibir_resultado(pilha);
    }

    // Mensagem de encerramento exigida pelo enunciado
    printf("Thank You So Much For Playing My Game!\n");

    // Boa prática: liberar a memória antes de fechar
    limpar_pilha(&pilha);

    return 0;
}