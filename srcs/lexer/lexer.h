#ifndef LEXER_H
# define LEXER_H
# include "../../libft/libft.h"
# include "../../minishell.h"



char	check_qoutes(char *line);
char	check_in_out_operators(char *line, char oper);
char	check_errors(char *line);
char	get_cmd(t_token *shell, char *line, int *i);
char	tokenizer(t_token *shell, char *line);


#endif