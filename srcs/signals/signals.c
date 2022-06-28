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

void	handler(int signal)
{
	int i;

	i = 0;
    // if (status.signals == 1)
    // {
    if (signal == SIGINT)
    {
        i++;
        status.signals = 0;
    	//printf("\033[1;32mMinishell:\e[0m ");
    	write(1, "\n\033[1;32mMinishell:\e[0m ", 24);
    	rl_on_new_line();
    	rl_redisplay();
		// rl_replace_line("\n\033[1;32mMinishell:\e[0m ", 0);
    }
   // }
	if (signal == SIGQUIT)
		i++;
}

// void	signals(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = handler;
// 	sigaction(SIGINT, &sa, NULL);
// }