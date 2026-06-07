#include <stdio.h>
#include <string.h>

void achar_p(char matriz[122][122], char resultado[122][122], int x, int y);

int main(){
    int x, y;
    char praca[122][122], praca_nova[122][122];
    scanf("%d %d", &x, &y);
    
    for(int i = 0; i < x; i++){
        scanf("%s", &praca[i]);
    }
    //copiar a matriz
    memcpy(praca_nova, praca, sizeof(praca));

    achar_p(praca, praca_nova, x ,y);

    for(int i = 0; i < x; i++){
        printf("%s\n", praca_nova[i]);
    }
    return 0;
}

void achar_p(char matriz[122][122], char resultado[122][122], int x, int y){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if (matriz[i][j] == 'P'){
                //vetores responsaveis por colocar os enfeites +
                int hor[4] = {0, 0, 1, -1};
                int ver[4] = {1, -1, 0, 0};
                
                //loop que coloca os "+"
                for(int m = 0; m < 4; m++){
                    if(i+hor[m] >= 0 && i+hor[m] < x && j+ver[m] >= 0 && j+ver[m] < y && matriz[i+hor[m]][j+ver[m]] != 'P') resultado[i+hor[m]][j+ver[m]] = '+';   
                }
                //vetorrs responsavei por colocar os enfeites x
                int dig_hor[4] = {1, 1, -1, -1};
                int dig_ver[4] = {1, -1, 1, -1};

                //loop que coloca os 'x'
                for(int n = 0; n < 4; n++){
                    if(i+dig_hor[n] >= 0 && i+dig_hor[n] < x && j+dig_ver[n] >= 0 && j+dig_ver[n] < y && resultado[i+dig_hor[n]][j+dig_ver[n]] == '-') resultado[i+dig_hor[n]][j+dig_ver[n]] = 'x';
                }
            }
        }
    }
}