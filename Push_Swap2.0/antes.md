# Push_Swap

> Projeto da 42 School — Ordenação de números utilizando duas stacks e um conjunto limitado de operações.

**Repositório:** https://github.com/pmip2005/Push_Swap
**Branch analisada:** `master`
**Estado da documentação:** Baseline inicial — antes da reestruturação
**Objetivo futuro:** Desenvolver algoritmos capazes de ordenar os elementos utilizando o menor número possível de operações.

---

# 1. Objetivo do projeto

O Push_Swap consiste em ordenar uma sequência de números inteiros utilizando duas stacks, A e B, e um conjunto limitado de operações.

O programa recebe números como argumentos e deve apresentar no standard output a sequência de operações necessária para ordenar a stack A.

A stack A deve terminar ordenada por ordem crescente e a stack B deve ficar vazia.

O desafio não consiste apenas em ordenar corretamente os números.

O principal objetivo de otimização é conseguir a menor quantidade possível de operações.

## Objetivos técnicos

- Implementar e manipular stacks.
- Trabalhar com estruturas de dados.
- Desenvolver algoritmos de ordenação.
- Otimizar operações de rotação.
- Trabalhar com complexidade algorítmica.
- Gerir memória dinâmica.
- Desenvolver testes e ferramentas de benchmarking.
- Comparar diferentes estratégias de ordenação.

---

# 2. Estrutura atual do projeto

A seguinte árvore representa a organização identificada no repositório durante a análise.

```text
Push_Swap/
│
├── main.c
├── PushSwap.h
├── Makefile
│
├── Stack Structure/
│   ├── StackStruct.h
│   ├── StackBehaviours.c
│   ├── StackBehaviours2.c
│   ├── StackChecks.c
│   ├── NodeBehaviours.c
│   └── tests/
│
├── Operations/
│   ├── Operations.h
│   ├── Swap.c
│   ├── Push.c
│   ├── Rotate.c
│   └── ReverseRotate.c
│
├── Parsing/
│   ├── Parsing.h
│   ├── ParseInt.c
│   ├── ParseArguments.c
│   ├── AppendArgument.c
│   ├── AppendToken.c
│   ├── SplitWhitespace.c
│   ├── ft_split.c
│   ├── ft_strlen.c
│   ├── ft_substr.c
│   └── tests/
│
├── Sorting/
│   ├── Sorting.h
│   ├── SortThree.c
│   ├── SortFive.c
│   ├── BringToTop.c
│   ├── ChunkAssignIndices.c
│   ├── ChunkFindTarget.c
│   ├── ChunkPush.c
│   ├── ChunkPullMax.c
│   ├── ChunkSort.c
│   ├── RadixSort.c
│   └── tests/
│
├── tests/
│   └── test_cli.py
│
├── .build/
└── .build-sanitized/
```

**Nota:** A árvore é uma representação da estrutura observada. Os diretórios de compilação contêm artefactos gerados e não devem ser considerados parte da arquitetura funcional.

---

# 3. Arquitetura atual

O projeto está dividido em quatro módulos principais.

| Módulo | Responsabilidade |
|---|---|
| Stack Structure | Implementação das stacks e dos nodes |
| Operations | Operações permitidas pelo Push_Swap |
| Parsing | Leitura e validação dos argumentos |
| Sorting | Estratégias de ordenação |

O fluxo geral do programa é:

```text
       INPUT
         |
         v
       main.c
         |
         v
      Parsing
         |
         v
    Initialize A
         |
         v
    Select Strategy
         |
         v
       Sorting
         |
         v
     Operations
         |
         v
      OUTPUT
```

---

# 4. Estruturas de dados

## 4.1. Node

Ficheiro: `Stack Structure/StackStruct.h`

A estrutura de cada elemento utiliza uma lista duplamente ligada.

```c
typedef struct s_node
{
    int             value;
    int             index;
    struct s_node   *above;
    struct s_node   *below;
}   t_node;
```

Responsabilidades:

- `value`: valor original do número.
- `index`: posição relativa do número depois da compressão de índices.
- `above`: aponta para o elemento acima.
- `below`: aponta para o elemento abaixo.

