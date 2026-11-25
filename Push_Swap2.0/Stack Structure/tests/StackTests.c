/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackTests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-15 21:48:56 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-15 21:48:56 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../StackStruct.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	g_passed;
static int	g_color;

/* Mostra o titulo de uma secao dos testes. */
static void	section(const char *title)
{
	printf("\n  %s%s%s\n", g_color ? "\033[1;36m" : "", title,
		g_color ? "\033[0m" : "");
	puts("  ------------------------------------------------");
	fflush(stdout);
}

/* Regista e imprime a conclusao de um grupo de verificacoes. */
static void	passed(const char *description)
{
	g_passed++;
	printf("  %s[PASS]%s  %s\n", g_color ? "\033[32m" : "",
		g_color ? "\033[0m" : "", description);
	fflush(stdout);
}

/* Confirma valores, tamanho e ligacoes nos dois sentidos da stack. */
static void	expect_stack(t_stack *stack, const int *values, int count)
{
	t_node	*current;
	t_node	*previous;
	int		i;

	assert(stack->size == count);
	current = stack->top;
	previous = NULL;
	i = 0;
	while (i < count)
	{
		assert(current != NULL);
		assert(current->value == values[i]);
		assert(current->above == previous);
		previous = current;
		current = current->below;
		i++;
	}
	assert(current == NULL && previous == stack->bottom);
	current = stack->bottom;
	previous = NULL;
	while (i > 0)
	{
		i--;
		assert(current != NULL);
		assert(current->value == values[i]);
		assert(current->below == previous);
		previous = current;
		current = current->above;
	}
	assert(current == NULL && previous == stack->top);
}

/* Cria um no e confirma os seus valores e ligacoes iniciais. */
static t_node	*checked_node(int value)
{
	t_node	*node;

	node = node_new(value);
	assert(node != NULL);
	assert(node->value == value);
	assert(node->above == NULL && node->below == NULL);
	return (node);
}

/* Testa stacks vazias, stacks unitarias e operacoes de limpeza. */
static void	test_empty_and_single(void)
{
	t_stack	a;
	t_stack	b;
	t_node	*node;
	t_node	*removed;

	stack_init(&a);
	stack_init(&b);
	section("01 / Empty stacks");
	expect_stack(&a, NULL, 0);
	assert(stack_is_sorted(&a) && !stack_contains(&a, 3));
	passed("Initialization, sorted check and search");
	assert(stack_pop(&a) == NULL);
	assert(stack_pop_bottom(&a) == NULL);
	passed("Popping either end returns NULL");
	stack_swap(&a);
	stack_rotate(&a);
	stack_reverse_rotate(&a);
	stack_send(&a, &b);
	expect_stack(&a, NULL, 0);
	expect_stack(&b, NULL, 0);
	passed("Swap, rotations and send leave empty stacks intact");

	section("02 / Single node");
	node = checked_node(3);
	stack_push(&a, node);
	expect_stack(&a, (int[]){3}, 1);
	assert(a.top == node && a.bottom == node);
	assert(stack_contains(&a, 3) && stack_is_sorted(&a));
	passed("New node becomes both top and bottom");
	stack_swap(&a);
	stack_rotate(&a);
	stack_reverse_rotate(&a);
	expect_stack(&a, (int[]){3}, 1);
	assert(a.top == node);
	passed("Swap and rotations preserve the same node");
	stack_send(&a, &b);
	expect_stack(&a, NULL, 0);
	expect_stack(&b, (int[]){3}, 1);
	assert(b.top == node);
	passed("Send moves the original node between stacks");
	removed = stack_pop_bottom(&b);
	assert(removed == node);
	assert(!removed->above && !removed->below);
	expect_stack(&b, NULL, 0);
	stack_push_bottom(&a, removed);
	expect_stack(&a, (int[]){3}, 1);
	removed = stack_pop(&a);
	assert(removed == node && !removed->above && !removed->below);
	free(removed);
	expect_stack(&a, NULL, 0);
	stack_clear(&a);
	stack_clear(&b);
	passed("Both pops detach links; empty cleanup is safe");
}

