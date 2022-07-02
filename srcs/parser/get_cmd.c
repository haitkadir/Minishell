#include "../../minishell.h"

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
		return (NULL);
	while (path[i])
	{
		full_cmd = ft_strjoin(path[i], tmp_cmd);
		if (!full_cmd)
			return (NULL);
		if (access(full_cmd, F_OK) == 0)
		{
			free_path(path);
			ft_free(tmp_cmd);
			return (full_cmd);
		}
		ft_free(full_cmd);
		i++;
	}
	return (put_error(cmd, "Command not found", 127), NULL);
}




/*----------------------------------------------------------------------------*/

static int	count_words(t_token *token)
{
	int i;

	i = 0;
	if (!token)
		return (0);
	while (token && (token->token != PIPE))
	{
		if (token->token == WORD)
			i++;
		token = token->next;
	}
	return (i);
}

/*----------------------------------------------------------------------------*/

char	**get_switchs(t_token *token)
{
	char	**switchs;
	int		i;
	i = 0;

	if (!token)
		return (NULL);
	switchs = (char **)ft_calloc(count_words(token) + 1, sizeof(char *));
	if (!switchs)
		return (NULL);
	while (token && (token->token != PIPE))
	{
		if (token->token == WORD)
			switchs[i++] = ft_strdup(token->content);
		token = token->next;
	}
	switchs[i] = NULL;
	return (switchs);
}

/*----------------------------------------------------------------------------*/

t_shell	*get_cmd(t_env *env, t_token *token)
{
	char	*full_cmd;
	char	**switchs;
	
	full_cmd = NULL;
	switchs = NULL;
	if (!token)
		return (NULL);
	if (check_builtins(token->content))
		full_cmd = ft_strdup(token->content);
	else if (ft_strchr("./", token->content[0]))
	{
		if (!check_cmd_permissions(token->content))
			full_cmd = ft_strdup(token->content);
	}
	else
		full_cmd = check_cmd(env, token->content);
	if (!full_cmd)
		return (shell_new(CMD_NOT_FOUND, NULL, NULL, -1));
	switchs = get_switchs(token);
	return (shell_new(CMD, full_cmd, switchs, -1));
}
