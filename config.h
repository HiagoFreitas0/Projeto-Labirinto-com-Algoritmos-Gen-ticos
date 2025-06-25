#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    float taxa_elitismo;
    float taxa_mutacao;
    int tamanho_populacao;
    int geracoes;
    int max_tamanho_individuo;
    int penalidade_movimento_invalido;
    char tipo_geracao[50];
    char caminho_saida_log[200];
} Config;

/**
 * Lê um arquivo de configuração
 * @param caminho Caminho para o arquivo de configuração
 * @return Ponteiro para a estrutura Config carregada
 */
Config* ler_config(const char *caminho);

/**
 * Libera a memoria da configuração
 */
void liberar_config(Config *config);

#endif