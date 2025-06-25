#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "labirinto.h"
#include "config.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <mapa.txt> <config.yml>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    const char *arquivo_mapa = argv[1];
    const char *arquivo_config = argv[2];

    Labirinto *lab = criar_labirinto(arquivo_mapa);
    if (!lab) {
        printf("Erro ao tentar carregar o mapa\n");
        return 1;
    }

    Config *config = ler_config(arquivo_config);
    if (!config) {
        printf("Erro ao tentar carregar a configuracao\n");
        liberar_labirinto(lab);
        return 1;
    }

    printf("Labirinto carregado:\n");
    imprimir_labirinto(lab);

    // Abri o log
    FILE *log = fopen(config->caminho_saida_log, "w");
    if (!log) {
        printf("Erro ao tentar abrir o arquivo de log\n");
        liberar_labirinto(lab);
        liberar_config(config);
        return 1;
    }
    fprintf(log, "Geracao,Fitness,Caminho\n");

    Populacao *pop = criar_populacao();
    inicializar_populacao(pop, lab, config->tamanho_populacao, config->max_tamanho_individuo, config->tipo_geracao);

    for (int geracao = 1; geracao <= config->geracoes; geracao++) {
        avaliar_populacao(pop, lab, config->penalidade_movimento_invalido);
        selecionar_melhores(pop);

        // Elitismo
        int n_elite = (int)(config->taxa_elitismo * config->tamanho_populacao);
        if (n_elite < 1) {
            n_elite = 1;
        }

        Populacao *nova_pop = criar_populacao();

        // Copiar elite
        for (int i = 0; i < n_elite; i++) {
            Individuo *atual = obter_individuo_por_posicao(pop, i);
            if (atual == NULL) 
            break;

            Individuo *copia = copiar_individuo(atual);
            adicionar_individuo(nova_pop, copia);
        }

        // Gerar o restante por cruzamento + mutação
        while (obter_tamanho_populacao(nova_pop) < config->tamanho_populacao) {
            Individuo *pai1 = selecionar_pai(pop);
            Individuo *pai2 = selecionar_pai(pop);

            Individuo *filho = cruzar(pai1, pai2);
            mutar(filho, config->taxa_mutacao);
            adicionar_individuo(nova_pop, filho);
        }

        liberar_populacao(pop);
        pop = nova_pop;

        Individuo *melhor = melhor_individuo(pop);

        printf("\nGeracao %d\n", geracao);
        printf("Melhor fitness: %d\n", obter_fitness(melhor));
        printf("Melhor caminho: ");
        imprimir_caminho(obter_movimentos(melhor));

        fprintf(log, "%d,%d,%s\n", geracao, obter_fitness(melhor), obter_movimentos(melhor));

        if (obter_fitness(melhor) >= 1000) {
            printf("Solucao encontrada na geracao %d\n", geracao);
            break;
        }
    }

    fclose(log);
    liberar_populacao(pop);
    liberar_labirinto(lab);
    liberar_config(config);

    printf("\nExecucao finalizada veja o log em %s\n", config->caminho_saida_log);
}
