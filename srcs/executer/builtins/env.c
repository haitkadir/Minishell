/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:23:50 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 21:23:48 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	env(t_env *env)
{
	int		i;
	int		j;
	t_env	*lst;

	i = 0;
	j = 0;
	lst = env;
	while (lst)
	{
		if (lst->value == NULL)
			j++;
		else
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
		i++;
		g_status.exit_status = 0;
	}
	if (i == 0)
	{
		ft_putstr_fd("env not set\n", 2);
		g_status.exit_status = 1;
		return ;
	}
}
