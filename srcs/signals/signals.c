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
extern t_global status;

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
    if (signal == SIGINT)
    {
		if (status.signals == 0)
    	{
			printf("\n");
    		rl_on_new_line();
			rl_replace_line("", 0);
    		rl_redisplay();
        	status.signals = 0;
		}
    }
	if (signal == SIGQUIT)
		i++;
}
