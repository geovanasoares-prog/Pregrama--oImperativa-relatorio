#include <stdio.h>

int main(){
    long long n;
    scanf("%lld", &n);
    long long a, b;
    scanf("%lld %lld", &a, &b);

    //soma de 1 ate n
    long long soma_n;
    soma_n = (n * (1 + n)) / 2;

    // soma de multiplos de a
    long long qnt_a;
    qnt_a = n / a;
    long long ultimo_a;
    ultimo_a = qnt_a * a;
    long long soma_a;
    soma_a = ((a + ultimo_a) * qnt_a) / 2;

    // somo dos multiplos de b
    long long qnt_b;
    qnt_b = n / b;
    long long ultimo_b;
    ultimo_b = qnt_b * b;
    long long soma_b;
    soma_b = ((b + ultimo_b) * qnt_b) / 2;

    // intersecção de a e b 
    long long mult_ab;
    mult_ab = a * b;
    long long soma_ab = 0;
    if (mult_ab <= n){
        long long qnt_ab;
        qnt_ab = n / mult_ab;
        long long ultimo_ab;
        ultimo_ab = qnt_ab * mult_ab;
        soma_ab = ((ultimo_ab + mult_ab) * qnt_ab) / 2;
    }
    long long resultado = soma_n - (soma_a + soma_b) + soma_ab;

    printf("%lld\n", resultado);

    if (resultado % 2 == 0){
        puts("Lá ele!!!");
    }else{
        puts("Opa xupenio AULAS...");
    }
    return 0;
}