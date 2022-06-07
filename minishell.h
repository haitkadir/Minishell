#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "./srcs/lexer/lexer.h"

typedef enum s_type
{
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


/*---------------------- Linkedlist functions ----------------------*/

t_token	*tokennew(char *content, int token);
void	tokenadd_front(t_token **lst, t_token *new);
void	tokenadd_back(t_token **lst, t_token *new);
int     tokensize(t_token *lst);
t_token	*tokenlast(t_token *lst);


#endif

