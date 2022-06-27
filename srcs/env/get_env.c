#include "../../minishell.h"

void	free_env(t_env *head, char error)
{
	t_env	*tmp;

	if (head)
	{
		while(head)
		{
			tmp = head;
			head = head->next;
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			if (tmp)
				free(tmp);
		}
	}
	if (error)
		ft_putstr_fd("\033[1;31mAllocation failed\033[0m\n", 2);
}


void    ft_envadd_back(t_env **lst, t_env *new)
{
    t_env    *tmp;

	if (!new)
	{
		free_env(*lst, 1);
		exit(-1);
	}
    tmp = *lst;
    if (!(*lst))
        *lst = new;
    else
    {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
    }
}

t_env    *ft_envnew(char *key, char *value)
{
    t_env    *tmp;

	// if (!key || !value)
	// 	return (NULL);
    tmp = NULL;
    tmp = (t_env *)malloc(sizeof(t_env));
    if (!tmp)
        return (NULL);
    tmp->key = key;
    tmp->value = value;
    tmp->next = NULL;
    return (tmp);
}



void    create_env(t_env **list, char **env)
{
    char	*value;
    char	*key;
    int		i;

    i = 0;
    *list = NULL;
	key = NULL;
	value = NULL;
    while (env[i])
    {
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		ft_bzero(ft_strchr(env[i], '='), 1);
		key = ft_strdup(env[i]);
        ft_envadd_back(list, ft_envnew(key, value));
		i++;
    }
}


char	*ft_getenv(t_env *env, char *buffer)
{
	t_env	*tmp;

	if (!env || !buffer)
		return (NULL);
	tmp = env;
	while(tmp)
	{
		if (ft_strcmp(buffer, tmp->key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_keys(char *str, int c)
{
	char	*h;
	char	a;
	int		j;

	h = (char *)str;
	j = 0;
	a = (char) c;
	while (h[j] != a)
		j++;
	if (h[j] + 2 == 0)
		return (str);
	else
	{
		h[j] = 0;
		return (h);
	}
	return (0);
}

