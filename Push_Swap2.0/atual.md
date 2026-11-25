# Push_Swap — Estado atual

> Atualização da documentação inicial `antes.md`, com as diferenças entre a
> baseline registada e o estado atual do projeto.

**Projeto:** 42 Lisboa — Push_Swap  
**Data desta atualização:** 25/11/2026  
**Objetivo:** ordenar os números com operações válidas, mantendo a correção e
reduzindo a quantidade de movimentos.

---

## 1. Resumo das alterações

O projeto mantém a arquitetura por módulos, o parsing, as operações permitidas,
as estruturas de stacks e os testes. A alteração mais importante foi substituir
o algoritmo associado à estratégia `COMPLEX`: a implementação ativa utiliza
agora Quick Sort adaptado às duas stacks, em vez de Radix Sort.

Também foram ajustadas a seleção adaptativa e a largura dos chunks para
melhorar os resultados experimentais em entradas de 100 e 500 elementos.

| Área | Estado anterior (`antes.md`) | Estado atual |
|---|---|---|
| Estruturas e operações | Stacks ligadas e operações Push_Swap | Mantidas |
| Parsing e validação | Módulo de parsing próprio | Mantidos |
| Ordenação de 3 e poucos elementos | `SortThree` e `SortFive` | Mantidas |
| Estratégia `MEDIUM` | Chunk Sort | Mantida; largura ajustada |
| Estratégia `COMPLEX` | Radix Sort | Quick Sort com partições entre A e B |
| Seleção `ADAPTIVE` | Baseada na contagem de inversões | Mantida, com encaminhamento por tamanho e caso inverso |
| Estratégias experimentais | Greedy/LIS proposto para estudo | Não fazem parte do fluxo atual |
| Thresholds de desordem | 0,2 e 0,5 | Mantidos; não foram alterados |

---

## 2. O que continua igual

- O programa recebe inteiros, valida os argumentos e escreve as operações
  necessárias no `stdout`.
- A stack A termina ordenada de forma crescente e a stack B fica vazia.
- As stacks continuam implementadas como listas duplamente ligadas.
- O conjunto de operações continua a ser o permitido pelo Push_Swap.
- O parsing continua a tratar espaços, sinais, limites de `int`, entradas
  inválidas e valores duplicados.
- `SortThree` e `SortFive` continuam a tratar entradas pequenas.
- `MEDIUM` continua a usar Chunk Sort; a estratégia continua a atribuir ranks,
  distribuir elementos de A para B por janelas e recuperar elementos de B.
- `ADAPTIVE` continua a calcular inversões para classificar a desordem. Os
  limites do subject correspondentes a 0,2 e 0,5 não foram modificados.
- As flags explícitas `--simple`, `--medium`, `--complex` e `--adaptive`
  continuam disponíveis. Sem flag, o programa seleciona `ADAPTIVE`.
- Os testes de stack, parsing, sorting, CLI e sanitizers continuam no projeto.

---

## 3. O que mudou

### 3.1. Quick Sort na estratégia `COMPLEX`

O `RadixSort.c` indicado na baseline já não faz parte da compilação ativa e foi
removido. A estratégia `COMPLEX` utiliza agora os módulos:

- `Sorting/QuickSort.c`
- `Sorting/QuickSplit.c`
- `Sorting/QuickSmallA.c`
- `Sorting/QuickSmallB.c`

O algoritmo atribui ranks aos elementos, divide intervalos de ranks entre as
duas stacks e ordena recursivamente os subproblemas. Os casos pequenos são
tratados com rotinas próprias. Não se afirma aqui uma garantia de limite de
operações para todas as permutações: o desempenho reportado é experimental.

### 3.2. Seleção adaptativa ajustada

O dispatch em `main.c` mantém a classificação por inversões, mas aplica
encaminhamentos adicionais:

- Se a entrada tiver exatamente 100 elementos e a classificação escolher
  `COMPLEX`, usa Chunk Sort. Os testes mostraram que esta alternativa reduz
  movimentos para este tamanho.
- Para entradas com pelo menos 500 elementos classificadas como `MEDIUM`, usa
  Quick Sort, exceto quando a sequência está estritamente em ordem inversa.
- Uma sequência estritamente decrescente com pelo menos 500 elementos usa
  Chunk Sort, que apresentou um resultado melhor nesse caso testado.

Estas decisões só alteram a escolha automática. As flags explícitas continuam
a selecionar a estratégia pedida. Os thresholds 0,2 e 0,5 permanecem intactos.

### 3.3. Largura dos chunks

Em `Sorting/ChunkSort.c`, a largura é agora calculada como:

```text
width = 2 * ceil(sqrt(n))
```

Esta largura foi experimentada porque reduziu o máximo observado nas entradas
de 100 elementos sem prejudicar os resultados medidos para 500. É um ajuste
empírico, não uma garantia de ótimo global.

### 3.4. Limpeza e documentação

