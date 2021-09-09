#include <stdlib.h>
#include <string.h>

#include "include/lexer.h"
#include "include/macros.h"

_lexer* init_lexer(char* src)
{
	_lexer* l = calloc(1, sizeof(struct LEXER_STRUCT));
	l->src = src;
	l->size = strlen(src);
	l->i = 0;
	l->c = src[l->i];

	return l;
};

void ladvance(_lexer* l)
{
	if ((l->i < l->size) && (l->c != '\0'))
	{
		l->i += 1;
		l->c = l->src[l->i];
	};
};

_token* ladvance_current(_lexer* l, int type)
{
	char* value = calloc(2, sizeof(char));
	value[0] = l->c;
	value[1] = '\0';
	
	_token* t = init_token(value, type);
	ladvance(l);
	
	return t;
};

_token* ladvance_with(_lexer* l, _token* t)
{
	ladvance(l);
	return t;
};

_token* lnext_token(_lexer* l)
{
	while (l->c != '\0')
	{
		lskip_whitespace(l);
		if (isalnum(l->c))
			return lparse_id(l);
		
		if (isdigit(l->c))
			return lparse_number(l);

		switch (l->c)
		{
			case '=':
			{
				if (peek(l, 1) == '>')
					return ladvance_with(l, ladvance_with(l, init_token("=>", TOKEN_RARROW)));
				return ladvance_with(l, init_token('=', TOKEN_EQUALS));
			} break;

			case '&':	return ladvance_current(l, TOKEN_AMPERSAND);
			case '\'':	return ladvance_current(l, TOKEN_APOSTROPHE);
			case '*':	return ladvance_current(l, TOKEN_ASTERISK);
			case '@':	return ladvance_current(l, TOKEN_ATSIGN);
			case '\\':	return ladvance_current(l, TOKEN_BSLASH);
			case '^':	return ladvance_current(l, TOKEN_CARROT);
			case ':':	return ladvance_current(l, TOKEN_COLON);
			case ',':	return ladvance_current(l, TOKEN_COMMA);
			case '$':	return ladvance_current(l, TOKEN_DOLLAR);
			case '!':	return ladvance_current(l, TOKEN_EPOINT);
			case '/':	return ladvance_current(l, TOKEN_FSLASH);
			case '>':	return ladvance_current(l, TOKEN_GREATERTHAN);
			case '-':	return ladvance_current(l, TOKEN_HYPHEN);
			case '[':	return ladvance_current(l, TOKEN_LBRACKET);
			case '{':	return ladvance_current(l, TOKEN_LBRACE);
			case '(':	return ladvance_current(l, TOKEN_LPAREN);
			case '<':	return ladvance_current(l, TOKEN_LESSTHAN);
			case '%':	return ladvance_current(l, TOKEN_PERCENT);
			case '.':	return ladvance_current(l, TOKEN_PERIOD);
			case '|':	return ladvance_current(l, TOKEN_PIPE);
			case '+':	return ladvance_current(l, TOKEN_PLUS);
			case '#':	return ladvance_current(l, TOKEN_POUND);
			case '}':	return ladvance_current(l, TOKEN_RBRACE);
			case ']':	return ladvance_current(l, TOKEN_RBRACKET);
			case ')':	return ladvance_current(l, TOKEN_RPAREN);
			case ';':	return ladvance_current(l, TOKEN_SEMICOLON);
			case '`':	return ladvance_current(l, TOKEN_TICK);
			case '~':	return ladvance_current(l, TOKEN_TILDE);
			case '_':	return ladvance_current(l, TOKEN_UNDERSCORE);

			case '\0':	break;
			default:
			{
				printf("[Lexer]: unexpected character: '%c' \n", l->c);
				exit(1);
				break;
			}
		}
	}

	return init_token(0, TOKEN_EOF);
};

void lskip_whitespace(_lexer* l)
{
	while ((l->c == 13) || (l->c == 10) || (l->c == ' ') || (l->c == '\t'))
		ladvance(l);
};

_token* lparse_id(_lexer* l)
{
	char* value = calloc(1, sizeof(char));
	while (isalnum(l->c))
	{
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char[]){l->c, 0});
		ladvance(l);
	}

	return init_token(value, TOKEN_ID);
};

_token* lparse_number(_lexer* l)
{
	char* value = calloc(1, sizeof(char));
	while (isdigit(l->c))
	{
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char[]){l->c, 0});
		ladvance(l);
	}
	
	return init_token(value, TOKEN_INT);
};

char peek(_lexer* l, int offset)
{
	return l->src[MIN(l->i + offset, l->size)];
};

