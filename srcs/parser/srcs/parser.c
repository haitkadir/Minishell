#include "../parser.h"

/*----------------------------------------------------------------------------*/

t_shell *parser(char *line, t_env *env)
{
	t_token	*token;
	t_shell	*shell;

	token = lexer(line, env);
	if (!token)
		return (NULL);
	if (process_data(&shell, token, env))
		return (NULL);
	return (shell);
}
