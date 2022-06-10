#include "../lexer.h"







t_token *lexer(char *line)
{
	if (check_errors(line))
		return (NULL);
	return (tokennew("hello", 5));
}