## 4.2. Stack

```c
typedef struct s_stack
{
    t_node  *top;
    t_node  *bottom;
    int     size;
}   t_stack;
```

Responsabilidades:

- `top`: primeiro elemento da stack.
- `bottom`: último elemento da stack.
- `size`: quantidade de elementos.

## 4.3. Representação visual

```text
          TOP
           |
           v
        [ Node ]
           |
           v
        [ Node ]
           |
           v
        [ Node ]
           |
           v
        [ Node ]
           |
           v
         BOTTOM
```

A estrutura permite percorrer a stack em ambas as direções.

### Funções identificadas

- `stack_init()`
- `stack_push()`
- `stack_push_bottom()`
- `stack_pop()`
- `stack_pop_bottom()`
- `stack_send()`
- `stack_swap()`
- `stack_rotate()`
- `stack_reverse_rotate()`
- `stack_clear()`
- `stack_is_sorted()`
- `stack_contains()`
- `node_new()`

---

# 5. Operações disponíveis

Diretório: `Operations/`

O projeto implementa as operações clássicas do Push_Swap.

| Operação | Comportamento |
|---|---|
| `sa` | Troca os dois primeiros elementos de A |
| `sb` | Troca os dois primeiros elementos de B |
| `ss` | Executa `sa` e `sb` |
| `pa` | Transfere o topo de B para A |
| `pb` | Transfere o topo de A para B |
| `ra` | Roda A para cima |
| `rb` | Roda B para cima |
| `rr` | Roda A e B para cima |
| `rra` | Roda A para baixo |
| `rrb` | Roda B para baixo |
| `rrr` | Roda A e B para baixo |

## Otimização das operações

Um dos pontos fundamentais para reduzir o número de operações é aproveitar as operações combinadas.

Exemplo:

```text
ra
rb
```

Pode ser substituído por:

```text
rr
```

Da mesma forma:

```text
rra
rrb
```

Pode ser substituído por:

```text
rrr
```

Esta otimização será fundamental na futura implementação de uma estratégia Greedy.

---

# 6. Parsing

Diretório: `Parsing/`

O parsing é responsável por transformar os argumentos recebidos pelo programa em elementos válidos para a stack A.

### Componentes identificados

| Ficheiro | Responsabilidade |
|---|---|
| `ParseInt.c` | Converter e validar inteiros |
| `ParseArguments.c` | Processar argumentos |
| `AppendArgument.c` | Processar argumentos individuais |
| `AppendToken.c` | Converter e inserir tokens |
| `SplitWhitespace.c` | Separar tokens por espaços |
| `ft_split.c` | Dividir strings |
| `ft_strlen.c` | Calcular comprimento |
| `ft_substr.c` | Extrair substrings |

### Validações importantes

- Argumentos vazios.
- Argumentos inválidos.
- Números negativos.
- Sinal positivo.
- `INT_MAX`.
- `INT_MIN`.
- Overflow.
- Números duplicados.
- Strings com múltiplos números.
- Argumentos com espaços.

### Observação

A função `parse_int()` foi analisada e apresenta verificações de overflow antes da multiplicação, incluindo tratamento dos limites dos inteiros.

O parsing também verifica números duplicados antes de inserir os nodes.

---

# 7. Estratégias de ordenação atuais

O projeto contém várias estratégias.

## 7.1. SortThree

Ficheiro: `Sorting/SortThree.c`

Destina-se a ordenar três elementos.

É uma estratégia especializada para conjuntos pequenos.

**Estado:** Implementado.

## 7.2. SortFive

Ficheiro: `Sorting/SortFive.c`

Apesar do nome, a função suporta conjuntos com mais de cinco elementos.

A lógica identificada é:

1. Encontrar o menor elemento em A.
2. Colocar esse elemento no topo.
3. Executar `pb`.
4. Repetir até restarem três elementos.
5. Ordenar os três elementos restantes.
6. Recuperar os elementos de B com `pa`.

**Complexidade interna aproximada:** O(n²).

