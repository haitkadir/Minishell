#include "../../minishell.h"

// void	free_env(t_env *head, char error)
// {
// 	t_env	*tmp;

// 	if (head)
// 	{
// 		while(head)
// 		{
// 			tmp = head;
// 			head = head->next;
// 			if (tmp->key)
// 				free(tmp->key);
// 			if (tmp->value)
// 				free(tmp->value);
// 			if (tmp)
// 				free(tmp);
// 		}
// 	}
// 	if (error)
// 		ft_putstr_fd("\033[1;31mAllocation failed\033[0m\n", 2);
// }


// void    ft_envadd_back(t_env **lst, t_env *new)
// {
//     t_env    *head;

// 	if (!new)
// 	{
// 		free_env(head, 1);
// 		exit(-1);
// 	}
//     head = *lst;
//     if (!(*lst))
//         *lst = new;
//     else
//     {
//         while (head->next != NULL)
//             head = head->next;
//         head->next = new;
//     }
// }

// t_env    *ft_envnew(char *key, char *value)
// {
//     t_env    *n1;

//     n1 = NULL;
//     n1 = (t_env *)malloc(sizeof(t_env));
//     if (n1 == NULL)
//         return (NULL);
//     n1->key = key;
//     n1->value = value;
//     n1->next = NULL;
//     return (n1);
// }



void    create_env(t_env **list, char **env)
{
    t_env	*lst;
    char	*value;
    char	*key;
    int		i;

    i = 0;
    *list = NULL;
    while (env[i])
    {
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		ft_bzero(ft_strchr(env[i], '='), 1);
		key = ft_strdup(env[i]);
		// printf("%s=%s\n", key, value);
        // lst = ft_lstnew1(key, value);
        // ft_lstadd_back1(list, lst);
		i++;
    }
}

