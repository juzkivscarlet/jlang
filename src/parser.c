#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/parser.h"
#include "include/types.h"

_parser* init_parser(_lexer* l)
{
	_parser* p	= calloc(1, sizeof(struct PARSER_STRUCT));
	p->lexer	= l;
	p->token	= lnext_token(l);

	return p;
};

_ast* parse(_parser* p)
{
	return pcompound(p);
};

_ast* pblock(_parser* p)
{
	peat(p, TOKEN_LBRACE);
	_ast* ast = init_ast(AST_COMPOUND);
	while (p->token->type != TOKEN_RBRACE)
	{
		list_push(ast->children, pexpr(p));
	};
	peat(p, TOKEN_RBRACE);

	return ast;
};

_ast* pcompound(_parser* p)
{
	_ast* ast	= init_ast(AST_COMPOUND);
	unsigned int should_close	= 0;
	if (p->token->type == TOKEN_LBRACE)
	{
		peat(p, TOKEN_LBRACE);
		should_close = 1;
	};

	while ((p->token->type != TOKEN_EOF) && (p->token->type != TOKEN_RBRACE))
	{
		list_push(ast->children, pexpr(p));
		if (p->token->type == TOKEN_SEMICOLON)
			peat(p, TOKEN_SEMICOLON);
	};

	if (p->token->type == TOKEN_RBRACE)
		peat(p, TOKEN_RBRACE);
	return ast;
};

_token* peat(_parser* p, int type)
{
	if (p->token->type != type)
	{
		printf("[Parser]: unexpected token:\t `%s` \n\t...was expecting:\t `%s` \n", 
				t_tostr(p->token), ttype_tostr(type));
		exit(1);
	}

	p->token	= lnext_token(p->lexer);
	return p->token;
};

_ast* pexpr(_parser* p)
{
	switch (p->token->type)
	{
		case TOKEN_ID:		return pid(p);
		case TOKEN_INT:		return pint(p);
		case TOKEN_LPAREN:	return plist(p);

		default:
		{
			printf("[Parser]: unexpected token '%s' \n", t_tostr(p->token));
			exit(1);
		};
	};
};

_ast* pid(_parser* p)
{
	char* value	= calloc((strlen(p->token->value)+1), sizeof(char));
	strcpy(value, p->token->value);
	peat(p, TOKEN_ID);

	if (p->token->type == TOKEN_EQUALS)
	{
		peat(p, TOKEN_EQUALS);
		_ast* ast	= init_ast(AST_ASSIGNMENT);
		ast->name	= value;
		ast->value	= pexpr(p);

		return ast;
	};

	_ast* ast	= init_ast(AST_VAR);
	ast->name	= value;
	if (p->token->type == TOKEN_COLON)
	{
		peat(p, TOKEN_COLON);
		while (p->token->type == TOKEN_ID)
		{
			ast->datatype		+= type_toint(p->token->value);
			peat(p, TOKEN_ID);
			if (p->token->type == TOKEN_LESSTHAN)
			{
				peat(p, TOKEN_LESSTHAN);
				ast->datatype	+= type_toint(p->token->value);
				peat(p, TOKEN_ID);
				peat(p, TOKEN_GREATERTHAN);
			};
		};
	} else
	{
		if (p->token->type == TOKEN_LPAREN)
		{
			ast->type		= AST_CALL;
			ast->children	= plist(p);
		};	
	};

	return ast;
};

_ast* pint(_parser* p)
{
	_ast* ast		= init_ast(AST_INT);
	int int_value	= atoi(p->token->value);
	peat(p, TOKEN_INT);
	ast->int_value	= int_value;

	return ast;
};

_ast* plist(_parser* p)
{
	peat(p, TOKEN_LPAREN);
	_ast* ast	= init_ast(AST_COMPOUND);
	list_push(ast->children, pexpr(p));
	while (p->token->type == TOKEN_COMMA)
	{
		peat(p, TOKEN_COMMA);
		list_push(ast->children, pexpr(p));
	};
	peat(p, TOKEN_RPAREN);

	if (p->token->type == TOKEN_COLON)
	{
		peat(p, TOKEN_COLON);
		while (p->token->type == TOKEN_ID)
		{
			ast->datatype		= type_toint(p->token->value);
			peat(p, TOKEN_ID);
			if (p->token->type == TOKEN_LESSTHAN)
			{
				peat(p, TOKEN_LESSTHAN);
				ast->datatype	+= type_toint(p->token->value);
				peat(p, TOKEN_ID);
				peat(p, TOKEN_GREATERTHAN);
			};
		};
	};

	if (p->token->type == TOKEN_RARROW)
	{
		peat(p, TOKEN_RARROW);
		ast->type	= AST_FUNC;
		ast->value	= pcompound(p);
	};

	return ast;
};

