#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

typedef struct PARSER_STRUCT
{
	_lexer* lexer;
	_token* token;
} _parser;
_parser* init_parser(_lexer* l);

_ast*	parse(_parser* p);
_ast*	pblock(_parser* p);
_ast*	pcompound(_parser* p);
_token*	peat(_parser* p, int type);
_ast*	pexpr(_parser* p);
_ast*	pid(_parser* p);
_ast*	pint(_parser* p);
_ast*	plist(_parser* p);

#endif

