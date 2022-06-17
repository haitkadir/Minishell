#ifndef LEXER_H
# define LEXER_H
# include "../../libft/libft.h"
# include "../../minishell.h"


char	check_qoutes(char *line);
char	check_in_out_operators(char *line, char oper);
char	check_errors(char *token);
char	*expender(char *line, int *i);
char	*word_within_dqoutes(char *line, int *i);
char	*word_within_sqoutes(char *line, int *i);
char	*word(char *line, int *i);
char	get_word(t_token **token, char *line, int *i);
char	get_here_doc(t_token **token, int *i);
char	get_red_in(t_token **token, int *i);
char	get_red_append(t_token **token, int *i);
char	get_red_out(t_token **token, int *i);
char	get_pipe(t_token **token, int *i);
char	tokenizer(t_token **token, char *line);


#endif