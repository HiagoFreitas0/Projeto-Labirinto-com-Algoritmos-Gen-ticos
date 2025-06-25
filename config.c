#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Config* ler_config(const char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        printf("Erro ao tentar abrir o arquivo de configuracao passado\n");
        return NULL;
    }

    Config *config = (Config*)malloc(sizeof(Config));

    // Valores padrão (caso não estejam no arquivo)
    config->taxa_elitismo = 0.1;
    config->taxa_mutacao = 0.05;
    config->tamanho_populacao = 100;
    config->geracoes = 200;
    config->max_tamanho_individuo = 300;
    config->penalidade_movimento_invalido = 1;
    strcpy(config->tipo_geracao, "aleatorio");
    strcpy(config->caminho_saida_log, "logs/log.csv");

    char linha[256];
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Ignora comentarios e linhas vazias
        if (linha[0] == '#' || linha[0] == '\n')
            continue;

        char chave[100], valor[100];
        if (sscanf(linha, "%[^:]: %s", chave, valor) == 2) {
            if (strcmp(chave, "taxa_elitismo") == 0)
                config->taxa_elitismo = atof(valor);
            else if (strcmp(chave, "taxa_mutacao") == 0)
                config->taxa_mutacao = atof(valor);
            else if (strcmp(chave, "tamanho_populacao") == 0)
                config->tamanho_populacao = atoi(valor);
            else if (strcmp(chave, "geracoes") == 0)
                config->geracoes = atoi(valor);
            else if (strcmp(chave, "max_tamanho_individuo") == 0)
                config->max_tamanho_individuo = atoi(valor);
            else if (strcmp(chave, "penalidade_movimento_invalido") == 0)
                config->penalidade_movimento_invalido = (strcmp(valor, "true") == 0) ? 1 : 0;
            else if (strcmp(chave, "tipo_geracao") == 0)
                strcpy(config->tipo_geracao, valor);
            else if (strcmp(chave, "saida_log") == 0)
                strcpy(config->caminho_saida_log, valor);
        }
    }
    fclose(arquivo);
    return config;
}

void liberar_config(Config *config) {
    free(config);
}
