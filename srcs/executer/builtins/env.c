/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:23:50 by sahafid           #+#    #+#             */
/*   Updated: 2022/06/02 20:23:51 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
extern t_global status;

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
		status.exit_status = 0;
	}
	if (i == 0)
	{
		printf("env not set\n");
		status.exit_status = 1;
		return ;
	}
}