- Foram removidos módulos experimentais de janela dinâmica e Insertion Sort que
  não faziam parte do fluxo ativo.
- Foram adicionados comentários em português a funções de produção e de teste.
- Foram atualizados o Makefile, os headers e a lista de fontes para refletir os
  algoritmos ativos.
- Foram corrigidos includes necessários para compilar sem depender de
  declarações indiretas.
- Os testes existentes foram preservados.

---

## 4. Benchmark: baseline e estado atual

### Resultados registados em `antes.md`

| Estratégia | 100: média / máximo | 500: média / máximo |
|---|---:|---:|
| Default / Adaptive | 748,9 / 1084 | 4980,0 / 6784 |
| Medium | 495,6 / 680 | 4076,9 / 5941 |
| Complex (Radix Sort na baseline) | 963,6 / 1084 | 6030,2 / 6784 |

### Estado atual — 20 entradas aleatórias por tamanho

As entradas foram geradas com `shuf -i 0-999 -n N`. Cada sequência foi
verificada com `checker_linux`.

| Tamanho | Média | Mínimo | Máximo | Checker |
|---:|---:|---:|---:|---:|
| 100 | 629,75 | 594 | 696 | 20/20 `OK` |
| 500 | 5247,75 | 5206 | 5302 | 20/20 `OK` |

O maior resultado observado ficou abaixo do objetivo experimental de 700
operações para 100 elementos e 5500 para 500 elementos. Isto descreve apenas
as amostras executadas; não prova que todas as entradas possíveis respeitam os
limites.

### Casos adicionais

- Entrada estritamente inversa de 500 elementos: 1988 operações, checker `OK`.
- Na bateria CLI determinística do projeto, o modo padrão registou:
  - 100 elementos: média 460,1, máximo 653.
  - 500 elementos: média 3786,8, máximo 5280.

Os dois conjuntos de resultados atuais usam amostras diferentes. Não se devem
comparar médias de conjuntos diferentes como se fossem entradas equivalentes.

---

## 5. Validação atual

Na validação realizada após os ajustes:

- `make re` / compilação com `-Wall -Wextra -Werror`: passou.
- `make test`: passou, incluindo 17 grupos de testes de stack, testes de
  parsing, 300 casos de sorting e 999 casos CLI.
- `make test-sanitize`: passou nos 999 casos CLI com AddressSanitizer e
  UndefinedBehaviorSanitizer.
- Norminette nos ficheiros de produção alterados (`main.c` e
  `Sorting/ChunkSort.c`): passou.

A verificação global de Norminette ainda reporta violações em ficheiros de
testes preexistentes, incluindo limites de linhas/funções e ternários. Isso é
distinto dos resultados dos testes funcionais e dos sanitizers.

---

## 6. Pontos que continuam a merecer atenção

- A seleção adaptativa conta inversões em tempo O(n²). É adequada aos tamanhos
  testados, mas pode ser dispendiosa em entradas muito maiores.
- A largura dos chunks e os encaminhamentos por tamanho foram ajustados com
  benchmarks, mas continuam heurísticas.
- Quick Sort pode produzir contagens diferentes conforme a permutação. Os
  resultados médios não garantem que o máximo de todas as entradas fique abaixo
  dos objetivos.
- A bateria de 20 entradas aleatórias deve ser repetida com sementes e conjuntos
  guardados se for necessária uma comparação reproduzível entre versões.
- A Norminette global deve ser tratada separadamente nos ficheiros de teste,
  sem eliminar cobertura existente.
- O suporte ao requisito `--bench` não foi confirmado nesta atualização e deve
  ser verificado diretamente contra a versão do subject utilizada.

---

## 7. Comandos úteis

Compilar:

```sh
make re
```

Executar os testes:

```sh
make test
make test-sanitize
```

Gerar, contar e validar operações para o mesmo conjunto de 100 números:

```sh
ARG=$(shuf -i 0-999 -n 100 | tr '\n' ' ')
OPS=$(./push_swap $ARG)
printf '%s\n' "$OPS" | sed '/^$/d' | wc -l
printf '%s\n' "$OPS" | ./checker_linux $ARG
```

Para testar 500 números, substitua `-n 100` por `-n 500`.

---

## 8. Conclusão

Em comparação com a baseline de `antes.md`, a alteração principal é a troca de
Radix Sort por Quick Sort na estratégia `COMPLEX`, acompanhada por ajustes no
dispatch adaptativo e no tamanho dos chunks. A arquitetura central, o parsing,
as operações Push_Swap, as estratégias para entradas pequenas e o conjunto de
testes foram preservados.

Nos benchmarks executados, o modo padrão atingiu os limites experimentais
definidos para 100 e 500 elementos, com todas as entradas medidas verificadas
como ordenadas pelo checker. A melhoria foi medida nas amostras indicadas e
deve continuar a ser acompanhada por testes reproduzíveis e variados.
