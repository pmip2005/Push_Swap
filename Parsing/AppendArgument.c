#include "Parsing.h"

/* Split one argument on whitespace and append each token in order. */
/* Return 1 on success, 0 on failure, including an empty argument. */
/* On failure, earlier tokens may already be in A; the caller clears A. */
int	append_argument(t_stack *a, const char *argument)
{
	/* Declare scan indices, a token pointer and a token count. */
	/* Starting at index zero, repeat until the argument ends: */
	/* Skip whitespace: a space or a character from 9 through 13. */
	/* If the argument ended after skipping whitespace, stop. */
	/* Save the token start, then scan until whitespace or the end. */
	/* Allocate token length + 1 bytes; return 0 if allocation fails. */
	/* Copy the token and add its terminating null byte. */
	/* Pass the token to append_token. */
	/* Free the temporary token on BOTH success and failure. */
	/* If append_token failed, return 0; otherwise count the token. */
	/* After the loop, return 1 only if at least one token was added. */
	/* Do not modify argument or print errors here. */
}
