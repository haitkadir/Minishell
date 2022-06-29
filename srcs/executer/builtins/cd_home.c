/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:49:39 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/30 16:49:40 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
extern t_global status;

int	get_home(char	**home, t_env *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, "HOME"))
		{
			if (chdir(lst->value))
			{
				printf("no such file or directory\n");
				status.exit_status = 1;
				return (1);
			}
			*home = lst->value;
			break ;
		}
		lst = lst->next;
	}
	if (!*home)
	{
		printf("home not found\n");
		status.exit_status = 1;
		return (1);
	}
	return (0);
}

void	cd_home(t_env *env, char *arg)
{
	t_env	*lst;
	char	*oldpwd;
	char	*home;

	lst = env;
	home = NULL;
	if (get_home(&home, lst))
		return ;
	while (lst)
	{
		if (!ft_strcmp(lst->key, "PWD"))
		{
			if (lst->value)
				oldpwd = lst->value;
			lst->value = home;
			break ;
		}
		lst = lst->next;
	}
	if (!pwd(env, 0))
	{
		home = NULL;
		lst = ft_envnew("PWD", getcwd(home, 9999));
		ft_envadd_back(&env, lst);
	}
	check_oldpwd(env, oldpwd);
}
