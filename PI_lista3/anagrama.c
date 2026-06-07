#include <stdio.h>
#include <string.h>
//nessa eu usei bastante o gemini, mas sempre pedia para explicar quando não entendia algo
int main() {
    char frase[101];
    int inicio[50], fim[50];// guando os indices de começo e fim das palavras no vetor frase
    int total_palavras = 0;
    int contagem_pares = 0;

    // Lendo a string
    if (fgets(frase, sizeof(frase), stdin)) {
        frase[strcspn(frase, "\n")] = '\0';
    }

    int n = strlen(frase);
    int termina = 0;//verifica se a palavra começa ou termina

    // localizando as palavras
    for (int i = 0; i <= n; i++) {
        char c = frase[i];
        // Verifica se é letra (A-Z ou a-z) manualmente
        int eh_letra = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');

        if (eh_letra) {
            if (!termina) {
                inicio[total_palavras] = i;
                termina = 1;
            }
        } else {
            if (termina) {
                fim[total_palavras] = i - 1;
                total_palavras++;
                termina = 0;
            }
        }
    }

    if (total_palavras < 2) {//já encerra o código se há menos de uma palavra
        printf("Nao existem anagramas na frase.\n");
        return 0;
    }

    //Comparar as palavras
    for (int i = 0; i < total_palavras; i++) {
        for (int j = i + 1; j < total_palavras; j++) {//loop emaranhado para verificar todas as palavaras sem repeti-las
            
            int tam_i = fim[i] - inicio[i] + 1;
            int tam_j = fim[j] - inicio[j] + 1;

            if (tam_i != tam_j) continue;//se as palavras tiverem quantidade de letras diferentes já não são anagramas

            //listas que marcam as letras do alfabeto que possuem
            int freq_i[26] = {0};
            int freq_j[26] = {0};

            // Contagem da palavra I
            for (int k = inicio[i]; k <= fim[i]; k++) {
                char letra = frase[k];
                // Converte para minúscula manualmente: 'A' (65) vira 'a' (97) somando 32
                if (letra >= 'A' && letra <= 'Z') {
                    letra += 32;// a diferença das letras minusculas para maiusculas é 32
                }
                freq_i[letra - 'a']++;// a subtração é para marcar adequadamente na lista qual letra é. ex: b - a = 1, a-a = 0...
            }

            // Contagem da palavra J
            for (int k = inicio[j]; k <= fim[j]; k++) {
                char letra = frase[k];
                if (letra >= 'A' && letra <= 'Z') {
                    letra = letra + 32;
                }
                freq_j[letra - 'a']++;
            }

            int eh_anagrama = 1;
            for (int k = 0; k < 26; k++) {
                if (freq_i[k] != freq_j[k]) {//verifica se possuem exatamente as mesmas as letras independente da ordem
                    eh_anagrama = 0;
                    break;
                }
            }

            if (eh_anagrama) {
                if (contagem_pares == 0) {
                    printf("Pares de anagramas encontrados:\n");
                }
                // Imprime palavra I
                for(int k = inicio[i]; k <= fim[i]; k++) printf("%c", frase[k]);
                printf(" e ");
                // Imprime palavra J
                for(int k = inicio[j]; k <= fim[j]; k++) printf("%c", frase[k]);
                printf("\n");
                
                contagem_pares++;
            }
        }
    }

    if (contagem_pares > 0) {
        printf("\nTotal de pares: %d\n", contagem_pares);
    } else {
        printf("Nao existem anagramas na frase.\n");
    }

    return 0;
}