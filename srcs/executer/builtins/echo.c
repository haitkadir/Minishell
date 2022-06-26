/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:19:33 by            #+#    #+#             */
/*   Updated: 2022/05/27 18:19:36 by           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	printing_echo(char	**str, int i)
{
	if (!ft_strcmp("$?", str[i]))
	{
		if (str[i + 1] != NULL)
			printf("%d ", status.exit_status);
		else
			printf("%d", status.exit_status);
		status.exit_status = 0;
	}
	else
	{
		if (str[i + 1] != NULL)
			printf("%s ", str[i]);
		else
			printf("%s", str[i]);
	}
}

int	flag_option(t_env *env, char **str, int j, int i)
{
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '-' && j == 0)
				j++;
			else if (str[i][j] != 'n')
			{
				while (str[i])
				{
					printing_echo(str, i);
					i++;
				}
				return (1);
			}
			else if (str[i][j] == 'n')
				j++;
		}
		i++;
	}
	return (0);
}

void	no_flag(char	**str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!ft_strcmp("$?", str[i]))
		{
			if (str[i + 1] != NULL)
				printf("%d ", status.exit_status);
			else
				printf("%d", status.exit_status);
			status.exit_status = 0;
		}
		else
		{
			if (str[i + 1] != NULL)
				printf("%s ", str[i]);
			else
				printf("%s", str[i]);
		}
		i++;
	}
}

void	echo_env1(t_env *env, char **str)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!str[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (str[1][0] == '-' && str[1][1] == 'n')
	{
		if (flag_option(env, str, j, i))
			return ;
	}
	no_flag(str);
	write(1, "\n", 1);
}
