#include "../../minishell.h"

void	shell_clear(t_shell **shell)
{
	t_shell	*head;
	t_shell	*current;

	if (!*shell)
		return ;
	head = *shell;
	*shell = NULL;
	while (head != NULL)
	{
		current = head;
		head = head->next;
		shelldelone(current);
	}
}
