#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT
{
	char*	value;
	enum
	{
		TOKEN_AMPERSAND,
		TOKEN_APOSTROPHE,
		TOKEN_ASTERISK,
		TOKEN_ATSIGN,
		TOKEN_BSLASH,
		TOKEN_CARROT,
		TOKEN_COLON,
		TOKEN_COMMA,
		TOKEN_DOLLAR,
		TOKEN_EOF,
		TOKEN_EQUALS,
		TOKEN_EPOINT,
		TOKEN_FSLASH,
		TOKEN_GREATERTHAN,
		TOKEN_HYPHEN,
		TOKEN_ID,
		TOKEN_INT,
		TOKEN_LBRACE,
		TOKEN_LBRACKET,
		TOKEN_LESSTHAN,
		TOKEN_LPAREN,
		TOKEN_PERCENT,
		TOKEN_PERIOD,
		TOKEN_PIPE,
		TOKEN_PLUS,
		TOKEN_POUND,
		TOKEN_QMARK,
		TOKEN_QUOTE,
		TOKEN_RARROW,
		TOKEN_RBRACE,
		TOKEN_RBRACKET,
		TOKEN_RPAREN,
		TOKEN_SEMICOLON,
		TOKEN_TICK,
		TOKEN_TILDE,
		TOKEN_UNDERSCORE
	} type;
} _token;
_token*		init_token(char* value, int type);

char*		t_tostr(_token* t);
const char*	ttype_tostr(int type);

#endif

