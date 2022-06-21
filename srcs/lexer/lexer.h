#ifndef LEXER_H
# define LEXER_H
# include "../../libft/libft.h"
# include "../../minishell.h"


char	check_qoutes(char *line);
char	check_in_out_operators(char *line, char oper);
char	check_errors(char *token);
char	*expender(char *line, int *i, t_env *env);
char	*word_within_dqoutes(char *line, int *i, t_env *env, t_token *token);
char	*word_within_sqoutes(char *line, int *i);
char	*word(char *line, int *i);
char	get_word(t_token **token, char *line, int *i, t_env *env);
char	get_here_doc(t_token **token, int *i);
char	get_red_in(t_token **token, int *i);
char	get_red_append(t_token **token, int *i);
char	get_red_out(t_token **token, int *i);
char	get_pipe(t_token **token, int *i);
char	get_space(t_token **token, char *line, int *i);
char	is_operators(char qoute, char a, char b);
char	is_last_operator(t_token *token);
char	get_operator(t_token **token, char *line, int *i);
char	check_last(t_token *token, int	macro);
char	tokenizer(t_token **token, char *line, t_env *env);


#endif