**Observação:** Esta estratégia é simples, mas pode gerar muitas operações para conjuntos maiores.

## 7.3. ChunkSort

Ficheiros:

- `ChunkSort.c`
- `ChunkPush.c`
- `ChunkFindTarget.c`
- `ChunkAssignIndices.c`
- `ChunkPullMax.c`
- `BringToTop.c`

Esta estratégia utiliza divisão dos números em grupos, denominados chunks.

### Funcionamento atual

1. Atribuir índices aos elementos.
2. Calcular o tamanho dos chunks.
3. Encontrar elementos pertencentes ao chunk atual.
4. Escolher o elemento com menor custo individual de rotação em A.
5. Colocar o elemento no topo.
6. Transferir para B com `pb`.
7. Opcionalmente rodar B com `rb`.
8. Repetir até transferir o chunk.
9. Repetir para os restantes chunks.
10. Recuperar os elementos de B para A, começando pelo maior índice.

### Cálculo atual do chunk

O tamanho é calculado através de:

```text
chunk_width = 2 * ceil(sqrt(size))
```

### Pontos fortes

- Utiliza compressão de índices.
- Divide o problema em grupos.
- Escolhe o elemento com menor custo individual de rotação.
- Utiliza uma estratégia de recuperação baseada no maior índice.

### Limitações identificadas

- O custo é calculado individualmente para A.
- Não considera o custo combinado de A e B.
- Não aproveita sistematicamente `rr` e `rrr`.
- A recuperação de B é baseada sempre no maior índice.
- O tamanho do chunk pode não ser o ideal para todos os conjuntos.

**Estado:** Implementado; otimização por investigar.

## 7.4. RadixSort

Ficheiro: `Sorting/RadixSort.c`

Implementa uma estratégia baseada em Binary LSD Radix Sort.

### Funcionamento

1. Atribuir índices aos elementos.
2. Percorrer os bits dos índices.
3. Verificar o bit atual de cada elemento.
4. Se o bit estiver ativo, executar `ra`.
5. Caso contrário, executar `pb`.
6. Devolver os elementos de B para A.
7. Repetir para o bit seguinte.

### Pontos fortes

- Estratégia previsível.
- Utiliza índices em vez dos valores originais.
- Tem comportamento de operações aproximadamente O(n log n).

### Limitações

- Pode produzir muitas operações.
- Não aproveita necessariamente todas as oportunidades de rotação combinada.
- A eficiência depende do tamanho dos índices.

**Estado:** Implementado; deve permanecer como referência de comparação.

---

# 8. Adaptive Strategy

Ficheiro: `main.c`

O programa possui uma estratégia adaptativa.

Esta estratégia analisa o grau de desordem da stack através da contagem de inversões.

Uma inversão ocorre quando:

```text
value[i] > value[j]
```

para `i < j`.

A contagem é feita comparando pares de elementos.

### Critérios identificados

A implementação utiliza os seguintes limites:

- Até aproximadamente 20% de inversões: SIMPLE.
- Até aproximadamente 50% de inversões: MEDIUM.
- Acima disso: COMPLEX.

Os limites utilizam divisão inteira e devem ser interpretados tendo em conta o arredondamento.

### Estratégias disponíveis

```text
--simple
--medium
--complex
--adaptive
```

Sem uma flag explícita, o comportamento identificado seleciona Adaptive.

### Observação

O cálculo da desordem utiliza dois ciclos e, por isso, apresenta complexidade O(n²).

Uma possível evolução será estudar métricas alternativas de desordem.

---

# 9. Makefile e compilação

O Makefile utiliza:

```makefile
CC := cc
CFLAGS := -Wall -Wextra -Werror
```

### Targets identificados

| Target | Responsabilidade |
|---|---|
| `all` | Compilar o projeto |
| `test` | Executar os testes |
| `test-sanitize` | Compilar e testar com sanitizers |
| `clean` | Remover objetos de compilação |
| `fclean` | Limpeza completa |
| `re` | Recompilar o projeto |

### Sanitizers

O target `test-sanitize` utiliza:

```text
-g -fsanitize=address,undefined
```

