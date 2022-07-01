/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:05:20 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:05:22 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	unset_utils(t_env **env, t_env *lst, char *find)
{
	t_env	*tmp;

	tmp = NULL;
	lst = *env;
	while (lst)
	{
		if (!ft_strncmp(lst->key, find, ft_strlen(lst->key)))
		{
			if (!tmp)
			{
				tmp = lst->next;
				free(lst);
				*env = tmp;
				return ;
			}
			tmp->next = lst->next;
			free(lst);
			break ;
		}
		tmp = lst;
		lst = lst->next;
	}
}

void	unset_env(t_env **env, char **str)
{
	t_env	*lst;
	t_env	*tmp;
	int		i;

	lst = NULL;
	i = 1;
	while (str[i])
	{
		unset_utils(env, lst, str[i]);
		i++;
	}
	status.exit_status = 0;
}
