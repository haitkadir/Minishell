#ifndef PARSER_H
# define PARSER_H
# include "../../libft/libft.h"
# include "../../minishell.h"

void	free_path(char **path);
char	**get_path(t_env *env);
char	*check_cmd(t_env *env, char *cmd);
char	**get_switchs( t_token **token);
void	get_cmd(t_shell **shell, t_env *env, t_token **token);

char	is_operator(t_token *token);
char	process_data(t_shell **shell, t_token *token, t_env *env);

#endif