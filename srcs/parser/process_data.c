#include "../../minishell.h"

// char	is_prev_operator(t_token *token)
// {
// 	if (token->prev)
// 	{
// 		return ((token->prev->token == RED_IN)
// 			|| (token->prev->token == RED_OUT)
// 			|| (token->prev->token == HERE_DOC));
// 	}
// 	return (0);
// }

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
			get_cmd(shell, env, &token);
			continue;
		}
		else if (is_operator(token))
		{
			is_cmd = 0;
			printf("operator\n");
		}
		if (token)
			token = token->next;
	}
	return 0;
}