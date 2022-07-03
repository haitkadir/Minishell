/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 17:51:25 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	no_pipe_case(t_shell *shell, t_arg *arg, int fd)
{
	if (shell->prev && shell->prev->token == RED_OUT)
	{
		fd = shell->prev->file;
		dup2(fd, 1);
		dup2(arg->in_fd, 0);
		if (arg->in_fd != 0)
			close(arg->in_fd);
		close(arg->fd[1]);
		close(arg->fd[0]);
	}
	else
	{
		dup2(arg->in_fd, 0);
		if (arg->in_fd != 0)
			close(arg->in_fd);
		close(arg->fd[1]);
		close(arg->fd[0]);
	}
}

void	pipe_case(t_shell *shell, t_arg *arg, int fd)
{
	if (shell->prev && shell->prev->token == RED_OUT)
	{
		fd = shell->prev->file;
		dup2(fd, 1);
		dup2(arg->in_fd, 0);
		if (arg->in_fd != 0)
			close(arg->in_fd);
		close(arg->fd[1]);
		close(arg->fd[0]);
	}
	else
	{
		dup2(arg->fd[1], 1);
		dup2(arg->in_fd, 0);
		if (arg->in_fd != 0)
			close(arg->in_fd);
		close(arg->fd[1]);
		close(arg->fd[0]);
	}
}

void	ft_dup(t_shell *shell, t_arg *arg, int j)
{
	int	fd;

	fd = 0;
	if (j == 1)
		pipe_case(shell, arg, fd);
	else if (j == 0)
		no_pipe_case(shell, arg, fd);
	else if (j == 2)
	{
		if (shell->prev && shell->prev->token == RED_OUT)
		{
			fd = shell->prev->file;
			dup2(fd, 1);
			dup2(arg->in_fd, 0);
		}
		else
			dup2(arg->in_fd, 0);
	}
}
