#include <stdio.h>
#include <math.h>
int main() {
    int d_a, m_a, a_a, d_h, m_h, a_h;
    scanf("%d/%d/%d %d/%d/%d", &d_a, &m_a, &a_a, &d_h, &m_h, &a_h);
    int soma_amor;
    soma_amor = d_a + m_a + a_a + d_h + m_h + a_h;
    int amor;
    amor = ((soma_amor) * 7) % 101;
    printf("Amor: %d%% ", amor);

    if (amor < 20){
        puts("Pessimo dia para se apaixonar.");
    }else if (amor >= 20 && amor <= 40){
        puts("Melhor manter o coracao <3 longe de perigo.");
    }else if (amor >= 41 && amor <= 69){
        puts("Se o papo e as ideias baterem, esta liberado pensar em algo.");
    }else if (amor >= 70 && amor <= 80){
        puts("Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.");
    }else{
        puts("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.");
    }

    int sorte;
    sorte = (((d_a + d_h + m_a + m_h) * 9) + (a_h - a_a)) % 101;
    printf("Sorte: %d%% ", sorte);

    if (sorte < 30){
        printf("Nem jogue moedas pra cima hoje.");
    }else if (sorte >= 30 && sorte <= 50){
        printf("Melhor nao arriscar.");
    }else if (sorte >= 51 && sorte <= 79){
        printf("Por sua conta em risco.");
    }else if (sorte >= 80 && sorte <= 90){
        printf("Hoje vale a pena arriscar.");
    }else{
        printf("Nao tenha medo de virar cartas hoje.");
    }
    puts( " Sem tigrinho nem jogos de azar, por favor!");

    int trabalho;
    trabalho = ((a_a + a_h) - (d_a + d_h + m_a + m_h) * 8) % 101;
    printf("Trabalho: %d%% ", trabalho);

    if (trabalho < 40){
        puts("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.");
    }else if (trabalho >= 40 && trabalho <= 50){
        puts("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.");
    }else if (trabalho >= 51 && trabalho <= 69){
        puts("Um dia proveitoso com certeza, leve sua simpatia consigo.");
    }else if (trabalho >= 70 && trabalho <= 84){
        puts("Boas vibracoes hoje, chances podem estar ao seu redor.");
    }else{
        puts("Use do maximo de networking possível hoje, dia bom para negocios.");
    }
    
    int cor;
    cor = ((d_a * d_a) + (d_h * d_h) + (m_a * m_a) + (m_h * m_h) + (a_a * a_a) + (a_h * a_h)) % 11;
    printf("Cor: ");
    if (cor == 0){
        puts("Cinza.");
    }else if (cor == 1){
        puts("Vermelho.");
    }else if (cor == 2){
        puts("Laranja.");
    }else if (cor == 3){
        puts("Amarelo.");
    }else if (cor == 4){
        puts("Verde.");
    }else if (cor == 5){
        puts("Azul.");
    }else if (cor == 6){
        puts("Roxo.");
    }else if (cor == 7){
        puts("Marrom.");
    }else if (cor == 8){
        puts("Rosa.");
    }else if (cor == 9){
        puts("Preto.");
    }else{
        puts("Branco.");
    }
    return 0;
}