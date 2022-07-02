/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:08:23 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	her_doc_logic(char	*str, int fd, t_shell *shell)
{
	while (1)
	{
		str = readline("herdoc> ");
		if (!ft_strcmp(str, shell->data))
		{
			free(str);
			close(fd);
			exit(0);
		}
		else if (!str)
		{
			close(fd);
			exit(1);
		}
		else
		{
			ft_putstr_fd(str, fd);
			ft_putstr_fd("\n", fd);
			free(str);
			str = NULL;
		}
	}
}

int	her_doc(t_shell *shell, t_arg *arg)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	status.signals = fork();
	if (status.signals == 0)
	{
		her_doc_logic(str, fd, shell);
		close(fd);
		write(1, "\n", 1);
		exit(0);
	}
	else
		return (status.signals);
}