Permite detetar problemas como:

- Memory leaks.
- Invalid memory access.
- Buffer overflows.
- Undefined behaviour.

**Nota:** Os targets foram inspecionados no Makefile, mas não foram executados durante a análise.

---

# 10. Testes atuais

O projeto contém testes para:

- Stack Structure.
- Parsing.
- Sorting.
- Interface CLI.

Existe também:

```text
tests/test_cli.py
```

### Testes CLI identificados

- Permutações de conjuntos pequenos.
- Argumentos vazios.
- Um único número.
- Argumentos com espaços.
- Valores nos limites dos inteiros.
- Argumentos inválidos.
- Números duplicados.
- Flags desconhecidas.
- Múltiplas flags.
- Diferentes estratégias.
- Testes de ordenação para 100 e 500 elementos.

O teste CLI utiliza uma função `replay` para reproduzir as operações e verificar se o resultado está ordenado.

### Importante

A existência dos testes não significa que todos tenham passado.

É necessário executar os testes localmente antes de declarar o projeto validado.

---

# 11. Problemas e pontos por confirmar

Esta secção representa a auditoria inicial.

| Elemento | Observação | Prioridade |
|---|---|---|
| ChunkSort | Custo individual em vez de combinado | Alta |
| Rotações | Potencial de melhoria com `rr` e `rrr` | Alta |
| Reinserção | Recuperação baseada no maior índice | Alta |
| Adaptive | Métrica de inversões O(n²) | Média |
| `--bench` | Não identificado no `main.c` analisado | Alta |
| README original | Não identificado na raiz analisada | Baixa |
| `.build` | Artefactos de compilação no repositório | Média |
| Testes | Ainda precisam de execução e validação | Alta |

### Requisito `--bench`

Na análise realizada, não foi encontrado tratamento de `--bench` no `main.c` nem nas estratégias verificadas pelo teste CLI.

É necessário confirmar a sua obrigatoriedade e implementação de acordo com o subject da versão do projeto.

### Artefactos de compilação

Foram identificados diretórios `.build` e `.build-sanitized`.

Recomenda-se avaliar a utilização de `.gitignore` e evitar manter ficheiros `.o` e binários gerados no controlo de versões.

Não remover ficheiros do repositório sem alinhar previamente com os restantes membros do grupo.

---

# 12. Nova direção: otimização de operações

A nossa prioridade futura será reduzir o número de operações, e não apenas reduzir o tempo de execução interno.

Vamos estudar duas abordagens.

## 12.1. Turk Algorithm / Greedy Insertion

Uma estratégia baseada na escolha do movimento mais barato.

### Ideia

1. Preparar as stacks.
2. Manter uma pequena sequência ordenada em A.
3. Transferir elementos para B.
4. Calcular o destino correto de cada elemento.
5. Calcular o custo de movimentação.
6. Escolher o movimento mais barato.
7. Aproveitar `rr` e `rrr`.
8. Repetir até B ficar vazia.
9. Alinhar A.

### Nova função conceptual

```c
calculate_cost();
```

Esta função deverá considerar:

- Posição atual do elemento em B.
- Posição de inserção em A.
- Rotações para cima.
- Rotações para baixo.
- Rotações simultâneas.
- Custo total da operação.

### Fórmulas fundamentais

Quando as rotações têm o mesmo sentido:

```text
cost = max(rotation_a, rotation_b)
```

Quando têm sentidos opostos:

```text
cost = rotation_a + rotation_b
```

O algoritmo Greedy não garante encontrar a solução globalmente ótima. A sua qualidade será avaliada experimentalmente.

## 12.2. LIS — Longest Increasing Subsequence

LIS significa Longest Increasing Subsequence, ou maior subsequência crescente.

### Ideia

Encontrar a maior sequência crescente que podemos preservar em A.

Exemplo:

```text
A = [8, 3, 6, 1, 5, 7, 2]

LIS possível:

[3, 5, 7]
```

Se preservarmos 3 elementos, os restantes 4 terão de ser movimentados para B.

### Vantagem

