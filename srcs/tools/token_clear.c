#include "../../minishell.h"

void	token_clear(t_token **lst)
{
	t_token	*head;
	t_token	*current;

	if (!*lst)
		return ;
	head = *lst;
	*lst = NULL;
	while (head != NULL)
	{
		current = head;
		head = head->next;
		tokendelone(current);
	}
}
