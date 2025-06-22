
# Projeto: Resolução de Labirintos com Algoritmos Genéticos

Este projeto tem como objetivo utilizar algoritmos genéticos para encontrar soluções de caminhos em labirintos, como parte da disciplina de Estrutura de Dados I (ED-I).

---

##  Como Executar

### Compilar:

Execute no terminal:

```bash
make
```

Ou manualmente:

```bash
gcc main.c labirinto.c config.c -o labirinto
```

---

###  Rodar o programa:

```bash
./labirinto <caminho_do_mapa.txt> <caminho_do_config.yml>
```

### Exemplo:

```bash
./labirinto mapas/mapa01.txt configs/config1.yml
```

---

## Arquivos de Entrada

### 🔹 Mapa (`mapa.txt`):
- Representa o labirinto.
- **Símbolos:**
  - `E` → Entrada
  - `S` → Saída
  - `#` → Parede
  - (espaço) → Caminho livre

---

### 🔹 Configuração (`config.yml`):
Arquivo YAML que define os parâmetros do algoritmo.

#### Exemplo de configuração:

```yaml
taxa_elitismo: 0.1
taxa_mutacao: 0.05
tamanho_populacao: 100
geracoes: 200
tipo_geracao: apenas_movimentos_validos  # ou aleatorio
max_tamanho_individuo: 300
penalidade_movimento_invalido: true
saida_log: logs/experimento1.csv
```

---

## Saídas do Programa

### Log CSV:

O programa gera um log no formato CSV com os seguintes dados:

| Geracao | Fitness | Caminho         |
|---------|---------|-----------------|
| 1       | 410     | DDEBEDBDCB...   |
| 2       | 540     | BEDDDCCB...     |
| ...     | ...     | ...             |

---

### Gráficos:

Você pode abrir o CSV no Excel, Google Planilhas ou Python e gerar gráficos de evolução do fitness.

**Eixo X:** Geração  
**Eixo Y:** Fitness do melhor indivíduo

---


## Estrutura do Projeto

```
.
├── configs/           → Arquivos de configuração (.yml)
├── mapas/             → Arquivos dos mapas (.txt)
├── logs/              → Logs gerados em CSV
├── graficos/          → Gráficos gerados (PNG, Excel, etc.)
├── main.c             → Código principal
├── labirinto.c/.h     → TAD Labirinto, População e Indivíduo
└── config.c/.h        → Leitura do arquivo de configuração
```

---

## Autores

- 💻 **Hiago Freitas Jatobá**
- 📅 Junho de 2025
- 📚 Disciplina: Estrutura de Dados I (ED-I)

---

Análise dos Resultados
Foram executados dois experimentos, cada um com um arquivo de configuração diferente, para comparar o comportamento do algoritmo com diferentes parâmetros.

🧪 Experimento 1 — Exploração Alta (Aleatório)
yaml
Copiar
Editar
taxa_elitismo: 0.1
taxa_mutacao: 0.2
tamanho_populacao: 50
geracoes: 100
tipo_geracao: aleatorio
max_tamanho_individuo: 200
penalidade_movimento_invalido: true
saida_log: logs/experimento1.csv
Observações:

Fitness mais instável, com muita oscilação.

Maior diversidade devido à alta taxa de mutação.

Demorou mais para estabilizar um caminho ótimo.

🧪 Experimento 2 — Conservador (Apenas Movimentos Válidos)
yaml
Copiar
Editar
taxa_elitismo: 0.4
taxa_mutacao: 0.02
tamanho_populacao: 100
geracoes: 100
tipo_geracao: apenas_movimentos_validos
max_tamanho_individuo: 200
penalidade_movimento_invalido: true
saida_log: logs/experimento2.csv
Observações:

Fitness sobe de forma estável e consistente.

Menor diversidade, mas maior foco na otimização dos melhores.

Convergência mais rápida, porém com risco de mínimos locais.
