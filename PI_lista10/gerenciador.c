#include <stdio.h>
#include <stdlib.h>

// 1. Definição da struct conforme solicitado
typedef struct Tarefa {
    int id;
    int prioridade;
    struct Tarefa* prox;
} Tarefa;

// 2. Função para inserir no FINAL da fila (Enqueue)
void inserir(Tarefa** inicio, Tarefa** final, int id, int prioridade) {
    Tarefa* novo = (Tarefa*)malloc(sizeof(Tarefa));
    novo->id = id;
    novo->prioridade = prioridade;
    novo->prox = NULL; // Como vai para o final, o próximo dele é NULL

    // Se a fila estiver vazia, o novo nó será tanto o início quanto o final
    if (*inicio == NULL) {
        *inicio = novo;
        *final = novo;
    } else {
        // O atual final passa a apontar para o novo nó
        (*final)->prox = novo;
        // O ponteiro 'final' é atualizado para o novo nó
        *final = novo;
    }
}

// 3. Função para remover do INÍCIO da fila (Dequeue)
void remover(Tarefa** inicio, Tarefa** final) {
    if (*inicio == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Tarefa* temp = *inicio;
    
    // Imprime os dados conforme o formato exigido: "Removida: id=X prioridade=Y"
    printf("Removida: id=%d prioridade=%d\n", temp->id, temp->prioridade);

    // O início avança para o próximo nó
    *inicio = (*inicio)->prox;

    // CASO ESPECIAL: Se a fila tinha apenas 1 elemento e ficou vazia,
    // o ponteiro 'final' também precisa ser atualizado para NULL
    if (*inicio == NULL) {
        *final = NULL;
    }

    // Libera a memória do nó removido
    free(temp);
}

// 4. Função para listar a fila do início ao fim
void listar(Tarefa* inicio) {
    if (inicio == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Tarefa* atual = inicio;
    while (atual != NULL) {
        printf("id=%d prioridade=%d\n", atual->id, atual->prioridade);
        atual = atual->prox;
    }
}

// Função auxiliar para limpar a memória restante ao encerrar o programa
void limpar_fila(Tarefa** inicio, Tarefa** final) {
    while (*inicio != NULL) {
        Tarefa* temp = *inicio;
        *inicio = (*inicio)->prox;
        free(temp);
    }
    *final = NULL;
}

int main() {
    // Inicialização dos ponteiros auxiliares da fila
    Tarefa* inicio = NULL;
    Tarefa* final = NULL;
    
    char comando;
    int id, prioridade;

    // Loop de leitura dos comandos até encontrar 'F' ou EOF
    while (scanf(" %c", &comando) != EOF) {
        if (comando == 'F') {
            break; // Encerra o programa
        }
        
        switch (comando) {
            case 'I':
                scanf("%d %d", &id, &prioridade);
                inserir(&inicio, &final, id, prioridade);
                break;
                
            case 'R':
                remover(&inicio, &final);
                break;
                
            case 'L':
                listar(inicio);
                break;
                
            default:
                // Ignora comandos inválidos caso existam
                break;
        }
    }

    // Boa prática: liberar qualquer memória que ainda tenha ficado na fila
    limpar_fila(&inicio, &final);

    return 0;
}