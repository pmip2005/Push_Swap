#ifndef PARSING_H
# define PARSING_H

# include <limits.h>
# include "../Stack Structure/StackStruct.h"

int	parse_int(const char *text, int *value);
int	append_token(t_stack *a, const char *text);
int	append_argument(t_stack *a, const char *argument);

#endif
