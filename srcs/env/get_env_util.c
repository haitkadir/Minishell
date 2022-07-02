/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:15:30 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/03 00:15:32 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

void	free_env(t_env **head, char error)
{
	t_env	*tmp;

	if (*head)
	{
		while (*head)
		{
			tmp = *head;
			*head = (*head)->next;
			ft_free(tmp->key);
			ft_free(tmp->value);
			if (tmp)
				free(tmp);
		}
	}
	if (error)
		ft_putstr_fd("\033[1;31mAllocation failed\033[0m\n", 2);
}
