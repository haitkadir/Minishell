/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 20:24:50 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	builtins(t_env	**envi, char **str, t_arg *arg)
{
	if (!ft_strcmp_tl(str[0], "pwd"))
		pwd(*envi, 1);
	else if (!ft_strcmp(str[0], "export"))
		export_env(envi, str[0], str, arg);
	else if (!ft_strcmp(str[0], "unset"))
		unset_env(envi, str);
	else if (!ft_strcmp_tl(str[0], "env"))
		env(*envi);
	else if (!ft_strcmp(str[0], "exit"))
	{
		if (str[1] != NULL)
			exit11(str[1]);
		else
			exit10();
	}
	else if (!ft_strcmp(str[0], "cd"))
		cd_env(*envi, str[0], str[1]);
	else if (!ft_strcmp(str[0], "echo"))
		echo_env1(*envi, str);
}
