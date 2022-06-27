/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:08:23 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	her_doc(t_shell *shell, t_arg *arg)
{
	int		i;
	int		id;
	char	*str;
	char	*tmp;

	id = fork();
	str = NULL;
	tmp = NULL;
	if (id == 0)
	{
		i = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC);
		while (1)
		{
			str = readline("<< ");
			if (!ft_strcmp(str, shell->data))
			{
				free(str);
				return ;
			}
			else if (!str)
			{
				close(i);
				exit(0);
				return ;
			}
			else
			{
				ft_putstr_fd(str, i);
				ft_putstr_fd("\n", i);
				free(str);
				str = NULL;
			}
		}
		close(i);
		exit(1);
	}
	return (id);
}

int	one_cmd(t_env	*env, t_arg *arg, t_shell *shell)
{
	int		i;
	t_shell	*lst;

	i = 0;
	lst = shell;
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
		if (lst && lst->token == RED_IN)
		{
			arg->in_fd = lst->file;
			lst = lst->next;
		}
		if (lst && lst->token == CMD && check_builtins(env, lst->switchs[0]))
		{
			ft_dup(lst, arg, 2);
			builtins(env, shell->switchs, arg);
			return (1);
		}

	}
	return (0);
}

void	check_command(t_env	*env, t_arg *arg, t_shell *shell)
{
	int	id;
	int	status;

	if (one_cmd(env, arg, shell))
		return ;
	while (shell)
	{
		if (shell->token == CMD)
		{
			if (cmd_token(shell, arg, env))
				return ;
			arg->in_fd = arg->fd[0];
			close(arg->fd[1]);
		}
		else if (shell->token == RED_IN)
			arg->in_fd = shell->file;
		else if (shell->token == HERE_DOC)
		{
			id = her_doc(shell, arg);
			waitpid(id, &status, NULL);
			if (status == 0)
				break ;
			arg->in_fd = open(".tmp", O_RDONLY);
		}
		shell = shell->next;
	}
}
