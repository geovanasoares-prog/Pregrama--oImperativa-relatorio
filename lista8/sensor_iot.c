#include <stdio.h>

union byte{
    unsigned char b_bruto;
    struct{
        unsigned char erro : 1;
        unsigned char modo : 3;
        unsigned char leitura : 4;
    }info;
};

void leitura_sinal(unsigned int sinal){
    union byte valor;
    // o struct já é atualizado por causa do union
    valor.b_bruto = sinal;

    printf("Byte bruto: %d | Erro: %d | Modo: %d | Leitura: %d\n", valor.b_bruto, valor.info.erro, valor.info.modo, valor.info.leitura);
}

int main(){
    int sinal;
    scanf("%d", &sinal);

    leitura_sinal((unsigned int)sinal);

    return 0;
}