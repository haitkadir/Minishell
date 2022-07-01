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

int	execute_builting(t_shell *lst, t_arg *arg, int rs, t_env **env)
{
	int	id;

	while (lst)
	{
		if (lst->token == CMD && arg->not_found == 0)
		{
			ft_dup(lst, arg, 2);
			builtins(env, lst->switchs, arg);
			dup2(arg->in, 0);
			dup2(arg->out, 1);
		}
		else if (lst->token == RED_IN)
			arg->in_fd = lst->file;
		else if (lst->token == HERE_DOC)
		{
			id = her_doc(lst, arg);
			waitpid(id, &rs, 0);
			status.signals = 1;
			if (rs != 0)
				return (1);
			arg->in_fd = open("tmp", O_RDONLY, 0777);
		}
		else if (shell->token == INVALID_FILE)
			arg->not_found = 1;
		lst = lst->next;
	}
	return (1);
}

int	one_cmd(t_env	**env, t_arg *arg, t_shell *shell)
{
	int		i;
	int		rs;
	int		in;
	int		out;
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
		if (check_one_cmd(shell))
			return (0);
		lst = shell;
		execute_builting(lst, arg, rs, env);
		return (1);
	}
	return (0);
}

void	check_command(t_env	**env, t_arg *arg, t_shell *shell)
{
	int	id;
	int	rs;

	arg->in_fd = 0;
	arg->not_found = 0;
	if (one_cmd(env, arg, shell))
		return ;
	while (shell)
	{
		if (shell->token == CMD)
		{
			pipe(arg->fd);
			if (arg->not_found == 0)
			{
				if (cmd_token(shell, arg, env))
					return ;
			}
			if (arg->in_fd != 0)
				close(arg->in_fd);
			arg->in_fd = arg->fd[0];
			close(arg->fd[1]);
		}
		else if (shell->token == RED_IN)
			arg->in_fd = shell->file;
		else if (shell->token == INVALID_FILE)
			arg->not_found = 1;
		else if (shell->token == HERE_DOC)
		{
			id = her_doc(shell, arg);
			waitpid(id, &rs, 0);
			status.signals = 1;
			if (rs != 0)
				return ;
			arg->in_fd = open("tmp", O_RDONLY, 0777);
		}
		else if (shell->token == PIPE)
			arg->not_found = 0;
		shell = shell->next;
	}
	unlink("tmp");
}
