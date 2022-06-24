/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*   By: sahafid <marvin@42.fr>                   +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:38:45 by haitkadi          #+#    #+#             */
/*   Updated: 2022/06/14 02:38:48 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error(char *keyword, char *err)
{
	ft_putstr_fd("\033[4;31mMinishell\033[0m: ", 2);
	ft_putstr_fd(keyword, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
}


static void print_env(t_env	*env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}


int main(int ac, char **av, char **main_env)
{
	char *line;
	t_shell *shell;
	t_env	*env;

	line = NULL;
	create_env(&env, main_env);
	while (1)
	{
		line = readline("\033[1;32mMinishell:\033[0m ");
		if (!line)
			break ;
		else if (line[0] == '\n')
			continue ;
		add_history (line);
		shell = parser(line, env);
		// if (!shell)
		// 	ft_putstr_fd("\033[1;31mSyntax error\033[0m\n", 2);
		// print_env(env);
		
	}
	return (0);
}
