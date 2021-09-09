#include <stdio.h>
#include <stdlib.h>

#include "include/asm.h"
#include "include/io.h"
#include "include/jlang.h"
#include "include/lexer.h"
#include "include/parser.h"

void _compile(char* src)
{
	_lexer* l	= init_lexer(src);
	_parser* p	= init_parser(l);
	_ast* r		= parse(p);
	_token* t 	= 0;

	char* s		= asmf(r);
	printf("%s\n", s);
};

void _compilefile(const char* f)
{
	char* src = read_file(f);
	_compile(src);
	free(src);
};

