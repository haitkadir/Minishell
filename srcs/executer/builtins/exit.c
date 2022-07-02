/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:08:04 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 20:33:25 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	exit10(void)
{
	printf("exit\n");
	g_status.exit_status = 0;
	exit(0);
}

void	exit11(char *ptr)
{
	if (check_is_digit(ptr))
	{
		printf("exit\n");
		g_status.exit_status = ft_atoi(ptr);
		exit(ft_atoi(ptr));
	}
	printf("exit\n");
	ft_putstr_fd("numeric argument required\n", 1);
	exit(255);
}
