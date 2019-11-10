#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdint.h>

/*
 * Symbol types:
 * SYMBOL is usual symbol like 'a' or '/', as well escape symbols have SYMBOL type
 * CTRL_SYMBOL is brackets and other operators of the regular expressions
 */

enum {CTRL_SYMBOL = 0, SYMBOL};

/*
 * Token structure:
 * in regexp we have only symbols, hence token structure is unsigned int type, where
 * HIGHER bit is type of the symbol (SYMBOL, CTRL_SYMBOL) and other bits is char code
 */

typedef struct
{
	uint32_t type:1;
	uint32_t sym:31;
} token_t;

#endif // TOKEN_H_
