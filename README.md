
# 🧠 Projeto: Resolução de Labirintos com Algoritmos Genéticos

Este projeto tem como objetivo utilizar algoritmos genéticos para encontrar soluções de caminhos em labirintos, como parte da disciplina de Estrutura de Dados I (ED-I).

---

## 🚀 Como Executar

### ✔️ Compilar:

Execute no terminal:

```bash
make
```

Ou manualmente:

```bash
gcc main.c labirinto.c config.c -o labirinto
```

---

### ▶️ Rodar o programa:

```bash
./labirinto <caminho_do_mapa.txt> <caminho_do_config.yml>
```

### Exemplo:

```bash
./labirinto mapas/mapa01.txt configs/config1.yml
```

---

## 🗺️ Arquivos de Entrada

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

#### 🔧 Exemplo de configuração:

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

## 🗂️ Saídas do Programa

### 📄 Log CSV:

O programa gera um log no formato CSV com os seguintes dados:

| Geracao | Fitness | Caminho         |
|---------|---------|-----------------|
| 1       | 410     | DDEBEDBDCB...   |
| 2       | 540     | BEDDDCCB...     |
| ...     | ...     | ...             |

---

### 📊 Gráficos:

Você pode abrir o CSV no Excel, Google Planilhas ou Python e gerar gráficos de evolução do fitness.

**Eixo X:** Geração  
**Eixo Y:** Fitness do melhor indivíduo

---

## 🔧 Requisitos

- Compilador `gcc` ou equivalente.
- (Opcional) `make` para usar o Makefile.

---

## 🏗️ Estrutura do Projeto

```
.
├── configs/           → Arquivos de configuração (.yml)
├── mapas/             → Arquivos dos mapas (.txt)
├── logs/              → Logs gerados em CSV
├── graficos/          → Gráficos gerados (PNG, Excel, etc.)
├── main.c             → Código principal
├── labirinto.c/.h     → TAD Labirinto, População e Indivíduo
├── config.c/.h        → Leitura do arquivo de configuração
├── Makefile           → Automatiza compilação e limpeza
└── README.md          → Documentação
```

---

## ✍️ Autores

- 💻 **Seu Nome Aqui**
- 📅 Junho de 2025
- 📚 Disciplina: Estrutura de Dados I (ED-I)

---

## ✅ Status do Projeto

✔️ Funcional  
✔️ Atende todos os requisitos  
✔️ Pronto para entrega e apresentação

---

## 📜 Licença

Uso acadêmico.
