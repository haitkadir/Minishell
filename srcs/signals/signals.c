/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:21:18 by            #+#    #+#             */
/*   Updated: 2022/05/27 18:21:19 by           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../../minishell.h"
#include <termios.h>

void	hide_ctrl(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCIFLUSH, &attr);
}

void	show_ctrl(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCIFLUSH, &attr);
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
	else if (signal == SIGINT && status.signals != 1 && status.signals != 0)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
	if (signal == SIGQUIT)
		i++;
}
