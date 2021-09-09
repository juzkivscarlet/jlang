#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/asm.h"

char* asmf(_ast* ast)
{
	char* value = calloc(1, sizeof(char));
	char* next_value = 0;
	
	switch (ast->type)
	{
		case AST_ASSIGNMENT:
		{
			next_value = asmf_assignment(ast);
			break;
		};

		case AST_CALL:
		{
			next_value = asmf_call(ast);
			break;
		};
		
		case AST_COMPOUND:
		{
			next_value = asmf_compound(ast);
			break;
		};

		case AST_INT:
		{
			next_value = asmf_int(ast);
			break;
		};

		case AST_VAR:
		{
			next_value = asmf_var(ast);
			break;
		};

		default:
		{
			printf("[ASM frontend]: no frontend for ast of type '%d' \n", ast->type);
			exit(1);
		};

		break;
	};

	value = realloc(value, (strlen(next_value) + 1) * sizeof(char));
	strcat(value, next_value);
	return value;
};

char* asmf_assignment(_ast* ast)
{
	char* s = calloc(1, sizeof(char));
	if (ast->value->type == AST_FUNC)
	{
		const char* templ	= ".globl _start\n%s:\n";
		s = realloc(s, ((strlen(templ)+(2*strlen(ast->name))+1)*sizeof(char)));
		sprintf(s, templ, ast->name);

		_ast* asmval = ast->value;
		char* asmval_val = asmf(asmval->value);
		s = realloc(s, ((strlen(s)+strlen(asmval)+1)*sizeof(char)));
		strcat(s, asmval_val);
	};

	return s;
};

char* asmf_call(_ast* ast)
{
	char* s = calloc(1, sizeof(char));
	if (strcmp(ast->name, "return") == 0)
	{
		_ast* arg1 = (_ast*)ast->value->children->size ? ast->children->items[0] : (void*)0;
		const char* templ = "mov $%d, \%eax\n"
			"ret\n";
		const char* rets = calloc((strlen(templ) + 128), sizeof(char));
		sprintf(rets, templ, (arg1 ? arg1->int_value : 0));
		s = realloc(s, ((strlen(rets)+1)*sizeof(char)));
		strcat(s, rets);
	};

	return s;
};

char* asmf_compound(_ast* ast)
{
	if (strcmp(ast->name, "main") == 0)
	{
		const char* templ	= ".globl _start\n"
							"_start:\n";
		char* s = calloc((strlen(templ) + 1), sizeof(char));
		strcpy(s, templ);

		return s;
	};
	
	char* value = calloc(1, sizeof(char));
	for (int i = 0; i < (int)ast->children->size; i++)
	{
		_ast* child			= (_ast*)ast->children->items[i];
		char* next_value	= asmf(child);
		value = realloc(value, (strlen(next_value) + 1) * sizeof(char));
		strcat(value, next_value);
	};

	return value;
};

char* asmf_int(_ast* ast)
{

};

char* asmf_var(_ast* ast)
{

};

