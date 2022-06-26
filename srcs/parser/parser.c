#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

static void print_node(t_shell *shell)
{
	int i;

	i = 0;
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

	token = lexer(line, env);
	if (!token)
		return (NULL);
	if (process_data(&shell, token, env))
		return (NULL);
	print_node(shell);
	return (shell);
}
