#ifndef LEXER_H
# define LEXER_H
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "../../libft/libft.h"


# define BBLACK    '\033[1;30m'
# define BRED      '\033[1;31m'
# define BGREEN    '\033[1;32m'
# define BYELLW    '\033[1;33m'
# define BBLUE     '\033[1;34m'
# define BPURPLE   '\033[1;35m'
# define BCYAN     '\033[1;36m'
# define COFF      '\033[0m'

// typedef enum s_type
// {
// 	CMD,
// 	HERE_DOC,
// 	RED_IN,
// 	RED_OUT,
// 	RED_APPEND,
// 	PIPE,
// }	t_type;




// typedef struct s_token
// {
// 	int		token;
// 	char 	*str;
// 	char 	*file;
// }	t_token;

char check_qoutes(char *line);
char	lexer(char *line);


#endif