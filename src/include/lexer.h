#ifndef LEXER_H_
#define LEXER_H_

/*
 * Header file with token structure
 */
#include "token.h"

/*
 * For integer types with fixed lengths
 */
#include <stdint.h>
#include "attr.h"
/*
 * Lexer structure, u don't need really know what is this
 */
typedef struct
{
	uint32_t mem[0]
} lexer_t;

/*
 * Function returns a pointer to real lexer structure
 * First argument is pointer to source string, which ends with '\0' - symbol
 */
extern "C" lexer_t *new_lexer (const char *__src);

/*
 * Free memory from lexer structure function
 */
extern "C" void free_lexer (lexer_t *__lex);

/*
 * Lexer interface have only one function, which aim is serching tokens in input string
 * I called it scan
 * first argument is pointer to real lexer structure
 * At the end of input string it returns a token_t value with type = CTRL_SYMBOL and sym = '\0'
 * As result token_t value == 0
 */
extern "C" token_t scan (lexer_t *__lex);


#endif // LEXER_H_
