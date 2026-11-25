## Sorting/ChunkFindTarget.c
	`t_node *find_chunk_target(t_stack *a, int first_rank, int end_rank)
	{
		t_node *scan;
		t_node *best_node;
		int best_cost;
		int current_cost;
		int current_position;

		best_node = NULL;
		best_cost = a->size;
		current_position = 0;
		scan = a->top;
		while (scan)
		{
			if (scan->index >= first_rank && scan->index < end_rank)
			{
				current_cost = rotation_cost(current_position, a->size);
				if (!best_node || current_cost < best_cost)
				{
					best_node = scan;
					best_cost = current_cost;
				}
			}
			scan = scan->below;
			current_position++;
		}
		return (best_node);
	}`

- current_position - [O código percorre a stack e incrementa current_position em cada iteração.]
- current_cost < best_cost - [Se encontrei um elemento cujo custo de rotação é inferior ao melhor custo encontrado anteriormente, atualizo o candidato.]
- Tem algo de importante que é: [A funcao nao conhece a stack de B]
## O problema

A função atual olha apenas para a **stack A**. Escolhe o número mais barato de mover em A. Isto pode dar um mau resultado, porque também temos de mover a stack B.

## Exemplo

Temos dois candidatos.

| | Stack A (rotações) | Stack B (rotações) |
|---|---|---|
| **Candidato X** | 2 | 8 |
| **Candidato Y** | 4 | 1 |

## Olhando só para A

- X custa 2.
- Y custa 4.
- Escolhemos **X**, porque parece mais barato.

## Olhando para as duas stacks

Temos de considerar o **sentido** das rotações.

- **Mesmo sentido** (`ra` + `rb`, ou `rra` + `rrb`): podemos usar `rr` ou `rrr`. Uma operação move as duas stacks. O custo é o número **maior**.
- **Sentidos diferentes**: não podemos combinar. O custo é a **soma** dos dois números.

| | Mesmo sentido | Sentidos diferentes |
|---|---|---|
| **Candidato X** | max(2, 8) = **8** | 2 + 8 = **10** |
| **Candidato Y** | max(4, 1) = **4** | 4 + 1 = **5** |

## Resultado

- X custa 8 ou 10 operações.
- Y custa 4 ou 5 operações.
- **Y é a escolha muito melhor.**

## O que falta na função atual

A função não sabe duas coisas:

1. A **posição** do elemento alvo na stack B.
2. O **custo combinado** das rotações nas duas stacks.

## Solução

Para cada candidato em A:

1. Encontrar a posição alvo em B.
2. Calcular o custo em A e o custo em B (nos dois sentidos).
3. Calcular o custo total (`max` se for o mesmo sentido, soma se forem sentidos diferentes).
4. Escolher o candidato com o **menor custo total**.


---

# Pull Max

A função `pull_max()` transfere os maiores elementos de B para A, procurando reduzir o número de operações.

- `find_rank()`: procura um elemento pelo seu index.
- `pos_of()`: encontra a posição de um elemento.
- `cost_of()`: calcula o menor número de rotações necessárias.

**Otimização:**
1. Procura o maior e o segundo maior elementos.
2. Compara os custos de rotação.
3. Se compensar, retira primeiro o segundo maior e depois o maior.
4. Executa `sa` para corrigir a ordem em A.
5. Caso contrário, retira apenas o maior.

**Objetivo:** reduzir o número de operações aproveitando a posição dos elementos em B.

## Objetivo

Retirar os maiores elementos da stack B e colocá-los na stack A, mantendo a ordem correta.

## Funções auxiliares

### `find_rank(b, rank)`
```text
COMEÇAR no topo de B
ENQUANTO existir um node:
    SE o index do node for igual ao rank:
        DEVOLVER o node
    AVANÇAR para o próximo node
DEVOLVER NULL
```

### `pos_of(b, target)`
```text
COMEÇAR no topo de B
INICIALIZAR posição a 0
ENQUANTO o node atual não for o target:
    AVANÇAR para o próximo node
    INCREMENTAR posição
DEVOLVER posição
```

### `cost_of(b, target)`
```text
OBTER a posição do target

SE a posição for menor que a distância inversa:
    DEVOLVER posição
SENÃO:
    DEVOLVER distância inversa
```

## `pull_max(a, b)`

```text
SE B estiver vazia:
    TERMINAR

CALCULAR o maior rank esperado

PROCURAR o maior elemento em B
PROCURAR o segundo maior elemento em B

SE ambos existirem:
    CALCULAR o custo de rotação do segundo maior
    CALCULAR o custo de rotação do maior

    SE o segundo maior compensar:
        COLOCAR o segundo maior no topo de B
        PASSAR o segundo maior para A

        COLOCAR o maior no topo de B
        PASSAR o maior para A

        TROCAR os dois elementos do topo de A
        TERMINAR

COLOCAR o maior no topo de B
PASSAR o maior para A
```

## Ideia principal da otimização

Em vez de trazer sempre apenas o maior elemento:

1. Verificar se o segundo maior está mais barato de retirar.
2. Se compensar, retirar primeiro o segundo maior.
3. Retirar depois o maior.
4. Trocar os dois elementos no topo de A com `sa`.
5. Caso contrário, retirar apenas o maior.

**Nota:** `cost_of()` calcula apenas o custo individual de rotação em B. Não considera rotações combinadas (`rr` ou `rrr`).
