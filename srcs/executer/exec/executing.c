/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 16:12:44 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	cmd_exec(t_env	**env, t_arg *arg, t_shell *shell)
{
	pipe(arg->fd);
	if (arg->not_found == 0)
	{
		if (cmd_token(shell, arg, env))
			return (1);
	}
	if (arg->in_fd != 0)
		close(arg->in_fd);
	arg->in_fd = arg->fd[0];
	close(arg->fd[1]);
	return (0);
}

int	her_doc_exec(t_shell *shell, t_arg *arg)
{
	int	id;
	int	rs;

	id = her_doc(shell, arg);
	waitpid(id, &rs, 0);
	status.signals = 1;
	if (rs != 0)
		return (1);
	arg->in_fd = open("tmp", O_RDONLY, 0777);
	return (0);
}

void	check_command(t_env	**env, t_arg *arg, t_shell *shell)
{
	arg->in_fd = 0;
	arg->not_found = 0;
	if (one_cmd(env, arg, shell))
		return ;
	while (shell)
	{
		if (shell->token == CMD)
		{
			if (cmd_exec(env, arg, shell))
				return ;
		}
		else if (shell->token == RED_IN)
			arg->in_fd = shell->file;
		else if (shell->token == INVALID_FILE)
			arg->not_found = 1;
		else if (shell->token == HERE_DOC)
		{
			if (her_doc_exec(shell, arg))
				return ;
		}
		else if (shell->token == PIPE)
			arg->not_found = 0;
		shell = shell->next;
	}
	unlink("tmp");
}
