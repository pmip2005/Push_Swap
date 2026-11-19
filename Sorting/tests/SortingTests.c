/* Test driver: stdout contains only the sorting instructions. */
#include "../Sorting.h"
#include <assert.h>
#include <errno.h>
#include <limits.h>

static int	parse_value(const char *text)
{
	char	*end;
	long	value;

	errno = 0;
	value = strtol(text, &end, 10);
	assert(errno == 0 && end != text && *end == '\0');
	assert(value >= INT_MIN && value <= INT_MAX);
	return ((int)value);
}

/* Sort a separate pointer array to establish the expected node order. */
static void	order_nodes(t_node **nodes, int count)
{
	t_node	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (nodes[i]->value > nodes[j]->value)
			{
				temp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	check_result(t_stack *a, t_stack *b, t_node **nodes, int count)
{
	t_node	*current;
	int		i;

	assert(b->size == 0 && b->top == NULL && b->bottom == NULL);
	assert(a->size == count && a->top == nodes[0]);
	assert(a->bottom == nodes[count - 1]);
	current = a->top;
	i = 0;
	while (i < count)
	{
		assert(current == nodes[i]);
		assert(current->above == (i ? nodes[i - 1] : NULL));
		assert(current->below == (i + 1 < count ? nodes[i + 1] : NULL));
		current = current->below;
		i++;
	}
	assert(current == NULL && stack_is_sorted(a));
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
	t_node	*nodes[5];
	int		i;

	assert(argc >= 4 && argc <= 6);
	stack_init(&a);
	stack_init(&b);
	i = 0;
	while (i < argc - 1)
	{
		nodes[i] = node_new(parse_value(argv[i + 1]));
		assert(nodes[i] != NULL);
		stack_push_bottom(&a, nodes[i]);
		i++;
	}
	order_nodes(nodes, argc - 1);
	if (argc == 4)
		sort_three(&a);
	else
		sort_five(&a, &b);
	check_result(&a, &b, nodes, argc - 1);
	stack_clear(&a);
	stack_clear(&b);
	assert(a.size == 0 && a.top == NULL && a.bottom == NULL);
	return (0);
}
