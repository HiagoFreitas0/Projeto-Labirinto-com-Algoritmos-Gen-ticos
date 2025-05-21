#ifndef LABIRINTO_H
#define LABIRINTO_H

#define ALTURA 6
#define LARGURA 10
#define GENOME_SIZE 100

typedef struct individuo Individuo;
typedef struct populacao Populacao;

/**
 * Cria e inicializa uma população de indivíduos
 * @return Ponteiro para a população criada
 */
Populacao *criar_populacao();

/**
 * Inicializa a população com indivíduos aleatórios
 * @param pop Ponteiro para a população
 */
void inicializar_populacao(Populacao *pop);

/**
 * Calcula o fitness de um indivíduo com base em seus movimentos
 * @param movimentos Sequência de movimentos do indivíduo
 * @return Fitness calculado
 */
int calcular_fitness(char *movimentos);

/**
 * Avalia o fitness de cada indivíduo da população
 * @param pop Ponteiro para a população
 */
void avaliar_populacao(Populacao *pop);

/**
 * Retorna o melhor indivíduo da população
 * @param pop Ponteiro para a população
 * @return Ponteiro para o melhor indivíduo
 */
Individuo *melhor_individuo(Populacao *pop);

/**
 * Libera a memória alocada para a população e seus indivíduos
 * @param pop Ponteiro para a população
 */
void liberar_populacao(Populacao *pop);

/**
 * Retorna o fitness de um indivíduo
 * @param ind Ponteiro para o indivíduo
 * @return Valor do fitness
 */
int obter_fitness(const Individuo *ind);

/**
 * Retorna a sequência de movimentos de um indivíduo
 * @param ind Ponteiro para o indivíduo
 * @return Ponteiro para a sequência de movimentos
 */
const char* obter_movimentos(const Individuo *ind);

/**
 * Imprime a sequência de movimentos de um indivíduo no formato de lista
 * Exemplo de saída: [D, E, B, C, D]
 * @param movimentos Ponteiro para a string que contém os movimentos (como 'D', 'E', 'B', 'C') terminada por '\0'
 */
void imprimir_caminho(const char *movimentos);

/**
 * Imprime os caminhos de todos os indivíduos da população.
 * @param pop Ponteiro para a população
 */
void imprimir_individuos(Populacao *pop);

#endif
