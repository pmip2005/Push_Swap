import pypandoc

markdown = r"""# Benchmark do Push_Swap — comparação de estratégias

## Objetivo

Este script compara quatro modos do teu programa `push_swap`:

- `simple`
- `medium`
- `complex`
- `adaptive`

Executa 100 testes com 100 números e outros 100 testes com 500 números.

A parte mais importante é que **as quatro estratégias recebem exatamente as mesmas entradas dentro de cada dimensão**. Assim, a comparação é mais justa: uma estratégia não beneficia de ter recebido números mais fáceis.

O script mede:

- **Média:** número médio de operações nos 100 testes.
- **Mínimo:** menor número de operações observado.
- **Máximo:** maior número de operações observado.
- **Falhas:** quantidade de testes em que o `checker_linux` não devolveu `OK`.

> Nota: o script usa divisão inteira do Bash em `TOTAL / 100`. Por isso, a média é apresentada sem casas decimais.

---

## Script completo comentado

	`#!/bin/bash

	benchmark()
	{
		SIZE=$1
		RANGE=$2
		INPUTS="/tmp/ps_inputs_$SIZE.txt"

		# Gerar 100 entradas e guardar para reutilizar
		> "$INPUTS"
		for i in $(seq 1 100); do
			shuf -i 0-$RANGE -n "$SIZE" | tr '\n' ' ' >> "$INPUTS"
			echo >> "$INPUTS"
		done

		for MODE in simple medium complex adaptive; do
			TOTAL=0
			MIN=999999
			MAX=0
			FAIL=0

			while IFS= read -r ARG; do
				[ -z "$ARG" ] && continue

				./push_swap --"$MODE" $ARG > /tmp/ps_ops

				OPS=$(wc -l < /tmp/ps_ops)
				CHECK=$(./checker_linux $ARG < /tmp/ps_ops)

				TOTAL=$((TOTAL + OPS))
				[ "$OPS" -lt "$MIN" ] && MIN=$OPS
				[ "$OPS" -gt "$MAX" ] && MAX=$OPS
				[ "$CHECK" != "OK" ] && FAIL=$((FAIL + 1))
			done < "$INPUTS"

			echo "===== $MODE | $SIZE números ====="
			echo "Média: $((TOTAL / 100))"
			echo "Mínimo: $MIN"
			echo "Máximo: $MAX"
			echo "Falhas: $FAIL"
			echo
		done
	}

	benchmark 100 999
	benchmark 500 9999

	rm -f /tmp/ps_inputs_100.txt /tmp/ps_inputs_500.txt /tmp/ps_ops`

```bash
#!/bin/bash

# Define uma função chamada benchmark.
# Recebe dois argumentos:
#   $1 = quantidade de números a testar (100 ou 500)
#   $2 = limite superior do intervalo usado pelo shuf
benchmark()
{
    SIZE=$1
    RANGE=$2

    # Ficheiro temporário onde vamos guardar as 100 entradas.
    # O nome muda consoante o tamanho do teste.
    # Exemplo: /tmp/ps_inputs_100.txt
    INPUTS="/tmp/ps_inputs_$SIZE.txt"

    # Cria o ficheiro vazio (ou apaga o conteúdo anterior).
    # O símbolo > redireciona a saída para o ficheiro.
    > "$INPUTS"

    # Gera 100 conjuntos de números aleatórios.
    for i in $(seq 1 100); do

        # shuf:
        #   -i 0-$RANGE  -> escolhe números entre 0 e RANGE, inclusive
        #   -n "$SIZE"  -> escolhe SIZE números sem repetição
        #
        # tr '\n' ' ' transforma as quebras de linha em espaços,
        # para formar uma linha de argumentos para o push_swap.
        #
        # >> acrescenta o resultado ao fim do ficheiro INPUTS,
        # sem apagar as entradas que já lá estão.
        shuf -i 0-$RANGE -n "$SIZE" | tr '\n' ' ' >> "$INPUTS"

        # Acrescenta uma quebra de linha para separar esta entrada
        # da próxima entrada no ficheiro.
        echo >> "$INPUTS"
    done

    # Percorre os quatro modos que queremos comparar.
    for MODE in simple medium complex adaptive; do

        # Inicializa os acumuladores e os extremos para este modo.
        # TOTAL soma todas as operações.
        # MIN começa num valor muito alto para poder ser atualizado.
        # MAX começa em zero.
        # FAIL conta os testes que não passaram no checker.
        TOTAL=0
        MIN=999999
        MAX=0
        FAIL=0

        # Lê o ficheiro linha a linha.
        # Cada linha contém uma entrada com SIZE números.
        #
        # IFS= evita que o Bash remova espaços no início/fim.
        # -r impede que barras invertidas sejam interpretadas.
        while IFS= read -r ARG; do

            # Ignora linhas vazias.
            [ -z "$ARG" ] && continue

            # Executa o push_swap no modo atual.
            # --"$MODE" forma opções como --simple ou --adaptive.
            # $ARG é expandido em vários argumentos, um por número.
            #
            # A saída (as operações) é guardada no ficheiro temporário.
            ./push_swap --"$MODE" $ARG > /tmp/ps_ops

            # Conta as linhas do ficheiro de operações.
            # Cada linha representa uma operação do Push_Swap.
            OPS=$(wc -l < /tmp/ps_ops)

            # Executa o checker com a mesma entrada.
            # A sequência de operações é enviada pela entrada standard
            # (stdin) através do símbolo <.
            #
            # CHECK deverá ser "OK" se a sequência ordenar corretamente
            # a stack; caso contrário, será outro resultado.
            CHECK=$(./checker_linux $ARG < /tmp/ps_ops)

            # Adiciona o número de operações ao total.
            TOTAL=$((TOTAL + OPS))

            # Atualiza o mínimo, se este teste tiver menos operações.
            [ "$OPS" -lt "$MIN" ] && MIN=$OPS

            # Atualiza o máximo, se este teste tiver mais operações.
            [ "$OPS" -gt "$MAX" ] && MAX=$OPS

            # Se o checker não devolver exatamente "OK",
            # incrementa o contador de falhas.
            [ "$CHECK" != "OK" ] && FAIL=$((FAIL + 1))

        # Indica que o while deve ler as linhas do ficheiro INPUTS.
        done < "$INPUTS"

        # Apresenta o resumo deste modo.
        echo "===== $MODE | $SIZE números ====="

        # Divide o total por 100 para obter a média inteira.
        echo "Média: $((TOTAL / 100))"

        # Apresenta o menor e o maior número de operações observado.
        echo "Mínimo: $MIN"
        echo "Máximo: $MAX"

        # Apresenta quantas entradas não passaram no checker.
        echo "Falhas: $FAIL"
        echo
    done
}

# Primeiro benchmark:
# 100 entradas, cada uma com 100 números entre 0 e 999.
benchmark 100 999

# Segundo benchmark:
# 100 entradas, cada uma com 500 números entre 0 e 9999.
benchmark 500 9999

# Apaga os ficheiros temporários no fim.
# -f evita erro caso algum dos ficheiros não exista.
rm -f /tmp/ps_inputs_100.txt /tmp/ps_inputs_500.txt /tmp/ps_ops
```

---

## Explicação dos comandos e símbolos importantes

| Comando ou símbolo | Significado |
|---|---|
| `#!/bin/bash` | Indica que o script deve ser executado com Bash. |
| `function()` / `benchmark()` | Define uma função reutilizável. |
| `$1`, `$2` | Primeiro e segundo argumentos recebidos pela função. |
| `$(comando)` | Executa um comando e substitui a expressão pelo resultado. |
| `shuf` | Gera uma ordem aleatória de linhas/números. |
| `seq` | Gera uma sequência de números. |
| `tr` | Transforma ou substitui caracteres. |
| `>` | Redireciona a saída e substitui o conteúdo do ficheiro. |
| `>>` | Acrescenta a saída ao fim do ficheiro. |
| `<` | Usa um ficheiro como entrada standard de um comando. |
| `\|` | Envia a saída de um comando para a entrada do seguinte (pipe). |
| `while IFS= read -r` | Lê um ficheiro linha a linha. |
| `[ -z "$ARG" ]` | Verifica se a variável está vazia. |
| `&&` | Executa o comando seguinte se o anterior tiver sucesso. |
| `$((...))` | Faz operações aritméticas no Bash. |
| `wc -l` | Conta linhas. |
| `rm -f` | Remove ficheiros sem pedir confirmação e sem erro se não existirem. |

---

## Porque guardamos as entradas num ficheiro?

Imagina que geramos 100 entradas aleatórias e testamos primeiro `simple`, depois `medium`, `complex` e `adaptive`.

Se gerássemos números novos para cada modo, a comparação não seria justa. Uma estratégia poderia receber entradas mais fáceis por acaso.

Ao guardar as entradas em `INPUTS`, todos os modos leem exatamente as mesmas 100 linhas.

Isto é uma forma de controlar a variável de entrada durante a experiência.

---

## Como executar

1. Guarda o conteúdo do script num ficheiro, por exemplo `benchmark.sh`.
2. Abre o terminal na pasta onde estão `push_swap` e `checker_linux`.
3. Dá permissão de execução:

```bash
chmod +x benchmark.sh
```

4. Executa:

```bash
./benchmark.sh
```

Também podes executá-lo diretamente com Bash:

```bash
bash benchmark.sh
```

### Pré-requisitos

Na pasta atual devem existir:

- `push_swap`, compilado e executável;
- `checker_linux`, executável;
- os modos `--simple`, `--medium`, `--complex` e `--adaptive` implementados no teu programa.

---

## Como interpretar os resultados

Exemplo fictício:

```text
===== adaptive | 500 números =====
Média: 5243
Mínimo: 5177
Máximo: 5340
Falhas: 0
```

Interpretação:

- A média foi de 5 243 operações por entrada.
- O melhor caso observado usou 5 177 operações.
- O pior caso observado usou 5 340 operações.
- Nenhuma das 100 entradas falhou no checker.

Não uses apenas a média para escolher a estratégia. Compara também o máximo e confirma que `Falhas` é zero.

## Limitações e cuidados

1. **A aleatoriedade:** o script não fixa uma seed. Cada execução gera um conjunto diferente de entradas. Para comparar versões do código em condições rigorosamente iguais, guarda o ficheiro de entradas e reutiliza-o.
2. **Erros de execução:** o script conta como falha qualquer resultado do checker diferente de `OK`, mas não interrompe automaticamente se `push_swap` falhar ao compilar ou executar.
3. **Divisão inteira:** `TOTAL / 100` descarta a parte decimal. Para uma média com casas decimais, podes usar `awk` ou outra ferramenta.
4. **Contagem de operações:** `wc -l` conta linhas. Pressupõe que cada operação emitida ocupa exatamente uma linha e que não há mensagens de diagnóstico misturadas com as operações.
5. **Desempenho do benchmark:** executar 800 chamadas ao `push_swap` e 800 ao checker pode demorar algum tempo, dependendo da máquina.

---

## Vocabulário técnico

- **Benchmark:** teste de desempenho para medir e comparar soluções.
- **Input:** entrada fornecida ao programa.
- **Output:** saída produzida pelo programa.
- **Standard input (stdin):** entrada standard de um processo.
- **Standard output (stdout):** saída standard de um processo.
- **Redirection:** redirecionamento da entrada ou saída.
- **Pipe:** ligação que encaminha a saída de um comando para outro.
- **Seed:** valor inicial que permite reproduzir uma sequência pseudoaleatória, quando o gerador suporta esse mecanismo.
- **Failure:** falha.
- **Average:** média.
- **Minimum / Maximum:** mínimo / máximo.
"""

output_path = "/mnt/data/push_swap_benchmark_explicado.md"
pypandoc.convert_text(
    markdown,
    "md",
    format="md",
    outputfile=output_path,
    extra_args=["--standalone"]
)

print(f"Ficheiro criado: {output_path}")
