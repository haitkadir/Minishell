#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define BUILTINS "echo cd pwd export unset env exit"

/*-------------------------------- global ------------------------------------*/


typedef enum s_type
{
	CMD,
	CMD_NOT_FOUND,
	HERE_DOC,
	RED_IN,
	RED_APPEND,
	RED_OUT,
	INVALID_FILE,
	PIPE,
	WORD,
	SPACE,
}	t_type;


void	put_error(char *keyword, char *err);




/*--------------------------- get environment variables ----------------------*/

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
} t_env;

void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envnew(char *key, char *value);
void	create_env(t_env **list, char **env);
char	*ft_getenv(t_env *env, char *buffer);
void	free_env(t_env *head, char error);


/*-------------------------------- Lexer -------------------------------------*/

typedef struct s_token
{
    struct s_token  *prev;
	int             token;
	char            *content;
    struct s_token  *next;
}	t_token;

char	is_last_operator(t_token *token);
char	check_last(t_token *token, int	macro);
t_token	*tokennew(char *content, int token);
void	tokenadd_front(t_token **lst, t_token *new);
char	tokenadd_back(t_token **lst, t_token *new);
int     tokensize(t_token *lst);
t_token	*tokenlast(t_token *lst);
void	tokendelone(t_token *lst);

t_token	*lexer(char *line, t_env *env);

/*-------------------------------- Parser ------------------------------------*/

typedef struct s_shell
{
    struct s_shell  *prev;
	int             token;
	char            *data;
	char			**switchs;
	int				file;
    struct s_shell  *next;
}	t_shell;

char	shelladd_front(t_shell **shell, t_shell *new);
char	shelladd_back(t_shell **shell, t_shell *new);
int		shell_size(t_shell *shell);
t_shell	*shell_new(int token, char *data, char **switchs, int file);
t_shell	*shell_last(t_shell *shell);
t_shell *parser(char *line, t_env *env);

/*-------------------------------- Lexer ------------------------------------*/

char	check_qoutes(char *line);
char	check_in_out_operators(char *line, char oper);
char	check_errors(char *token);
char	*expender(char *line, int *i, t_env *env);
char	*word_within_dqoutes(char *line, int *i, t_env *env, t_token *token);
char	*word_within_sqoutes(char *line, int *i);
char	*word(char *line, int *i);
char	get_word_util(char **s1, char **s2);
char	get_word(t_token **token, char *line, int *i, t_env *env);
char	get_here_doc(t_token **token, int *i);
char	get_red_in(t_token **token, int *i);
char	get_red_append(t_token **token, int *i);
char	get_red_out(t_token **token, int *i);
char	get_pipe(t_token **token, int *i);
char	get_space(t_token **token, char *line, int *i);
char	is_operators(char qoute, char a, char b);
char	get_operator(t_token **token, char *line, int *i);
char	tokenizer(t_token **token, char *line, t_env *env);

/*-------------------------------- Parser ------------------------------------*/

void	free_path(char **path);
char	**get_path(t_env *env);
char	*check_cmd(t_env *env, char *cmd);
char	**get_switchs(t_token **token);
void	get_cmd(t_shell **shell, t_env *env, t_token **token);
int		open_file(char *filename, int macro);
void    check_file_permession(char  *file, int macro);
char	is_operator(t_token *token);
void    process_operator(t_shell **shell, t_token **token);
char	process_data(t_shell **shell, t_token *token, t_env *env);

#endif
