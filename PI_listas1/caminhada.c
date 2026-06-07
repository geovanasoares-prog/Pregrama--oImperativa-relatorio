#include <stdio.h>

int main(){
    int x, y, qua;
    scanf("%d %d %d", &x, &y, &qua);

    //verifica onde mario esta e conclui o x e y que ele vai
    int x_des, y_des;
    if (x > 0 && y > 0){
        x_des = -1;
        y_des = -1;
    }else if (x < 0 && y > 0){
        x_des = 1;
        y_des = -1;
    }else if (x > 0 && y < 0){
        x_des = -1;
        y_des = 1;
    }else if (x < 0 && y < 0){
        x_des = 1;
        y_des = 1;
    }else{
        puts("caminhada invalida/n");
    }
    //calculo da distancia em x e y
    int passos_x = abs(x_des - x);
    int passos_y = abs(y_des - y);

    // verifica por qual quadrante passa movendo em y primeiro
    int y_primeiro;
    if (x > 0 && y_des > 0) y_primeiro = 1;
    else if (x < 0 && y_des > 0) y_primeiro = 2;
    else if (x < 0 && y_des < 0) y_primeiro = 3;
    else y_primeiro = 4;

    int x_primeiro;
    if (x_des > 0 && y > 0) x_primeiro = 1;
    else if (x_des < 0 && y > 0) x_primeiro = 2;
    else if (x_des < 0 && y < 0) x_primeiro = 3;
    else x_primeiro = 4;

    // Verificação de qual caminho seguir
    if (y_primeiro != qua) {
        printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
    } else if (x_primeiro != qua) {
        printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
    } else {
        puts("caminhada invalida\n");
    }
    return 0;
}