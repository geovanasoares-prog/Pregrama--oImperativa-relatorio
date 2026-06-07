#include <stdio.h>
#include <string.h>
// esse eu tive um pouco de dificuldade para entender a luz gigante então usei o gemini
int main() {
    char luzGigante[100000] = ""; // String para acumular o resultado final
    int tamanhoGigante = 0;
    int R; // Número de casos de teste
    
    // Lendo a quantidade de casos
    scanf("%d", &R);

    //loop dos casos testes
    for (int r = 0; r < R; r++) {
        char S[61];
        long long F; // Usamos long long porque o número de flashes pode ser grande
        
        scanf("%s %lld", &S, &F);
        int n = strlen(S);
        
        //loop das trocas nos leds
        for (long long f = 0; f < F; f++) {
            // O primeiro LED sempre troca de estado
            int i = 0;
            int deve_trocar = 1;
            
            //loop para continuar trocqndo enquanto as leds devem trocar ou acabarem as leds
            while (deve_trocar && i < n) {
                char estadoAntigo = S[i];
                
                // Troca o estado atual
                if (S[i] == 'X') S[i] = 'O';
                else{
                    S[i] = 'X';
                }
                
                // verifica de o led foi desligadp
                if (estadoAntigo == 'O' && S[i] == 'X') {
                    deve_trocar = 1;
                    i++;//passa para o próximo led a mudança
                } else {
                    deve_trocar = 0;
                }
            }
        }
        
        //Imprimi o estado final do fio atual
        printf("%s\n", S);
        
        //Construir a Luz Gigante
        if (r > 0) { // precisa ter passado do 1 caso
            char ultimoLuzGigante = luzGigante[tamanhoGigante - 1];//retira o \0
            char primeiroNovoFio = S[0];
            char ornamento;

            if (tamanhoGigante % 2 == 0) { // Tamanho Par
                if (ultimoLuzGigante == primeiroNovoFio) ornamento = '@';
                else ornamento = '$';
            } else { // Tamanho Ímpar
                if (ultimoLuzGigante == primeiroNovoFio) ornamento = '#';
                else ornamento = '%';
            }
            
            // Adiciona o ornamento na string gigante
            luzGigante[tamanhoGigante] = ornamento;
            tamanhoGigante++;
            luzGigante[tamanhoGigante] = '\0';
        }

        // Anexa o fio atual na luz gigante
        for (int k = 0; S[k] != '\0'; k++) {
            luzGigante[tamanhoGigante] = S[k];
            tamanhoGigante++;
        }
        luzGigante[tamanhoGigante] = '\0';
    }

    // --- PASSO 4: Imprimir a Luz Gigante final ---
    printf("%s\n", luzGigante);

    return 0;
}