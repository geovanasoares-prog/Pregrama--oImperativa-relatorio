#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_SPECIES_LEN 50

// Estrutura para armazenar os dados de uma linha do dataset Iris
typedef struct {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char species[MAX_SPECIES_LEN];
} IrisRecord;

// Estrutura auxiliar para contagem de espécies (Moda)
typedef struct {
    char name[MAX_SPECIES_LEN];
    int count;
} SpeciesCount;

// Função auxiliar para atualizar a contagem de espécies para a Moda
void update_species_count(SpeciesCount **counts, int *unique_types, const char *species) {
    for (int i = 0; i < *unique_types; i++) {
        if (strcmp((*counts)[i].name, species) == 0) {
            (*counts)[i].count++;
            return;
        }
    }
    
    // Se for uma espécie nova, expande o array auxiliar
    *counts = realloc(*counts, (*unique_types + 1) * sizeof(SpeciesCount));
    strcpy((*counts)[*unique_types].name, species);
    (*counts)[*unique_types].count = 1;
    (*unique_types)++;
}

// Função para processar um arquivo individual
void process_file(const char *filename) {
    // Abre o arquivo para leitura e escrita ("r+")
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        exit(1);
    }

    char line[MAX_LINE];
    char header[MAX_LINE];
    
    // Ler e salvar o cabeçalho
    if (!fgets(header, sizeof(header), file)) {
        fclose(file);
        exit(1);
    }

    IrisRecord *records = NULL;
    int record_count = 0;

    // Loop de leitura do arquivo
    while (fgets(line, sizeof(line), file)) {
        // Realoca memória dinamicamente para cada nova linha
        IrisRecord *temp = realloc(records, (record_count + 1) * sizeof(IrisRecord));
        if (temp == NULL) {
            free(records);
            fclose(file);
            exit(1);
        }
        records = temp;

        // Remove a quebra de linha se houver
        line[strcspn(line, "\r\n")] = 0; 
        
        int parsed = sscanf(line, "%lf,%lf,%lf,%lf,%[^,]", 
                            &records[record_count].sepal_length,
                            &records[record_count].sepal_width,
                            &records[record_count].petal_length,
                            &records[record_count].petal_width,
                            records[record_count].species);

        if (parsed == 5) {
            record_count++;
        }
    }

    if (record_count == 0) {
        free(records);
        fclose(file);
        return;
    }

    // --- CÁLCULOS ESTATÍSTICOS ---
    double sum_sl = 0, sum_sw = 0, sum_pl = 0, sum_pw = 0;
    SpeciesCount *species_counts = NULL;
    int unique_species_count = 0;

    for (int i = 0; i < record_count; i++) {
        sum_sl += records[i].sepal_length;
        sum_sw += records[i].sepal_width;
        sum_pl += records[i].petal_length;
        sum_pw += records[i].petal_width;

        update_species_count(&species_counts, &unique_species_count, records[i].species);
    }

    // Determinar a Moda (Espécie predominante) com critério lexicográfico em caso de empate
    SpeciesCount mode_species = species_counts[0];
    for (int i = 1; i < unique_species_count; i++) {
        if (species_counts[i].count > mode_species.count) {
            mode_species = species_counts[i];
        } else if (species_counts[i].count == mode_species.count) {
            // Em caso de empate, escolhe a menor ordem lexicográfica
            if (strcmp(species_counts[i].name, mode_species.name) < 0) {
                mode_species = species_counts[i];
            }
        }
    }

    printf("%s\n", filename);
    for (int i = 0; i < record_count; i++) {
        printf("%.1f,%.1f,%.1f,%.1f,%s\n", 
               records[i].sepal_length, records[i].sepal_width,
               records[i].petal_length, records[i].petal_width, 
               records[i].species);
    }
    // Move o ponteiro do arquivo para o final para anexar os resultados
    fseek(file, 0, SEEK_END);
    
    fprintf(file, "%.3f\n", sum_sl / record_count);
    fprintf(file, "%.3f\n", sum_sw / record_count);
    fprintf(file, "%.3f\n", sum_pl / record_count);
    fprintf(file, "%.3f\n", sum_pw / record_count);
    fprintf(file, "%s\n", mode_species.name);

    // Liberar memórias alocadas e fechar arquivo
    free(records);
    free(species_counts);
    fclose(file);    
}

int main() {
    int num_files;

    printf("Digite a quantidade total de arquivos a processar: ");
    if (scanf("%d", &num_files) != 1 || num_files <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    // Processa os arquivos sequencialmente baseado no padrão irisX.csv
    for (int i = 1; i <= num_files; i++) {
        char filename[30];
        sprintf(filename, "iris%d.csv", i);
        process_file(filename);
    }

    printf("Processamento concluido para todos os arquivos.\n");
    return 0;
}