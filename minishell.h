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
	RED_OUT,
	RED_APPEND,
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

/*---------------------- Linkedlist functions ----------------------*/

t_token	*tokennew(char *content, int token);
void	tokenadd_front(t_token **lst, t_token *new);
char	tokenadd_back(t_token **lst, t_token *new);
int     tokensize(t_token *lst);
t_token	*tokenlast(t_token *lst);

/*---------------------- Lexer ----------------------*/

t_token	*lexer(char *line);




#endif
