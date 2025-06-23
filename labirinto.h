#ifndef LABIRINTO_H
#define LABIRINTO_H

#define ALTURA 6
#define LARGURA 10

typedef struct labirinto Labirinto;
typedef struct individuo Individuo;
typedef struct populacao Populacao;

// Labirinto
Labirinto *criar_labirinto(const char *arquivo);
void imprimir_labirinto(Labirinto *lab);
void liberar_labirinto(Labirinto *lab);
int verificar_parede(Labirinto *lab, int x, int y);

// População e individuos
Populacao *criar_populacao();
void inicializar_populacao(Populacao *pop, Labirinto *lab, int tam_pop, int max_tam, const char *tipo);
void avaliar_populacao(Populacao *pop, Labirinto *lab, int penalidade);
void selecionar_melhores(Populacao *pop);
void adicionar_individuo(Populacao *pop, Individuo *ind);
int obter_tamanho_populacao(const Populacao *pop);
Individuo *melhor_individuo(Populacao *pop);
Individuo *selecionar_pai(Populacao *pop);
Individuo *cruzar(Individuo *pai1, Individuo *pai2);
Individuo *copiar_individuo(const Individuo *origem);
Individuo *obter_individuo_por_posicao(Populacao *pop, int pos);
void mutar(Individuo *ind, float taxa_mutacao);
void liberar_populacao(Populacao *pop);

// Acesso a dados
int obter_fitness(const Individuo *ind);
const char *obter_movimentos(const Individuo *ind);

// Impressão
void imprimir_caminho(const char *movimentos);

#endif
