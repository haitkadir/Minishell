/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:08:04 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 18:35:18 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	check_is_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return(1);
}

void	exit10(void)
{
	printf("exit\n");
	status.exit_status = 0;
	exit(0);
}

void	exit11(int i)
{
	if (check_is_digit(ft_itoa(i)))
	{
		printf("exit\n");
		status.exit_status = i;
		exit(i);
	}
	printf("exit\n");
	ft_putstr_fd("numeric argument required\n", 1);
	exit(255);
}
