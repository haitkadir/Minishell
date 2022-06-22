#include "../parser.h"

/*----------------------------------------------------------------------------*/

void	free_path(char **path)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
			free(path[i++]);
		free(path);
	}
}

/*----------------------------------------------------------------------------*/

char	**get_path(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			return (ft_split(env->value, ':'));
		}
		env = env->next;
	}
	return (NULL);
}

/*----------------------------------------------------------------------------*/

char	*check_cmd(t_env *env, char *cmd)
{
	char	*tmp_cmd;
	char	*full_cmd;
	char	**path;
	int		i;

	i = 0;
	tmp_cmd = ft_strjoin("/", cmd);
	path = get_path(env);
	if (!tmp_cmd || !path)
		exit(-1);
	while (path[i])
	{
		full_cmd = ft_strjoin(path[i], tmp_cmd);
		if (!full_cmd)
			exit(-1);
		if (access(full_cmd, F_OK) == 0)
		{
			free_path(path);
			ft_free(tmp_cmd);
			return (full_cmd);
		}
		ft_free(full_cmd);
		i++;
	}
	return (NULL);
}

/*----------------------------------------------------------------------------*/

static int	count_words(t_token *token)
{
	int i;

	i = 0;
	if (!token)
		return (0);
	while (token && (token->token == WORD || token->token == SPACE))
	{
		if (token->token == WORD && token->prev->token == SPACE)
			i++;
		token = token->next;
	}
	return (i);
}

/*----------------------------------------------------------------------------*/

char	**get_switchs( t_token ***token)
{
	char	**switchs;
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	switchs = (char **)ft_calloc(count_words(**token) + 1, sizeof(char *));
	while ((**token) && ((**token)->token == WORD || (**token)->token == SPACE))
	{
		if ((**token)->token == WORD)
		{
			if (tmp)
				tmp = ft_realloc(tmp, ft_strdup((**token)->content));
			else
				tmp = ft_strdup((**token)->content);
		}
		if (tmp && (!(**token)->next || (**token)->token == SPACE))
		{
			switchs[i++] = tmp;
			tmp = NULL;
		}
		(**token) = (**token)->next;
	}
	return (switchs);
}

/*----------------------------------------------------------------------------*/

char	*get_cmd(t_shell **shell, t_env *env, t_token **token)
{
	char	*full_cmd;
	char	**switchs;
	if (ft_strnstr(BUILTINS, (*token)->content, ft_strlen(BUILTINS)))
		full_cmd = ft_strdup((*token)->content);
	else if (ft_strchr("./", (*token)->content[0]))
		full_cmd = ft_strdup((*token)->content);
	else
		full_cmd = check_cmd(env, (*token)->content);
	if (!full_cmd)
		return (NULL);
	switchs = get_switchs(&token);
	if (!switchs)
		return (NULL);
	if (shelladd_back(shell, shell_new(CMD, full_cmd, switchs, -1)))
		exit(1);
	return (full_cmd);
}

/*----------------------------------------------------------------------------*/

// int	check_files(char **filename)
// {
// 	int file;

// 	file = open(av[1], O_RDONLY);
// 	if (file == -1)
// 		return (-1);
// 	exec->outfile = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
// 	if (exec->outfile == -1)
// 		return (exec->err = 4, 1);
// 	return (0);
// }

/*----------------------------------------------------------------------------*/

// t_exec	*parsing(char **env, char **av)
// {
// 	t_exec	*exec;
// 	char	**paths;

// 	paths = NULL;
// 	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
// 	if (!exec)
// 		exit_err();
// 	if (check_files(av, exec))
// 		return (exec);
// 	paths = get_paths(env);
// 	if (!paths)
// 		return (exec->err = 9, exec);
// 	exec->cmd_switchs1 = ft_split(av[2], ' ');
// 	exec->cmd_switchs2 = ft_split(av[3], ' ');
// 	if (!exec->cmd_switchs1[0] || !exec->cmd_switchs2[0])
// 		return (exec->err = 5, exec);
// 	exec->full_cmd1 = check_cmd(paths, exec->cmd_switchs1[0]);
// 	if (!exec->full_cmd1)
// 		return (exec->err = 2, exec);
// 	exec->full_cmd2 = check_cmd(paths, exec->cmd_switchs2[0]);
// 	if (!exec->full_cmd2)
// 		return (exec->err = 3, exec);
// 	if (paths)
// 		free_paths(paths);
// 	return (exec);
// }