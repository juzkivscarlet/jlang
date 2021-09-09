#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include "token.h"

typedef struct LEXER_STRUCT
{
	char 			c;
	unsigned int	i;
	char*			src;
	size_t			size;
} _lexer;
_lexer*	init_lexer(char* src);

void	ladvance(_lexer* l);
_token*	ladvance_current(_lexer* l, int type);
_token*	ladvance_with(_lexer* l, _token* t);
_token*	lnext_token(_lexer* l);
void	lskip_whitespace(_lexer* l);

_token*	lparse_id(_lexer* l);
_token*	lparse_number(_lexer* l);

char	peek(_lexer* l, int offset);

#endif

