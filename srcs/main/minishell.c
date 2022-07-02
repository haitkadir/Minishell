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

#include "../../minishell.h"


int main(int ac, char **av, char **main_env)
{
	char				*line;
	t_env				*env;

	line = NULL;
	status.signals = 1;
	status.exit_status = 0;
	create_env(&env, main_env);
	hide_ctrl();
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
	while (1)
	{
		line = readline("\033[1;32mMinishell:\e[0m ");
		if (!line)
			break ;
		else if (line[0] == '\n')
			continue ;
		add_history (line);
		parser(line, &env);
		ft_free(line);
	}
	free_env(&env, 0);
	show_ctrl();
	exit10();
	return (0);
}
