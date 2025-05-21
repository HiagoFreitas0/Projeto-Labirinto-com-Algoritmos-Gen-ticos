#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char labirinto[ALTURA][LARGURA] = {
    "##########",
    "#S     # #",
    "# ## #   #",
    "# ## ### #",
    "#      #E#",
    "##########"
};

struct individuo {
    char movimentos[GENOME_SIZE];//caminho
    int fitness;
    Individuo *prox;
};

struct populacao {
    Individuo *inicio;
    int tamanho;
};

int distancia_manhattan(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

Populacao* criar_populacao() {
    Populacao *pop = (Populacao *) malloc(sizeof(Populacao));
    pop->inicio = NULL;
    pop->tamanho = 0;
    return pop;
}

void inicializar_populacao(Populacao *pop) {
    int ex = 8, ey = 4; // (saida)
    int tamanho_min = distancia_manhattan(1, 1, ex, ey);
    int tamanho_max = tamanho_min * 2;

    for (int i = 0; i < 100; i++) {
        Individuo *novo = (Individuo *) malloc(sizeof(Individuo));
        int tamanho = tamanho_min + rand() % (tamanho_max - tamanho_min + 1);
        for (int j = 0; j < tamanho; j++) {
            novo->movimentos[j] = "CBED"[rand() % 4];
        }
        novo->movimentos[tamanho] = '\0';
        novo->fitness = 0;
        novo->prox = pop->inicio;
        pop->inicio = novo;
        pop->tamanho++;
    }
}

int calcular_fitness(char *movimentos) {
    int x = 1, y = 1; //(inicial)
    int ex = 8, ey = 4;

    for (int i = 0; movimentos[i] != '\0'; i++) {
        int nx = x, ny = y;

        switch (movimentos[i]) {
            case 'C':
            ny = y - 1; 
            break;
            case 'B':
            ny = y + 1; 
            break;
            case 'E':
            nx = x - 1; 
            break;
            case 'D':
            nx = x + 1; 
            break;
        }

        if(labirinto[ny][nx] == '#'){
            // Colisão (para o caminho)
            break;
        } else {
            x = nx;
            y = ny;
        }
    }

    double dx = ex - x;
    double dy = ey - y;
    double distancia = sqrt(dx * dx + dy * dy);

    int fitness = (int)(1000 - distancia * 10);
    if (fitness < 0) 
    fitness = 0;
    return fitness;
}

void avaliar_populacao(Populacao *pop) {
    Individuo *atual = pop->inicio;
    while (atual) {
        atual->fitness = calcular_fitness(atual->movimentos);
        atual = atual->prox;
    }
}

Individuo *melhor_individuo(Populacao *pop) {
    Individuo *atual = pop->inicio;
    Individuo *melhor = atual;
    while (atual) {
        if (atual->fitness > melhor->fitness)
            melhor = atual;
        atual = atual->prox;
    }
    return melhor;
}

void liberar_populacao(Populacao *pop) {
    Individuo *atual = pop->inicio;
    while (atual) {
        Individuo *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(pop);
}

int obter_fitness(const Individuo *ind) {
    return ind->fitness;
}

const char* obter_movimentos(const Individuo *ind) {
    return ind->movimentos;
}

void imprimir_caminho(const char *movimentos) {
    printf("[");
    for (int i = 0; movimentos[i] != '\0'; i++) {
        printf("%c", movimentos[i]);
        if (movimentos[i + 1] != '\0')
            printf(", ");
    }
    printf("]\n");
}

void imprimir_individuos(Populacao *pop) {
    Individuo *atual = pop->inicio;
    int i = 1;
    while (atual) {
        printf("Individuo %d: ", i++);
        imprimir_caminho(atual->movimentos);
        atual = atual->prox;
    }
}

