/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:55:07 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 17:54:52 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_one_cmd(t_shell *lst)
{
	while (lst)
	{
		if (lst->token == CMD)
		{
			if (check_builtins(lst->switchs[0]))
				return (0);
			else
				return (1);
		}
		lst = lst->next;
	}
	return (1);
}

int	execute_builting(t_shell *lst, t_arg *arg, t_env **env)
{
	while (lst)
	{
		if (lst->token == CMD && arg->not_found == 0)
		{
			ft_dup(lst, arg, 2);
			builtins(env, lst->switchs, arg);
			dup2(arg->in, 0);
			dup2(arg->out, 1);
			if (lst->prev && lst->prev->token == RED_OUT)
				close(lst->prev->file);
		}
		else if (lst->token == RED_IN)
			arg->in_fd = lst->file;
		else if (lst->token == HERE_DOC)
		{
			if (her_doc_exec(lst, arg))
				return (1);
		}
		else if (lst->token == INVALID_FILE)
			arg->not_found = 1;
		lst = lst->next;
	}
	return (1);
}

int	one_cmd(t_env	**env, t_arg *arg, t_shell *shell)
{
	int		i;
	t_shell	*lst;

	i = 0;
	lst = shell;
	arg->in = dup(STDIN_FILENO);
	arg->out = dup(STDOUT_FILENO);
	arg->in_fd = 0;
	while (lst)
	{
		if (lst->token == PIPE)
			i++;
		lst = lst->next;
	}
	if (i == 0)
	{
		lst = shell;
		if (check_one_cmd(lst))
			return (0);
		lst = shell;
		execute_builting(lst, arg, env);
		return (1);
	}
	return (0);
}
