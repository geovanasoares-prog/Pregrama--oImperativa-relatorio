#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definição do nó que representa um aluno/requisição
typedef struct Aluno {
    long long mat;
    int pri;
    double cr;
    long long L;
    long long R;
    struct Aluno* prox;
} Aluno;

// Estrutura que gerencia as extremidades da Fila (Head e Tail) em O(1)
typedef struct Queue {
    Aluno* head;
    Aluno* tail;
} Queue;

// Inicializa uma fila vazia
void init_queue(Queue* q) {
    q->head = NULL;
    q->tail = NULL;
}

// Inserção no final da fila (Enqueue)
void enqueue(Queue* q, Aluno* novo) {
    novo->prox = NULL;
    if (q->head == NULL) {
        q->head = novo;
        q->tail = novo;
    } else {
        q->tail->prox = novo;
        q->tail = novo;
    }
}

// Remoção no início da fila (Dequeue)
Aluno* dequeue(Queue* q) {
    if (q->head == NULL) {
        return NULL;
    }
    Aluno* temp = q->head;
    q->head = q->head->prox;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    return temp;
}

// Libera a memória restante de uma fila de forma segura
void clear_queue(Queue* q) {
    while (q->head != NULL) {
        Aluno* temp = dequeue(q);
        free(temp);
    }
}

int main() {
    char cmd[20];
    char nome_disciplina[55];
    int vagas = 0;
    long long tempo_atual = 1;

    Queue req_queue;
    Queue conf_queue;
    
    init_queue(&req_queue);
    init_queue(&conf_queue);

    // Processa os fluxos de entrada dinamicamente até o fim do arquivo (EOF)
    while (scanf("%s", cmd) != EOF) {
        
        if (strcmp(cmd, "START") == 0) {
            scanf("%s %d", nome_disciplina, &vagas);
            tempo_atual = 1;
            // Garante que as filas estão limpas para um novo ciclo de disciplina
            clear_queue(&req_queue);
            clear_queue(&conf_queue);
        } 
        
        else if (strcmp(cmd, "ADD") == 0) {
            Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
            scanf("%lld %d %lf %lld %lld", &novo->mat, &novo->pri, &novo->cr, &novo->L, &novo->R);
            enqueue(&req_queue, novo);
        } 
        
        else if (strcmp(cmd, "PROC") == 0) {
            int qtd;
            scanf("%d", &qtd);
            
            for (int i = 0; i < qtd; i++) {
                Aluno* aluno = dequeue(&req_queue);
                if (aluno == NULL) {
                    break; // Fila de requisições esvaziou antes da cota do lote
                }

                // Se o servidor ficou ocioso aguardando o aluno, o relógio salta para L
                if (tempo_atual < aluno->L) {
                    tempo_atual = aluno->L;
                }

                // Cenário 1: TIMEOUT - O tempo atual estourou a tolerância do aluno
                if (tempo_atual > aluno->R) {
                    printf("[TIMEOUT] mat=%lld | Desconectado da fila.\n", aluno->mat);
                    free(aluno); // Requisição descartada
                } 
                // Cenário 2: Processamento válido (Pode ser ALOCADO ou LOTADO)
                else {
                    // Cálculo do Score utilizando o round() da <math.h>
                    int score = (int)round(aluno->cr * 100.0) / aluno->pri;
                    
                    if (vagas > 0) {
                        printf("[ALOCADO] mat=%lld | score=%d | Processado no seg: %lld\n", 
                               aluno->mat, score, tempo_atual);
                        vagas--;
                        enqueue(&conf_queue, aluno); // Transfere o nó para a lista oficial
                    } else {
                        printf("[LOTADO] mat=%lld | score=%d | Processado no seg: %lld\n", 
                               aluno->mat, score, tempo_atual);
                        free(aluno); // Não há vagas, desaloca o nó
                    }
                    
                    // O relógio avança 1 segundo após cada processamento com sucesso
                    tempo_atual++;
                }
            }
        } 
        
        else if (strcmp(cmd, "FIM") == 0) {
            printf("--- LISTA OFICIAL: %s ---\n", nome_disciplina);
            int posicao = 1;
            while (conf_queue.head != NULL) {
                Aluno* conf = dequeue(&conf_queue);
                printf("%d. Matricula: %lld\n", posicao++, conf->mat);
                free(conf); // Liberação final da memória após a impressão
            }
            // Limpa qualquer requisição residual que não foi processada por um PROC
            clear_queue(&req_queue);
        }
    }

    return 0;
}