#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "labirinto.h"

void imprimir_caminho(const char *movimentos);

int main() {
    srand(time(NULL));

    Populacao *pop = criar_populacao();
    inicializar_populacao(pop);

    for (int geracao = 0; geracao < 50; geracao++) {
        avaliar_populacao(pop);

        Individuo *melhor = melhor_individuo(pop);

        printf("Geracao %d\n", geracao);
        printf("Melhor Fitness: %d\n",obter_fitness(melhor));
        printf("Melhor caminho: ");
        imprimir_caminho(obter_movimentos(melhor));

        if (obter_fitness(melhor) >= 1000) {
            printf("Solucao encontrada na geracao %d\n", geracao);
            break;
        }
    }

    liberar_populacao(pop);
    return 0;
}