/* Testa a ordem, os ponteiros, as operacoes e a reutilizacao das stacks. */
static void	test_operations(void)
{
	t_stack	a;
	t_stack	b;
	t_node	*first;
	t_node	*second;
	t_node	*third;

	stack_init(&a);
	stack_init(&b);
	section("03 / Order and pointer integrity");
	first = checked_node(1);
	second = checked_node(3);
	third = checked_node(8);
	stack_push_bottom(&a, first);
	stack_push_bottom(&a, second);
	stack_push_bottom(&a, third);
	expect_stack(&a, (int[]){1, 3, 8}, 3);
	assert(stack_is_sorted(&a));
	assert(stack_contains(&a, 1) && stack_contains(&a, 3));
	assert(stack_contains(&a, 8) && !stack_contains(&a, 42));
	passed("Build [1, 3, 8]; search top, middle and bottom");
	stack_swap(&a);
	expect_stack(&a, (int[]){3, 1, 8}, 3);
	assert(a.top == second && a.top->below == first);
	assert(!stack_is_sorted(&a));
	passed("Swap: [1, 3, 8] -> [3, 1, 8]");
	stack_swap(&a);
	stack_rotate(&a);
	expect_stack(&a, (int[]){3, 8, 1}, 3);
	assert(a.top == second && a.bottom == first);
	passed("Rotate: [1, 3, 8] -> [3, 8, 1]");
	stack_reverse_rotate(&a);
	expect_stack(&a, (int[]){1, 3, 8}, 3);
	passed("Reverse rotation undoes rotation");
	stack_reverse_rotate(&a);
	expect_stack(&a, (int[]){8, 1, 3}, 3);
	assert(a.top == third && a.bottom == second);
	passed("Reverse rotate: [1, 3, 8] -> [8, 1, 3]");
	stack_rotate(&a);
	stack_push(&b, checked_node(-5));
	stack_send(&a, &b);
	expect_stack(&a, (int[]){3, 8}, 2);
	expect_stack(&b, (int[]){1, -5}, 2);
	assert(b.top == first);
	passed("Send onto a nonempty destination preserves both stacks");

	section("04 / Two nodes and cleanup");
	stack_swap(&a);
	expect_stack(&a, (int[]){8, 3}, 2);
	stack_rotate(&a);
	expect_stack(&a, (int[]){3, 8}, 2);
	stack_reverse_rotate(&a);
	expect_stack(&a, (int[]){8, 3}, 2);
	stack_clear(&a);
	passed("Swap and both rotations work with two nodes");
	stack_clear(&b);
	expect_stack(&a, NULL, 0);
	expect_stack(&b, NULL, 0);
	stack_clear(&a);
	passed("Clear resets both ends and size; clearing twice is safe");

	section("05 / Integer boundaries and reuse");
	stack_push(&a, checked_node(INT_MAX));
	stack_push(&a, checked_node(0));
	stack_push(&a, checked_node(INT_MIN));
	expect_stack(&a, (int[]){INT_MIN, 0, INT_MAX}, 3);
	assert(stack_is_sorted(&a));
	assert(stack_contains(&a, INT_MIN) && stack_contains(&a, INT_MAX));
	passed("INT_MIN, zero and INT_MAX sort and search correctly");
	stack_clear(&a);
	expect_stack(&a, NULL, 0);
	passed("A cleared stack can be populated and cleared again");
}

/* Executa todos os testes de stack e devolve sucesso ao sistema. */
int	main(void)
{
	g_color = isatty(STDOUT_FILENO) && getenv("NO_COLOR") == NULL;
	puts("\n  +------------------------------------------------+");
	puts("  |           PUSH_SWAP / STACK TESTS               |");
	puts("  |                    ppoco                       |");
	puts("  +------------------------------------------------+");
	puts("  Checking values, sizes and links in both directions.");
	puts("  A failed assertion stops the run at its source line.");
	fflush(stdout);
	test_empty_and_single();
	test_operations();
	puts("\n  ------------------------------------------------");
	printf("  %sAll %d test groups passed.%s\n\n",
		g_color ? "\033[1;32m" : "", g_passed,
		g_color ? "\033[0m" : "");
	return (0);
}
