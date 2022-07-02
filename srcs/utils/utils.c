/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:06:58 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/30 16:07:00 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtins(char *str)
{
	if (!ft_strcmp_tl(str, "pwd"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp_tl(str, "env"))
		return (1);
	else if (!ft_strcmp(str, "exit"))
		return (1);
	else if (!ft_strcmp_tl(str, "cd"))
		return (1);
	else if (!ft_strcmp_tl(str, "echo"))
		return (1);
	return (0);
}

void	put_error(char *keyword, char *msg, int err)
{
	ft_putstr_fd("\033[4;31mMinishell\033[0m: ", 2);
	ft_putstr_fd(keyword, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	g_status.exit_status = err;
}
