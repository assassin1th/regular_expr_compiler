#include <stdint.h> // unit8_t
#include <string.h> // strlen, strcmp (in test mode), memcpy
#include <stdlib.h> // malloc, free
#include "token.h" // token structure
#include "attr.h"

/*
 * Jump table for state machine
 */
static const char _jtab[1][128] =
{
	{
		1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2
	}
};
 
/* 
 * Real lexer structure
 */
typedef struct
{
	char *	peek;
	uint8_t	state;
	char 	src_string[0];
} _lexer_t;

/*
 * Production function, that return pointer to real lexer structure or NULL if not enought memory
 */
_lexer_t *new_lexer (const char *__src)
{
	size_t len = strlen (__src) + 1;
	_lexer_t *lex = (_lexer_t *) malloc (len + sizeof (_lexer_t));
	
	if (!lex)
		goto EXIT;

	lex->peek	= lex->src_string;
	lex->state	= 0;

	memcpy (lex->src_string, __src, len);
EXIT:
	return lex;
}

void free_lexer (_lexer_t *__lex)
{
	free (__lex);
}
	
/*
 * I use state machine handler for src string
 * Start state is 0
 * If we got '\' as symbol on starting state it move to 1 state and parse continued
 * If we got any symbol in 1 state function return token_t value with value.type = SYMBOL and
 * value.sym = char_code
 * If we got non operator symbol in 0 state, then function return token_t value with value.type = SYMBOL and
 * value.sym = char_code
 * If we got operator symbol in 0 state, then function return token_t value with value.type = CTRL_SYMBOL and
 * value.sym = char_code
 */
inline static void _next_state (_lexer_t *__lex) _inline
{
	__lex->state = _jtab[__lex->state][*(__lex->peek)];
}

token_t scan (_lexer_t *lex)
{
	register token_t token = {0};
	while (*(lex->peek) != '\0')
		switch (lex->state)
		{
			case 0:
				_next_state (lex);
				break;
			case 1:
				token.type 	= CTRL_SYMBOL;
				token.sym 	= *(lex->peek++);
				goto EXIT;
			case 2:
				token.type	= SYMBOL;
				token.sym 	= *(lex->peek++);
				goto EXIT;
		}
EXIT:
	lex->state = 0;
	return token;
}

#ifdef TEST
#include <stdio.h>

int main (int argc, char *argv[])
{
	if (argc != 2)
		return 0;

	char scan_res[strlen (argv[1]) + 1];

	char *res	= scan_res;
	token_t tok	= {0};
	_lexer_t *lex	= new_lexer (argv[1]);
	
	for (;; ++res)
	{
		tok = scan (lex);

		*res = tok.sym;
		if (*res == '\0')
			break;

		switch (tok.type)
		{
			case SYMBOL:
				printf ("SYMBOL, ");
				break;
			case CTRL_SYMBOL:
				printf ("CTRL_SYMBOL, ");
				break;
		}

		printf ("%c\n", *res);
	}

	free_lexer (lex);

	return strcmp (scan_res, argv[1]);
}
#endif // TEST
