/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 17:16:35 by sahafid          ###   ########.fr       */
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
			exit(0);
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

int	her_doc(t_shell *shell)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open("/tmp/tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	g_status.signals = fork();
	if (g_status.signals == 0)
	{
		her_doc_logic(str, fd, shell);
		close(fd);
		write(1, "\n", 1);
		exit(0);
	}
	else
		return (g_status.signals);
}
