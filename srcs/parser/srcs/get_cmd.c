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

char	*get_cmd(t_env *env, char *cmd)
{
	char	*full_cmd;

	if (ft_strnstr(BUILTINS, cmd, ft_strlen(BUILTINS)))
		return (ft_strdup(cmd));
	full_cmd = check_cmd(env, cmd);
	if (!full_cmd)
		return (NULL);
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