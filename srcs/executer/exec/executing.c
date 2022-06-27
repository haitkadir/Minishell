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
	i = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (id == 0)
	{
		while (1)
		{
			str = readline("herdoc> ");
			if (!ft_strcmp(str, shell->data))
			{
				free(str);
				close(i);
				// break ;
				exit(0);
			}
			else if (!str)
			{
				close(i);
				// break ;
				exit(1);
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
		exit(0);
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
			waitpid(-1, &status, 0);
			if (!WIFEXITED(status))
				break ;
			if (status != 0)
				break ;
			arg->in_fd = open("tmp", O_RDONLY, 0777);
		}
		shell = shell->next;
	}
}
