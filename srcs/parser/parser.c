#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

static void print_node(t_shell *shell)
{
	int i;

	if (shell)
	{
		while (shell)
		{
		printf("\n================Start======================\n");
			printf("| prev:%p:\n", shell->prev);
			printf("| token:%d:\n",shell->token);
			printf("| data:%s:\n",shell->data);
			if (shell->switchs)
			{
				i = 0;
				while (shell->switchs[i])
					printf("| switchs:%s:\n",shell->switchs[i++]);
			}
			printf("| fd:%d:\n",shell->file);
			printf("| next:%p:\n", shell->next);
			shell = shell->next;
		printf("=================End=======================\n");
		}
	}
}

/*----------------------------------------------------------------------------*/

t_shell *parser(char *line, t_env *env)
{
	t_token	*token;
	t_shell	*shell;
	t_arg args;

	args.paths = NULL;
	token = lexer(line, env);
	if (!token)
		return (NULL);
	if (process_data(&shell, token, env))
		return (NULL);
	token_clear(&token);
	// print_node(shell);
	check_command(env, &args, shell);
	return (shell);
}
