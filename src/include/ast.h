#ifndef AST_H
#define AST_H

#include "list.h"

typedef struct AST_STRUCT
{
	enum 
	{
		AST_ASSIGNMENT,
		AST_CALL,
		AST_COMPOUND,
		AST_FUNC,
		AST_FUNC_DEF,
		AST_INT,
		AST_NOOP,
		AST_STATEMENT,
		AST_TYPE,
		AST_VAR
	} type;

	_list*				children;
	int					datatype;
	int					int_value;
	char*				name;
	struct AST_STRUCT*	value;
} _ast;
_ast*	init_ast(int type);

#endif

