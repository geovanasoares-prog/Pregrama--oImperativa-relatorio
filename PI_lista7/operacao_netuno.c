//usei bastante o gemini para interpretar esse problema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//indica que existe uma struct Mecha
typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib2;     // Atk: Custo Ener. | Def: Bônus de Slot   | Utl: Multiplicador
    
    // Função Modular: deve ser atribuída conforme o tipo do sistema.
    // m: ponteiro para o mecha dono do sistema.
    // slot: o índice da posição de entrada deste sistema no array sistemas[]
    // input: o dano base enviado pelo Wintermute para o combate.
    // output: onde deve ser gravado o resultado final da operação.
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;                // Identificador único (0 até N-1)
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;       // Contexto de dano enviado pelo Comando
    SubSistema sistemas[]; // O Flexible Array Member (FAM)
};

void defesa(Mecha *m, int slot, int input, int *output){
    int dano = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if(dano < 0)dano = 0;
    *output = dano;
}

void ataque(Mecha *m, int slot, int input, int *output){
    int dano;
    if(m->energia_atual < m->sistemas[slot].atrib2){
        dano = -1;
    }
    else{
        dano = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= m->sistemas[slot].atrib2;
    }
    *output = dano;
}

void utilidade(Mecha *m, int slot, int input, int *output){
    m->energia_atual += m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
}

void (*ordem[])(Mecha*, int, int, int*) = {defesa, utilidade, ataque};

int main(){
    int N;
    scanf("%d", &N);
    Mecha **esquadrao = (Mecha**)malloc(N * sizeof(Mecha*));
    if(esquadrao == NULL)exit(1);

    //loop para cada mecha
    for(int qnt_m = 0; qnt_m<N; qnt_m++){
        int id, enegia, q;
        char modelo[20];
        scanf("%d %s %d %d", &id, modelo, &enegia, &q);

        //precisa de espaço para o struct mecha e os q struct subsistemas
        Mecha *robo = (Mecha*)malloc(sizeof(Mecha) + q * sizeof(SubSistema));
        if(robo == NULL)exit(1);

        robo->energia_atual = enegia;
        robo->id = id;
        robo->num_sistemas = q;
        strcpy(robo->modelo, modelo);

        //loop para cada sistema
        for(int qnt_s = 0; qnt_s<q; qnt_s++){
            char tipo;
            scanf(" %c %s %d %d", &tipo, robo->sistemas[qnt_s].nome, &robo->sistemas[qnt_s].atrib1, &robo->sistemas[qnt_s].atrib2);

            //define qual é o tipo e sua funçaõ
            if(tipo == 'A')robo->sistemas[qnt_s].subrotina = ataque;
            else if(tipo == 'D')robo->sistemas[qnt_s].subrotina = defesa;
            else if(tipo == 'U')robo->sistemas[qnt_s].subrotina = utilidade;
        }
        int valor;
        scanf("%d", &valor);
        robo->valor_wintermute = valor;
        //define os mechas na ordem correta dos ids
        esquadrao[id] = robo;
    }
    //calculos e relatorio
    puts("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]");
    for(int mecah = 0; mecah<N; mecah++){
        Mecha *m = esquadrao[mecah];
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, m->energia_atual);

        //ambos loops servem para realizar as rotinas em ordem mas ainda preservar o slot
        //loop das rotinas
        for(int r = 0; r<3; r++){
            //loop da quantidade de sistemas para preservar o slot original
            for(int s = 0; s< m->num_sistemas; s++){
                if(m->sistemas[s].subrotina == ordem[r]){
                    int resultado;
                    //chama a função da rotina
                    m->sistemas[s].subrotina(m, s, m->valor_wintermute, &resultado);

                    //verifica qual rotina foi realizada
                    if(ordem[r] == defesa){
                        printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[s].nome, resultado);
                    }
                    else if(ordem[r] == utilidade)printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[s].nome, m->energia_atual);
                    else if(ordem[r] == ataque){
                        if(resultado == -1)printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[s].nome);
                        else printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[s].nome, resultado, m->energia_atual);
                    }
                }
            }
        }
        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        puts("-----------------------------------------");
        free(m);
    }
    puts("Esquadrao pronto para o combate.");
    free(esquadrao);

    return 0;
}