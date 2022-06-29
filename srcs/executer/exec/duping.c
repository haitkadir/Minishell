/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:08:23 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_dup(t_shell *shell, t_arg *arg, int j)
{
	int	fd;

	fd = 0;
	if (j == 1)
	{
		if (shell->prev && shell->prev->token == RED_OUT)
		{
			fd = shell->prev->file;
			dup2(fd, 1);
			dup2(arg->in_fd, 0);
			close(arg->fd[1]);
		}
		else
		{
			dup2(arg->fd[1], 1);
			dup2(arg->in_fd, 0);
			close(arg->fd[1]);
		}
	}
	else if (j == 0)
	{
		if (shell->prev && shell->prev->token == RED_OUT)
		{
			fd = shell->prev->file;
			dup2(fd, 1);
			dup2(arg->in_fd, 0);
			close(arg->fd[1]);
		}
		else
		{
			dup2(arg->in_fd, 0);
			close(arg->fd[1]);
		}
	}
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
