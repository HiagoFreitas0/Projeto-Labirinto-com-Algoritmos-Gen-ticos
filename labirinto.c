#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct labirinto {
    char mapa[ALTURA][LARGURA];
    int x_inicio, y_inicio, x_saida, y_saida;
};

struct individuo {
    char movimentos[300];//caminho
    int fitness;
    Individuo *prox;
};

struct populacao {
    Individuo *inicio;
    int tamanho;
};
//função nova 
Labirinto *criar_labirinto(const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("Erro ao tentar abrir mapa\n");
        return NULL;
    }
    Labirinto *lab = malloc(sizeof(Labirinto));

    char linha[LARGURA + 2];
    for (int i = 0; i < ALTURA; i++) {
        fgets(linha, sizeof(linha), f);
        for (int j = 0; j < LARGURA; j++) {
            lab->mapa[i][j] = linha[j];
            if (linha[j] == 'E') {
                lab->x_inicio = j;
                lab->y_inicio = i;
            }
            if (linha[j] == 'S') {
                lab->x_saida = j;
                lab->y_saida = i;
            }
        }
    }
    fclose(f);
    return lab;
}

void imprimir_labirinto(Labirinto *lab) {
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            printf("%c", lab->mapa[i][j]);
        }
        printf("\n");
    }
}

void liberar_labirinto(Labirinto *lab) {
    free(lab);
}
//função nova
int verificar_parede(Labirinto *lab, int x, int y) {
    if (x < 0 || x >= LARGURA || y < 0 || y >= ALTURA)
        return 1;
    return (lab->mapa[y][x] == '#');
}

// População e individuos
Populacao *criar_populacao() {
    Populacao *pop = malloc(sizeof(Populacao));
    pop->inicio = NULL;
    pop->tamanho = 0;
    return pop;
}
//função nova
void adicionar_individuo(Populacao *pop, Individuo *ind) {
    ind->prox = pop->inicio;
    pop->inicio = ind;
    pop->tamanho++;
}

int obter_tamanho_populacao(const Populacao *pop) {
    return pop->tamanho;
}

void inicializar_populacao(Populacao *pop, Labirinto *lab, int tam_pop, int max_tam, const char *tipo) {
    for (int i = 0; i < tam_pop; i++) {
        Individuo *novo = malloc(sizeof(Individuo));
        int tamanho = 10 + rand() % (max_tam - 10 + 1);

        int x = lab->x_inicio;
        int y = lab->y_inicio;

        for (int j = 0; j < tamanho; j++) {
            char mov;
            if (strcmp(tipo, "apenas_movimentos_validos") == 0) {
                char movimentos_possiveis[4];
                int cont = 0;
                if (!verificar_parede(lab, x, y - 1)) movimentos_possiveis[cont++] = 'C';
                if (!verificar_parede(lab, x, y + 1)) movimentos_possiveis[cont++] = 'B';
                if (!verificar_parede(lab, x - 1, y)) movimentos_possiveis[cont++] = 'E';
                if (!verificar_parede(lab, x + 1, y)) movimentos_possiveis[cont++] = 'D';

                if (cont > 0) {
                    mov = movimentos_possiveis[rand() % cont];
                } else {
                    mov = "CBED"[rand() % 4];
                }
            } else {
                mov = "CBED"[rand() % 4];
            }
            novo->movimentos[j] = mov;

            switch (mov) {
                case 'C': y--;
                break;
                case 'B': y++;
                break;
                case 'E': x--;
                break;
                case 'D': x++;
                break;
            }
        }
        novo->movimentos[tamanho] = '\0';
        novo->fitness = 0;
        adicionar_individuo(pop, novo);
    }
}

int calcular_fitness(Labirinto *lab, const char *mov, int penalidade) {
    int x = lab->x_inicio;
    int y = lab->y_inicio;

    int penal = 0;
    for (int i = 0; mov[i] != '\0'; i++) {
        int nx = x, ny = y;
        switch (mov[i]) {
            case 'C': ny--;
            break;
            case 'B': ny++;
            break;
            case 'E': nx--;
            break;
            case 'D': nx++;
            break;
        }
        if (verificar_parede(lab, nx, ny)) {
            if (penalidade) 
            penal++;
            continue;
        } else {
            x = nx;
            y = ny;
        }
    }
    double dx = lab->x_saida - x;
    double dy = lab->y_saida - y;
    double distancia = sqrt(dx * dx + dy * dy);//√(dx² + dy²)

    int fit = (int)(1000 - distancia * 10 - penal * 20);
    if (fit < 0) 
      fit = 0;
    return fit;
}

