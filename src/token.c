#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/token.h"

_token* init_token(char* value, int type)
{
	_token* t 	= calloc(1, sizeof(struct TOKEN_STRUCT));
	t->value	= value;
	t->type		= type;

	return t;
};

char* t_tostr(_token* t)
{
	const char* type_str	= ttype_tostr(t->type);
	const char* templ		= "<type=%s, int_type=%d, value='%s'>";
	char* str				= calloc(strlen(type_str) + strlen(templ) + 8, sizeof(char));
	sprintf(str, templ, type_str, t->type, t->value);
	
	return str;
};

const char* ttype_tostr(int type)
{
	switch (type)
	{
		case TOKEN_ID:				return "TOKEN_ID";
		case TOKEN_AMPERSAND:		return "TOKEN_AMPERSAND";
		case TOKEN_APOSTROPHE:		return "TOKEN_APOSTROPHE";
		case TOKEN_ASTERISK:		return "TOKEN_ASTERISK";
		case TOKEN_ATSIGN:			return "TOKEN_ATSIGN";
		case TOKEN_BSLASH:			return "TOKEN_BSLASH";;
		case TOKEN_CARROT:			return "TOKEN_CARROT";
		case TOKEN_COLON:			return "TOKEN_COLON";
		case TOKEN_COMMA:			return "TOKEN_COMMA";
		case TOKEN_DOLLAR:			return "TOKEN_DOLLAR";
		case TOKEN_EOF:				return "TOKEN_EOF";
		case TOKEN_EQUALS:			return "TOKEN_EQUALS";
		case TOKEN_EPOINT:			return "TOKEN_EPOINT";
		case TOKEN_FSLASH:			return "TOKEN_FSLASH";
		case TOKEN_GREATERTHAN:		return "TOKEN_GREATERTHAN";
		case TOKEN_HYPHEN:			return "TOKEN_HYPHEN";
		case TOKEN_INT:				return "TOKEN_INT";
		case TOKEN_LBRACE:			return "TOKEN_LBRACE";
		case TOKEN_LBRACKET:		return "TOKEN_LBRACKET";
		case TOKEN_LESSTHAN:		return "TOKEN_LESSTHAN";
		case TOKEN_LPAREN:			return "TOKEN_LPAREN";
		case TOKEN_PERCENT:			return "TOKEN_PERCENT";
		case TOKEN_PERIOD:			return "TOKEN_PERIOD";
		case TOKEN_PIPE:			return "TOKEN_PIPE";
		case TOKEN_PLUS:			return "TOKEN_PLUS";
		case TOKEN_POUND:			return "TOKEN_POUND";
		case TOKEN_QMARK:			return "TOKEN_QMARK";
		case TOKEN_QUOTE:			return "TOKEN_QUOTE";
		case TOKEN_RARROW:			return "TOKEN_RARROW";
		case TOKEN_RBRACE:			return "TOKEN_RBRACE";
		case TOKEN_RBRACKET:		return "TOKEN_RBRACKET";
		case TOKEN_RPAREN:			return "TOKEN_RPAREN";
		case TOKEN_SEMICOLON:		return "TOKEN_SEMICOLON";
		case TOKEN_TICK:			return "TOKEN_TICK";
		case TOKEN_TILDE:			return "TOKEN_TILDE";
		case TOKEN_UNDERSCORE:		return "TOKEN_UNDERSCORE";
	}

	return "not_stringable";
};

