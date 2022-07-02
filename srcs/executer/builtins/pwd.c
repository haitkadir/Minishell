/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:19:40 by            #+#    #+#             */
/*   Updated: 2022/05/27 18:19:41 by           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*pwd(t_env *env, int i)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (!ft_strcmp(lst->key, "PWD"))
		{
			if (lst->value)
			{
				if (i == 1)
					printf("%s\n", lst->value);
				g_status.exit_status = 0;
				return (lst->value);
			}
			else
			{
				if (i == 1)
					printf("pwd is not set\n");
				g_status.exit_status = 1;
				return (NULL);
			}
		}
		lst = lst->next;
	}
	return (NULL);
}
