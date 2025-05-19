#ifndef LABIRINTO_H
#define LABIRINTO_H

#define ALTURA 6
#define LARGURA 10
#define GENOME_SIZE 100

typedef struct individuo Individuo;
typedef struct populacao Populacao;

/**
 * Cria e inicializa uma população de indivíduos.
 * @return Ponteiro para a população criada.
 */
Populacao *criar_populacao();

/**
 * Inicializa a população com indivíduos aleatórios.
 * @param pop Ponteiro para a população.
 */
void inicializar_populacao(Populacao *pop);

/**
 * Avalia o fitness de cada indivíduo da população.
 * @param pop Ponteiro para a população.
 */
void avaliar_populacao(Populacao *pop);

/**
 * Calcula o fitness de um indivíduo com base em seus movimentos.
 * @param movimentos Sequência de movimentos do indivíduo.
 * @return Fitness calculado.
 */
int calcular_fitness(char *movimentos);

/**
 * Retorna o melhor indivíduo da população.
 * @param pop Ponteiro para a população.
 * @return Ponteiro para o melhor indivíduo.
 */
Individuo *melhor_individuo(Populacao *pop);

/**
 * Libera a memória alocada para a população e seus indivíduos.
 * @param pop Ponteiro para a população.
 */
void liberar_populacao(Populacao *pop);

/**
 * Retorna o fitness de um indivíduo.
 * @param ind Ponteiro para o indivíduo.
 * @return Valor do fitness.
 */
int obter_fitness(const Individuo *ind);

/**
 * Retorna a sequência de movimentos de um indivíduo.
 * @param ind Ponteiro para o indivíduo.
 * @return Ponteiro para a sequência de movimentos.
 */
const char* obter_movimentos(const Individuo *ind);

#endif
