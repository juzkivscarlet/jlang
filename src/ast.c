#include <stdlib.h>
#include "include/ast.h"

_ast* init_ast(int type)
{
	_ast* ast	= calloc(1, sizeof(struct AST_STRUCT));
	ast->type	= type;

	if (type == AST_COMPOUND)
		ast->children = init_list(sizeof(struct AST_STRUCT*));

	return ast;
};

