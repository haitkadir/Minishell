#include "../../minishell.h"

char	is_operator(t_token *token)
{
	return ((token->token == RED_IN)
		|| (token->token == RED_OUT)
		|| (token->token == RED_APPEND)
		|| (token->token == HERE_DOC)
		|| (token->token == PIPE));
}

char	process_data(t_shell **shell, t_token *token, t_env *env)
{
	char	is_cmd;

	is_cmd = 0;
	*shell = NULL;
	while (token)
	{
		if (!is_cmd && token->token == WORD)
		{
			is_cmd = !is_cmd;
			printf("######################## CMD #########################\n");
			get_cmd(shell, env, &token);
			continue;
		}
		else if (is_operator(token))
		{
			is_cmd = 0;
			printf("######################## OPERATOR #########################\n");
			process_operator(shell, &token);
		}
		if (token)
			token = token->next;
	}
	return 0;
}