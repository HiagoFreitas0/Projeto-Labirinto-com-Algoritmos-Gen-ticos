#  Projeto: Resolução de Labirintos com Algoritmos Genéticos

Este projeto tem como objetivo utilizar algoritmos genéticos para encontrar soluções de caminhos em labirintos

---

##  Como Executar

###  Compilar:

Execute no terminal:

```bash
gcc main.c labirinto.c config.c -o labirinto
```

---

### Rodar o programa:

```bash
./labirinto <caminho_do_mapa.txt> <caminho_do_config.yml>
```

### Exemplo:

```bash
.\labirinto.exe mapas\mapa.txt configs\config.yml
```

---

##  Arquivos de Entrada

###  Mapa (`mapa.txt`):
- Representa o labirinto
- **Símbolos:**
  - `E` → Entrada
  - `S` → Saída
  - `#` → Parede
  - (espaço) → Caminho livre

---

###  Configuração (`config.yml`):
Arquivo YAML que define os parâmetros do algoritmo

####  Exemplo de configuração:

```yaml
taxa_elitismo: 0.1
taxa_mutacao: 0.05
tamanho_populacao: 100
geracoes: 200
tipo_geracao: aleatorio  # ou apenas_movimentos_valido
max_tamanho_individuo: 300
penalidade_movimento_invalido: true
saida_log: logs/experimento1.csv
```

---

##  Saídas do Programa

###  Log CSV:

O programa gera um log no formato CSV com os seguintes dados:

| Geracao | Fitness | Caminho         |
|---------|---------|-----------------|
| 1       | 410     | DDEBEDBDCB...   |
| 2       | 540     | BEDDDCCB...     |
| ...     | ...     | ...             |

---

###  Gráficos:

Você pode abrir o CSV no Excel ou Google Planilhas e gerar gráficos de evolução do fitness

**Eixo X:** Geração  
**Eixo Y:** Fitness do melhor indivíduo

---

##  Estrutura do Projeto

```
configs/           - Arquivos de configuração (.yml)
mapas/             - Arquivos dos mapas (.txt)
logs/              - Logs gerados em CSV
main.c             - Código principal
labirinto.c/.h     - TAD Labirinto, População e Indivíduo
config.c/.h        - Leitura do arquivo de configuração
README.md          - Documentação
```

---

##  Análise dos Resultados

Foram executados dois experimentos, cada um com um arquivo de configuração diferente, para comparar o comportamento do algoritmo com diferentes parâmetros

---

###  Experimento 1 — Exploração Alta (Aleatório)

```yaml
taxa_elitismo: 0.1
taxa_mutacao: 0.2
tamanho_populacao: 50
geracoes: 100
tipo_geracao: aleatorio
max_tamanho_individuo: 200
penalidade_movimento_invalido: true
saida_log: logs/experimento1.csv
```
### 📈 Evolução do Fitness — Experimento 1

![Imagem1](https://github.com/user-attachments/assets/4d2b25c0-4c19-4231-ba85-4da246d7c8b5)

---

---
##  Experimento 2 — Conservador (Apenas Movimentos Válidos)

```yaml
taxa_elitismo: 0.4
taxa_mutacao: 0.02
tamanho_populacao: 100
geracoes: 100
tipo_geracao: apenas_movimentos_validos
max_tamanho_individuo: 200
penalidade_movimento_invalido: true
saida_log: logs/experimento2.csv
```
###  Evolução do Fitness — Experimento 2

![Imagem2](https://github.com/user-attachments/assets/71b8b664-d192-46d6-840c-3c5f8b6fe0bd)

---

##  Autor

-  Hiago Freitas Jatobá
-  Junho de 2025
-  Disciplina: Estrutura de Dados 1

---
