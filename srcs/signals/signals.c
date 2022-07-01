/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:21:18 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/27 18:21:19 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hide_ctrl(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

void	show_ctrl(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

void	handler(int signal)
{
	int i;

	i = 0;
    if (signal == SIGINT && status.signals == 0)
		exit(1);
	else if (signal == SIGINT && status.signals == 1)
	{
		printf("\n");
    	rl_on_new_line();
		rl_replace_line("", 0);
    	rl_redisplay();
	}
	else if (signal == SIGINT && status.signals != 1)
		i++;
	if (signal == SIGQUIT)
		i++;
}
