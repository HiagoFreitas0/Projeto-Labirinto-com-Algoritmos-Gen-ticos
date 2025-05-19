# Projeto-Labirinto-com-Algoritmos-Gen-ticos
🌐 Labirinto com Algoritmos Genéticos

📌 Descrição

Este projeto implementa um algoritmo genético para encontrar o melhor caminho em um labirinto. Cada indivíduo da população representa um caminho (sequência de movimentos) e evolui ao longo das gerações
##

🚀 Como Funciona

🗺️ Modelo do Mapa: O labirinto é representado como uma matriz de caracteres

🧬 População Inicial: Cada indivíduo tem uma sequência aleatória de movimentos com tamanho dinâmico

📍 Simulação de Caminhos: Os movimentos são aplicados a partir da posição inicial (S)

🎯 Cálculo de Fitness: Com base na distância até a saída (E) e penalizações por colisão
##

📂 Estrutura do Projeto

| labirinto.h | labirinto.c | main.c |
|-------------|-------------|--------|
|Cabeçalho do TAD| Implementação das funções| Função principal (execução)|

##

 Exemplo de Saída

 Geração 0 - Melhor Fitness: 820
Melhor caminho: [D, D, B, B, D, E, E, B, C]

Geração 50 - Melhor Fitness: 999
Melhor caminho: [D, D, D, B, B, B, B, D, D]
##
