#include <stdio.h>

int main(){
    int div1, div2, div3;
    int carteira = 3;
    int premio, p1, p2, p3;
    scanf("%d", &premio);
    scanf("%d", &p1);
    scanf("%d", &p2);
    scanf("%d", &p3);

    //se as porcentagens derem num inteiros
    if ((premio * p1) % 100 == 0 && (premio * p2) % 100 == 0 && (premio * p3) % 100 == 0){
        //calculo de divisão do premio
        int div1 = (premio * p1) / 100;
        int div2 = (premio * p2) / 100;
        int div3 = (premio * p3) / 100;
        int resto1 = premio - (div1 + div2 + div3);
        carteira += resto1;
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", div1, div2, div3);
    //acrescenta 1 real
    }else if(((premio + 1) * p1) % 100 == 0 && ((premio + 1) * p2) % 100 == 0 && ((premio + 1) * p3) % 100 == 0) {
        int novo_total = premio + 1;
        div1 = (novo_total * p1) / 100;
        div2 = (novo_total * p2) / 100;
        div3 = (novo_total * p3) / 100;
        int sobra = novo_total - (div1 + div2 + div3);
        
        if (sobra > 1) { // Sobra >= investimento + 1
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", div1, div2, div3);
            carteira = (carteira - 1) + sobra;
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        }
    //acrescenta 2 reais
    }else if (((premio + 2) * p1) % 100 == 0 && ((premio + 2) * p2) % 100 == 0 && ((premio + 2) * p3) % 100 == 0) {
        int novo_total = premio + 2;
        div1 = (novo_total * p1) / 100;
        div2 = (novo_total * p2) / 100;
        div3 = (novo_total * p3) / 100;
        int sobra = novo_total - (div1 + div2 + div3);

        if (sobra > 2) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", div1, div2, div3);
            carteira = (carteira - 2) + sobra;
            char l1, l2, l3;
            scanf(" %c %c %c", &l1, &l2, &l3);
            //explicação da subtração de 96: como 'a' vale 97 e na questão ele deve valer 1 entao para que ele e as demais fiquem corretas subtrai 96
            printf("%d\n", (l1 - 96) + (l2 - 96) + (l3 - 96));
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        }
    //acrescenta 3 reais
    }else if (((premio + 3) * p1) % 100 == 0 && ((premio + 3) * p2) % 100 == 0 && ((premio + 3) * p3) % 100 == 0) {
        int novo_total = premio + 3;
        div1 = (novo_total * p1) / 100;
        div2 = (novo_total * p2) / 100;
        div3 = (novo_total * p3) / 100;
        int sobra = novo_total - (div1 + div2 + div3);

        if (sobra > 3) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", div1, div2, div3);
            carteira = (carteira - 3) + sobra;
            int i1, i2, i3;
            scanf("%d %d %d", &i1, &i2, &i3);
            if (i1 % 3 == 0 || i2 % 3 == 0 || i3 % 3 == 0) {
                int soma_parcelas3 = 0;
                if(i1 % 3 == 0){
                    soma_parcelas3+=i1 / 3;
                }
                if (i2 % 3 == 0){
                    soma_parcelas3 += i2 / 3;
                }
                if (i3 % 3 == 0){
                    soma_parcelas3 += i3 / 3;
                }
                printf("%d\n", soma_parcelas3);
            }
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        }
    }
    // Caso nenhuma tentativa funcione
    else {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
    }
    // verifica se rebeca tem dinheiro ou nao para o onibus
    if (carteira >= 7.0) {
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    } else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }
    return 0;
}