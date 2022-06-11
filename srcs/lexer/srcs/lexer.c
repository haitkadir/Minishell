#include "../lexer.h"







t_token *lexer(char *line)
{
	t_token	*shell;

	shell = NULL;
	if (check_errors(line))
		return (NULL);
	if (tokenizer(shell, line))
		return (NULL);
	return (tokennew("hello", 5));
}
