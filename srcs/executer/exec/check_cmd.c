/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:08:23 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// int	check_path(t_env *env, t_arg *arg)
// {
// 	t_env	*lst;
// 	int		i;

// 	lst = env;
// 	i = 0;
// 	while (lst)
// 	{
// 		if (!ft_strcmp(lst->key, "PATH"))
// 		{
// 			if (lst->value)
// 			{
// 				arg->paths = ft_split(lst->value, ':');
// 				i = 1;
// 			}
// 			return (0);
// 		}
// 		lst = lst->next;
// 	}
// 	if (i != 1)
// 	{
// 		ft_putstr_fd("PATH not found\n", 2);
// 		status.exit_status = 1;
// 		return (1);
// 	}
// }

// int	checking_path(t_arg *arg, char	*str, char	*tmp)
// {
// 	int		i;
// 	char	*cmd_path;

// 	i = 0;
// 	while (arg->paths[i])
// 	{
// 		cmd_path = ft_strjoin(arg->paths[i], "/");
// 		tmp = cmd_path;
// 		cmd_path = ft_strjoin(cmd_path, str);
// 		free(tmp);
// 		if (!access(cmd_path, X_OK))
// 		{
// 			arg->cmd_path = cmd_path;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	ft_putstr_fd("Command not found\n", 2);
// 	status.exit_status = 1;
// 	return (0);
// }

int	check_cmd1(t_env	*env, t_arg *arg, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	
	return (1);
	// if (checking_path(arg, str, tmp))
	// 	return (1);
	ft_putstr_fd("Command not found\n", 2);
	status.exit_status = 127;
	return (0);
}

void	builtins(t_env	*envi, char **str, t_arg *arg)
{
	if (!ft_strcmp_tl(str[0], "pwd"))
		pwd(envi, 1);
	else if (!ft_strcmp(str[0], "export"))
		export_env(&envi, str[0], str, arg);
	else if (!ft_strcmp(str[0], "unset"))
		unset_env(&envi, str);
	else if (!ft_strcmp_tl(str[0], "env"))
		env(envi);
	else if (!ft_strcmp(str[0], "exit"))
	{
		if (str[1] != NULL)
			exit11(ft_atoi(str[1]));
		else
			exit10();
	}
	else if (!ft_strcmp(str[0], "cd"))
		cd_env(envi, str[0], str[1]);
	else if (!ft_strcmp(str[0], "echo"))
		echo_env1(envi, str);
}

int	check_builtins(char *str)
{
	if (!ft_strcmp_tl(str, "pwd"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp_tl(str, "env"))
		return (1);
	else if (!ft_strcmp(str, "exit"))
		return (1);
	else if (!ft_strcmp_tl(str, "cd"))
		return (1);
	else if (!ft_strcmp_tl(str, "echo"))
		return (1);
	return (0);
}