Quanto maior for a sequência preservada, menor será a quantidade de elementos que precisamos de retirar inicialmente de A.

### Combinação proposta

```text
LIS
 |
 v
Preservar sequência
 |
 v
Enviar restantes para B
 |
 v
Greedy insertion
 |
 v
Ordenar A
```

Esta combinação é uma proposta de investigação, não uma funcionalidade implementada.

---

# 13. Plano de desenvolvimento

A nova implementação deverá ser feita de forma independente.

Não vamos eliminar os algoritmos existentes antes de termos resultados comparativos.

## Fase 1 — Baseline

- [ ] Executar `make`.
- [ ] Executar `make test`.
- [ ] Executar `make test-sanitize`.
- [ ] Testar 100 números.
- [ ] Testar 500 números.
- [ ] Guardar resultados.
- [ ] Registar erros encontrados.

## Fase 2 — Estudo de Greedy

- [ ] Compreender cálculo de posições.
- [ ] Compreender custos de rotação.
- [ ] Estudar `rr` e `rrr`.
- [ ] Desenhar `calculate_cost()`.
- [ ] Estudar a escolha do melhor candidato.
- [ ] Desenvolver pseudocódigo.

## Fase 3 — Estudo de LIS

- [ ] Compreender subsequências crescentes.
- [ ] Estudar o algoritmo LIS.
- [ ] Implementar uma versão independente.
- [ ] Testar sequências pequenas.
- [ ] Medir o tamanho das subsequências encontradas.

## Fase 4 — Implementação experimental

- [ ] Criar estratégia nova.
- [ ] Manter ChunkSort.
- [ ] Manter RadixSort.
- [ ] Integrar a nova estratégia sem destruir código anterior.
- [ ] Testar correctness.
- [ ] Testar edge cases.

## Fase 5 — Otimização

- [ ] Comparar diferentes estratégias.
- [ ] Experimentar diferentes formas de escolher candidatos.
- [ ] Otimizar rotações.
- [ ] Reduzir operações redundantes.
- [ ] Avaliar os resultados em conjuntos aleatórios.

## Fase 6 — Decisão final

- [ ] Escolher a estratégia principal.
- [ ] Validar os requisitos do subject.
- [ ] Rever Norminette.
- [ ] Rever memória.
- [ ] Rever Makefile.
- [ ] Atualizar documentação.

---

# 14. Plano de Benchmark

Os resultados devem ser registados antes e depois de cada otimização.

### Conjuntos de teste

| Tamanho | Tipo |
|---|---|
| 3 | Aleatório |
| 5 | Aleatório |
| 10 | Aleatório |
| 50 | Aleatório |
| 100 | Aleatório |
| 500 | Aleatório |

Também devemos testar:

- Sequências ordenadas.
- Sequências inversas.
- Sequências quase ordenadas.
- Sequências alternadas.
- Sequências aleatórias com várias seeds.

### Tabela de comparação

| Estratégia | 100 números | 500 números | Média | Máximo |
|---|---:|---:|---:|---:|
| Simple | Por medir | Por medir | — | — |
| ChunkSort | Por medir | Por medir | — | — |
| RadixSort | Por medir | Por medir | — | — |
| Turk | Por implementar | Por implementar | — | — |
| LIS + Greedy | Por implementar | Por implementar | — | — |

Não preencher os valores com estimativas. Todos os números devem vir de execuções reais.

---

# 15. Critérios de qualidade

Uma implementação não deve ser considerada concluída apenas porque consegue ordenar alguns exemplos.

Devemos validar:

### Correctness

- Todos os números ficam ordenados.
- Não existem elementos perdidos.
- Não existem elementos duplicados.
- B termina vazia.
- Todas as operações são válidas.

### Memory management

- Todos os nodes são libertados.
- Não existem leaks.
- Não existem acessos inválidos.
- Não existem use-after-free.

### Performance

- Número de operações.
- Média de operações.
- Máximo de operações.
- Consistência entre diferentes conjuntos.
- Complexidade interna.

### Code quality

- Norminette.
- `-Wall -Wextra -Werror`.
- Código legível.
- Funções pequenas.
- Headers organizados.
- Makefile correto.

