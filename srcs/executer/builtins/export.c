/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:05:59 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 22:18:06 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	export_special_char(char c)
{
	if (ft_strchr("/|#`[]!{};()*&~,-+@%%^<>", c))
		return (1);
	return (0);
}

int	no_keys_case(char	*str, t_env **lst, t_env *lst1)
{
	t_env	*tmp;
	int		i;

	tmp = *lst;
	while (tmp)
	{
		i = 0;
		while (str[i])
		{
			if (export_special_char(str[i]))
			{
				ft_putstr_fd("not a valid identifier\n", 2);
				g_status.exit_status = 1;
				return (1);
			}
			i++;
		}
		if (!ft_strcmp(tmp->key, str))
			return (1);
		tmp = tmp->next;
	}
	lst1 = ft_envnew(ft_strdup(str), NULL);
	ft_envadd_back(lst, lst1);
	return (1);
}

int	key_existed(char	*str, int	*j, int i)
{
	int	t;

	t = 0;
	if (str[i - 1] && str[i - 1] == '+' && str[i - 2] != '+')
		*j = 1;
	else if (str[i - 1] == '-')
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		g_status.exit_status = 1;
		return (1);
	}
	if (str[i - 1] && str[i - 1] == '+')
		i -= 2;
	while (t <= i)
	{
		if (str[t] && export_special_char(str[t]))
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			g_status.exit_status = 1;
			return (1);
		}
		t++;
	}
	return (0);
}

int	check_keys(t_env **lst, char *str, int *j, int i)
{
	t_env	*lst1;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		g_status.exit_status = 1;
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (key_existed(str, j, i))
				return (1);
			return (0);
		}
		i++;
	}
	if (i == ft_strlen(str))
	{
		if (no_keys_case(str, lst, lst1))
			return (1);
	}
	return (1);
}

void	export_env(t_env **env, char *str, char **find, t_arg *arg)
{
	t_env	*lst;
	int		i;

	i = 1;
	lst = *env;
	if (!find[1])
	{
		sorted_env(lst, arg);
		return ;
	}
	else
	{
		while (find[i])
		{
			export_things(env, find[i], arg);
			i++;
		}
	}
}
