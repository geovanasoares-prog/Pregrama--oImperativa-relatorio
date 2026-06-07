#include <stdio.h>
int main(){
    int n, x, y;
    scanf("%d", &n);
    scanf("%d", &x);
    scanf("%d", &y);
    // loop para receber os horarios
    int horarios[y], energeticos[y];
    for(int i = 0; i < y; i++){
        int hora, min, qnt;
        scanf("%d:%d %d", &hora, &min, &qnt);
        horarios[i] = (hora * 60) + min;
        energeticos[i] = qnt;
    }
    //loop dos clientes
    int tempo_atual = 420, energ_vendidos = 0, vencendor = 0; // 7 * 60 = 420
    for(int cliente = 1; cliente <= n; cliente++){
        tempo_atual+=3;
        //verifica se o cliente comprou mais de 1 energetico
        for(int j = 0; j < y; j++){
            if(horarios[j] == tempo_atual){
                energ_vendidos+=energeticos[j];
                if(0 != x && cliente % x == 0){
                    energ_vendidos-=1;
                }
                //verifica se é a 50º lata
                if(energ_vendidos >= 50 && 0 == vencendor){
                    vencendor = 1;
                    printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.", cliente, tempo_atual/60, tempo_atual%60, energeticos[j]);//nessa situação sempre vai ser plural
                }       
            }
        }// verifica se o cliente é multiplo de x
        if(0 != x && cliente % x == 0){
            energ_vendidos += 1;
            //verifica se é a 50º lata
            if(energ_vendidos >= 50 && 0 == vencendor){
                vencendor = 1;
                printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d lata.", cliente, tempo_atual/60, tempo_atual%60, 1);//nessa situação sempre vai ser singular
            }       
        }
    }//caso não haja vencedor
    if(0 == vencendor){
        printf( "Ainda nao foram vendidas latas suficientes.");
        if (50 - energ_vendidos > 1){
            printf(" Faltam %d latas.", 50 - energ_vendidos);
        }else{
            printf(" Falta 1 lata.");
        }
    }return 0;
}