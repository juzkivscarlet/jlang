#ifndef ASM_H
#define ASM_H

#include "ast.h"

char*	asmf(_ast* ast);
char*	asmf_assignment(_ast* ast);
char*	asmf_call(_ast* ast);
char*	asmf_compound(_ast* ast);
char*	asmf_int(_ast* ast);
char*	asmf_var(_ast* ast);

#endif

