#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef enum s_type
{
	WORD,
	SPACE,
	CMD,
	HERE_DOC,
	RED_IN,
	RED_APPEND,
	RED_OUT,
	PIPE,
}	t_type;



typedef struct s_token
{
    struct s_token  *prev;
	int             token;
	char            *content;
    struct s_token  *next;
}	t_token;

typedef struct s_shell
{
    struct s_token  *prev;
	int             token;
	char            *content;
	char			**cmd;
    struct s_token  *next;
}	t_shell;

/*------------------- get environment variables -------------------*/

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

/*---------------------- Linkedlist functions ----------------------*/

t_token	*tokennew(char *content, int token);
void	tokenadd_front(t_token **lst, t_token *new);
char	tokenadd_back(t_token **lst, t_token *new);
int     tokensize(t_token *lst);
t_token	*tokenlast(t_token *lst);

/*---------------------- Lexer ----------------------*/

t_token	*lexer(char *line, t_env *env);




#endif
