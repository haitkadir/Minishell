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

	str = NULL;
	tmp = NULL;
	i = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	status.signals = fork();
	if (status.signals == 0)
	{
		while (1)
		{
			str = readline("herdoc> ");
			if (!ft_strcmp(str, shell->data))
			{
				free(str);
				close(i);
				exit(0);
			}
			else if (!str)
			{
				close(i);
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
		write(1, "\n", 1);
		exit(0);
	}
	else
		return (status.signals);
}

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

int	one_cmd(t_env	*env, t_arg *arg, t_shell *shell)
{
	int		i;
	int		rs;
	int		id;
	int		in;
	int		out;
	t_shell	*lst;

	i = 0;
	lst = shell;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	arg->in_fd = 0;
	while (lst)
	{
		if (lst->token == PIPE)
			i++;
		lst = lst->next;
	}
	if (i == 0)
	{
		if (check_one_cmd(shell))
			return (0);
		lst = shell;
		while (lst)
		{
			if (lst->token == CMD)
			{
				if (check_builtins(lst->switchs[0]))
				{
					ft_dup(lst, arg, 2);
					builtins(env, lst->switchs, arg);
					dup2(in, 0);
					dup2(out, 1);
				}
				else
					return (0);
			}
			else if (lst->token == RED_IN)
				arg->in_fd = lst->file;
			else if (lst->token == HERE_DOC)
			{
				id = her_doc(lst, arg);
				waitpid(id, &rs, 0);
				if (rs != 0)
					return (1);
				arg->in_fd = open("tmp", O_RDONLY, 0777);
			}
			lst = lst->next;
		}
		return (1);
	}
	return (0);
}

void	check_command(t_env	*env, t_arg *arg, t_shell *shell)
{
	int	id;
	int	rs;

	arg->in_fd = 0;
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
			waitpid(id, &rs, 0);
			if (rs != 0)
				return ;
			arg->in_fd = open("tmp", O_RDONLY, 0777);
		}
		shell = shell->next;
	}
	unlink("tmp");
}
