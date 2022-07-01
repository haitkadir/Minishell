/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:05:59 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:06:00 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_export(char	**keys, int i)
{
	i = 0;
	while (keys[i])
	{
		free(keys[i]);
		i++;
	}
	free(keys);
}

void	print_export(char	**keys, t_env *sort, int i)
{
	t_env	*lst;

	i = 0;
	while (keys[i])
	{
		lst = sort;
		while (sort)
		{
			if (!ft_strcmp(keys[i], lst->key))
			{
				if (lst->value == NULL)
					printf("declare -x %s\n", keys[i]);
				else
					printf("declare -x %s=\"%s\"\n", keys[i], lst->value);
				break ;
			}
			lst = lst->next;
		}
		i++;
	}
	status.exit_status = 0;
	free_export(keys, i);
}

void	compare_keys(char	**keys, int i)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	i = 0;
	while (keys[i])
	{
		j = 0;
		while (keys[j])
		{
			if (ft_strcmp(keys[j], keys[i]) > 0)
			{
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	filling_keys(t_env *lst, char	**keys)
{
	t_env	*sort;
	int		i;

	i = 0;
	sort = lst;
	while (sort)
	{
		if (sort->key != NULL)
			keys[i] = ft_strdup(sort->key);
		else
			keys[i] = NULL;
		i++;
		sort = sort->next;
	}
	sort = lst;
	keys[i] = NULL;
}

void	sorted_env(t_env *lst, t_arg *arg)
{
	t_env	*sort;
	char	**keys;
	int		i;

	i = 0;
	sort = lst;
	while (sort)
	{
		i++;
		sort = sort->next;
	}
	keys = (char **)malloc(sizeof(char *) * (i + 1));
	filling_keys(lst, keys);
	compare_keys(keys, i);
	print_export(keys, lst, i);
}