---

# 16. Vocabulário técnico

| Inglês | Português |
|---|---|
| Stack | Pilha |
| Node | Nó |
| Pointer | Ponteiro |
| Linked List | Lista ligada |
| Doubly Linked List | Lista duplamente ligada |
| Rotation | Rotação |
| Reverse Rotation | Rotação inversa |
| Greedy Algorithm | Algoritmo ganancioso |
| Candidate | Candidato |
| Cost Calculation | Cálculo de custo |
| Longest Increasing Subsequence | Maior subsequência crescente |
| Rank Compression | Compressão de índices |
| Benchmark | Teste de desempenho |
| Edge Case | Caso limite |
| Memory Leak | Fuga de memória |
| Undefined Behaviour | Comportamento indefinido |
| Time Complexity | Complexidade temporal |
| Space Complexity | Complexidade espacial |
| Optimization | Otimização |

---

# 17. Decisões arquiteturais futuras

Esta secção deverá ser atualizada durante a evolução do projeto.

| Decisão | Estado |
|---|---|
| Manter parsing atual | Por avaliar |
| Manter lista duplamente ligada | Por avaliar |
| Manter operações atuais | Por avaliar |
| Substituir ChunkSort | Em investigação |
| Desenvolver Turk | Planeado |
| Desenvolver LIS | Planeado |
| Combinar LIS + Greedy | Em investigação |
| Melhorar Adaptive | Planeado |
| Implementar ou confirmar `--bench` | Por confirmar |

---

# 18. Histórico de evolução

| Versão | Descrição |
|---|---|
| v1 — Baseline | Arquitetura original analisada |
| v2 | Primeira estratégia Greedy |
| v3 | Implementação LIS |
| v4 | Comparação LIS + Greedy |
| v5 | Otimização final |

---

# 19. Princípio de desenvolvimento

Este projeto será desenvolvido com uma prioridade:

**Encontrar a melhor sequência de operações possível, mantendo o código correto, compreensível e sustentável.**

Não vamos substituir algoritmos apenas porque parecem melhores teoricamente.

Cada mudança deverá ser justificada por:

1. Uma hipótese técnica.
2. Uma implementação.
3. Testes de correctness.
4. Resultados de benchmark.
5. Comparação com a versão anterior.

O objetivo é compreender cada decisão algorítmica e conseguir explicar as escolhas feitas durante a avaliação da 42 School.

---

**Última atualização:** 24/11/2026
**Estado:** Documentação inicial — antes da reestruturação.







---
---
---
---







# `Push_Swap — Benchmark Baseline`

**Data:** 24/11/2026

**Ambiente:** Linux
**Compiler:** cc
**Flags:** -Wall -Wextra -Werror -g -fsanitize=address,undefined

## Testes funcionais

- 999 CLI cases passed.
- Todas as permutações de 2 a 5 elementos passaram.
- Parsing e validação passaram.
- Adaptive dispatch passou.
- Replay dos conjuntos grandes passou.

## Resultados — 100 elementos

| Strategy | Average | Maximum |
|---|---:|---:|
| Default | 748.9 | 1084 |
| Simple | 891.3 | 1566 |
| Medium | 495.6 | 680 |
| Complex | 963.6 | 1084 |
| Adaptive | 748.9 | 1084 |

## Resultados — 500 elementos

| Strategy | Average | Maximum |
|---|---:|---:|
| Default | 4980.0 | 6784 |
| Simple | 18256.7 | 34472 |
| Medium | 4076.9 | 5941 |
| Complex | 6030.2 | 6784 |
| Adaptive | 4980.0 | 6784 |

## Primeira conclusão

A estratégia Medium apresenta o menor número médio e máximo de operações nos dois tamanhos testados.

A estratégia Complex, baseada em RadixSort, não supera Medium nestes testes.

## Objetivo da próxima versão

Desenvolver uma estratégia Greedy/LIS e comparar os resultados com esta baseline.

Os resultados futuros devem utilizar conjuntos de teste equivalentes para permitir uma comparação justa.
