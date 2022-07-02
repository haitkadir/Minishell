/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/07/02 20:48:50 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	converting_env(t_env *env, char	**envirement)
{
	char	*tmp;
	t_env	*lst;
	int		i;

	tmp = NULL;
	i = 0;
	lst = env;
	while (lst)
	{
		if (lst->value)
		{
			tmp = ft_strjoin(lst->key, "=");
			envirement[i] = ft_strjoin(tmp, lst->value);
			free(tmp);
		}
		lst = lst->next;
		i++;
	}
	envirement[i] = NULL;
}

char	**env_to_table(t_env *env)
{
	char	**envirement;
	int		i;
	t_env	*lst;

	lst = env;
	i = 0;
	envirement = NULL;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	envirement = (char **)ft_calloc(i + 1, sizeof(char *));
	converting_env(env, envirement);
	return (envirement);
}

void	execute_func(t_env	*env, t_arg *arg, t_shell *shell, int j)
{
	int	i;

	i = fork();
	g_status.signals = 2;
	if (i == 0)
		exec_in_child(env, arg, shell, j);
	if (!(shell->next && shell->next->token == PIPE))
	{
		waitpid(i, &g_status.exit_status, 0);
		if (WIFEXITED(g_status.exit_status))
			g_status.exit_status = g_status.exit_status % 255;
		else if (WIFSIGNALED(g_status.exit_status))
			g_status.exit_status += 128;
		waitpid(-1, NULL, 0);
	}
	g_status.signals = 1;
}

void	executing_builtins(t_shell *shell, t_arg *arg, t_env **env)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (shell->next != NULL && shell->next->token == PIPE)
			ft_dup(shell, arg, 1);
		else
			ft_dup(shell, arg, 0);
		builtins(env, shell->switchs, arg);
		close(arg->fd[1]);
		exit(g_status.exit_status);
	}
	if (!(shell->next && shell->next->token == PIPE))
	{
		waitpid(id, &g_status.exit_status, 0);
		if (WIFEXITED(g_status.exit_status))
			g_status.exit_status = g_status.exit_status % 255;
		waitpid(-1, NULL, 0);
	}
	close(arg->fd[1]);
}

int	cmd_token(t_shell *shell, t_arg *arg, t_env **env)
{
	int	j;

	if (check_builtins(shell->switchs[0]))
		executing_builtins(shell, arg, env);
	else
	{
		if (shell->next != NULL && shell->next->token == PIPE)
			execute_func(*env, arg, shell, 1);
		else
		{
			execute_func(*env, arg, shell, 0);
			close(arg->fd[0]);
		}
	}
	return (0);
}
