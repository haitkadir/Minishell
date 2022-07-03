/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:07:37 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 22:47:55 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	check_oldpwd(t_env *env, char	*oldpwd)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (!ft_strcmp(lst->key, "OLDPWD"))
		{
			if (lst->value != NULL)
				free(lst->value);
			if (oldpwd != NULL)
				lst->value = oldpwd;
			else
				lst->value = ft_strdup("");
			return ;
		}
		lst = lst->next;
	}
	if (oldpwd != NULL)
		lst = ft_envnew(ft_strdup("OLDPWD"), oldpwd);
	else
		lst = ft_envnew(ft_strdup("OLDPWD"), ft_strdup(""));
	ft_envadd_back(&env, lst);
}

void	update_dir(t_env *env, char	*dir, char	**oldpwd)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = env;
	while (lst)
	{
		if (!ft_strcmp(lst->key, "PWD"))
		{
			if (lst->value != NULL)
			{
				*oldpwd = ft_strdup(lst->value);
				free(lst->value);
			}
			lst->value = getcwd(dir, sizeof(dir));
			i = 1;
			break ;
		}
		lst = lst->next;
	}
	if (i == 0)
	{
		lst = ft_envnew(ft_strdup("PWD"), getcwd(dir, sizeof(dir)));
		ft_envadd_back(&env, lst);
	}
}

int	check_cases(t_env *env, char *arg, char *dir, char *oldpwd)
{
	t_env	*lst;
	int		i;

	i = 0;
	lst = env;
	dir = NULL;
	if (chdir(arg))
	{
		printf("not sush directory\n");
		g_status.exit_status = 1;
		return (1);
	}
	update_dir(lst, dir, &oldpwd);
	check_oldpwd(env, oldpwd);
	return (0);
}

void	cd_env(t_env *env, char *arg)
{
	t_env	*lst;
	char	*dir;
	char	*oldpwd;
	int		i;

	lst = env;
	dir = NULL;
	oldpwd = NULL;
	i = 0;
	if (!ft_strcmp(arg, NULL))
		cd_home(env, oldpwd);
	else
	{
		if (check_cases(env, arg, dir, oldpwd))
			return ;
	}
}