void avaliar_populacao(Populacao *pop, Labirinto *lab, int penalidade) {
    Individuo *atual = pop->inicio;
    while (atual) {
        atual->fitness = calcular_fitness(lab, atual->movimentos, penalidade);
        atual = atual->prox;
    }
}
//função nova
void selecionar_melhores(Populacao *pop) {
    Individuo **vet = malloc(pop->tamanho * sizeof(Individuo *));
    Individuo *atual = pop->inicio;
    int i = 0;//preencher o vetor
    while (atual) {
        vet[i++] = atual;
        atual = atual->prox;
    }
    for (int i = 0; i < pop->tamanho - 1; i++) {
        for (int j = i + 1; j < pop->tamanho; j++) {
            if (vet[j]->fitness > vet[i]->fitness) {
                Individuo *tmp = vet[i];
                vet[i] = vet[j];
                vet[j] = tmp;
            }
        }
    }
    int novos = pop->tamanho / 2;
    for (int i = novos; i < pop->tamanho; i++) {
        free(vet[i]);
    }
    pop->inicio = NULL;
    for (int i = 0; i < novos; i++) {
        vet[i]->prox = pop->inicio;
        pop->inicio = vet[i];
    }
    pop->tamanho = novos;
    free(vet);
}

Individuo *melhor_individuo(Populacao *pop) {
    Individuo *melhor = pop->inicio;
    Individuo *atual = pop->inicio;
    while (atual) {
        if (atual->fitness > melhor->fitness)
            melhor = atual;
        atual = atual->prox;
    }
    return melhor;
}
//função nova (roleta usada)
Individuo *selecionar_pai(Populacao *pop) {
    int soma = 0;
    Individuo *atual = pop->inicio;

    while (atual) {
        soma += atual->fitness;
        atual = atual->prox;
    }

    if (soma == 0) {
        int idx = rand() % pop->tamanho;
        atual = pop->inicio;
        for (int i = 0; i < idx; i++) 
        atual = atual->prox;
        return atual;
    }

    int r = rand() % soma;
    int acum = 0;
    atual = pop->inicio;
    
    while (atual) {
        acum += atual->fitness;
        if (acum > r)
            return atual;
        atual = atual->prox;
    }
    return pop->inicio;
}
//função nova
Individuo *cruzar(Individuo *pai1, Individuo *pai2) {
    Individuo *filho = malloc(sizeof(Individuo));
    int tam1 = strlen(pai1->movimentos);
    int tam2 = strlen(pai2->movimentos);
    int menor = tam1 < tam2 ? tam1 : tam2;
    int corte = menor / 2;

    strncpy(filho->movimentos, pai1->movimentos, corte);
    strcpy(filho->movimentos + corte, pai2->movimentos + corte);

    filho->fitness = 0;
    filho->prox = NULL;
    return filho;
}
//função nova
Individuo *copiar_individuo(const Individuo *origem) {
    Individuo *novo = malloc(sizeof(Individuo));
    strcpy(novo->movimentos, origem->movimentos);
    novo->fitness = origem->fitness;
    novo->prox = NULL;
    return novo;
}
//função nova
Individuo *obter_individuo_por_posicao(Populacao *pop, int pos) {
    Individuo *atual = pop->inicio;
    int i = 0;
    while (atual != NULL) {
        if (i == pos) {
            return atual;
        }
        atual = atual->prox;
        i++;
    }
    return NULL;
}
//função nova
void mutar(Individuo *ind, float taxa_mutacao) {
    int tam = strlen(ind->movimentos);
    for (int i = 0; i < tam; i++) {
        if ((rand() / (float)RAND_MAX) < taxa_mutacao) {
            ind->movimentos[i] = "CBED"[rand() % 4];
        }
    }
}

void liberar_populacao(Populacao *pop) {
    Individuo *atual = pop->inicio;
    while (atual) {
        Individuo *tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
    free(pop);
}

int obter_fitness(const Individuo *ind) {
    return ind->fitness;
}

const char *obter_movimentos(const Individuo *ind) {
    return ind->movimentos;
}

void imprimir_caminho(const char *mov) {
    printf("[");
    for (int i = 0; mov[i] != '\0'; i++) {
        printf("%c", mov[i]);
        if (mov[i + 1] != '\0') printf(", ");
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
