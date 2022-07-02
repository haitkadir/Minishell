#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>


/*-------------------------------- global ------------------------------------*/


enum
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
	SPACE_,
};
// Tokenizer or lexer part
typedef struct s_token
{
    struct s_token  *prev;
	int             token;
	char            *content;
    struct s_token  *next;
}	t_token;
// The final data that will be returnd to execution part
typedef struct s_shell
{
    struct s_shell  *prev;
	int             token;
	char            *data;
	char			**switchs;
	int				file;
    struct s_shell  *next;
}	t_shell;

// for exit status and signals
typedef struct s_global
{
	int	exit_status;
	int	signals;
} t_global;

t_global status;
/*--------------------------- get environment variables ----------------------*/

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
} t_env;

void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envnew(char *key, char *value);
char	*get_keys(char *str, int c);
void	create_env(t_env **list, char **env);
char	*ft_getenv(t_env *env, char *buffer);
void	free_env(t_env *head, char error);

/*-------------------------------- Utils -------------------------------------*/

int		check_builtins(char *str);
void	put_error(char *keyword, char *msg, int err);

/*-------------------------------- Tools -------------------------------------*/

t_token	*tokennew(char *content, int token);
void	tokenadd_front(t_token **lst, t_token *new);
char	tokenadd_back(t_token **lst, t_token *new);
int     tokensize(t_token *lst);
t_token	*tokenlast(t_token *lst);
void	tokendelone(t_token *lst);
void	token_clear(t_token **lst);

char	shelladd_front(t_shell **shell, t_shell *new);
char	shelladd_back(t_shell **shell, t_shell *new);
int		shell_size(t_shell *shell);
t_shell	*shell_new(int token, char *data, char **switchs, int file);
t_shell	*shell_last(t_shell *shell);

/*-------------------------------- Lexer ------------------------------------*/


char	check_qoutes(char *line);
char	is_redirection(t_token *token);
char	check_errors(t_token *token);
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
char	is_last_operator(t_token *token);
char	check_last(t_token *token, int	macro);
t_token	*lexer(char *line, t_env *env);

/*-------------------------------- Parser ------------------------------------*/


void	free_path(char **path);
char	**get_path(t_env *env);
char	check_cmd_permissions(char *cmd);
char	*check_cmd(t_env *env, char *cmd);
char	**get_switchs(t_token *token);
t_shell	*get_cmd(t_env *env, t_token *token);
int		open_file(char *filename, int macro);
void    check_file_permession(char  *file, int macro);
char	filetype(char *input);
char	is_operator(t_token *token);
void    process_operator(t_shell **shell, t_token **token);
void	handle_files(int *args, char *file, int token);
void	store_data(t_shell **shell, int *files, t_shell *cmd, t_shell *here_doc);
void	process_data_util(t_shell **shell, t_token **token, t_env *env);
char	process_data(t_shell **shell, t_token *token, t_env *env);
void	parser(char *line, t_env **env);

/*-------------------------------- Executer ------------------------------------*/

typedef struct s_arg
{
	char	*str;
	int		fd[2];
	char	**paths;
	int		in_fd;
	int		in;
	int		out;
	int		out_fd;
	int		not_found;
	int		i;
} t_arg;

/* ------------------------------ Utils functions ---------------------------- */
void	check_oldpwd(t_env *env, char	*oldpwd);

/* --------------------------------- builtins --------------------------------- */

void	builtins(t_env	**envi, char **str, t_arg *arg);
char	*pwd(t_env *env, int i);
void	unset_env(t_env **env, char **str);
void	unset_utils(t_env **env, t_env *lst, char *find, t_env *tmp);
void	env(t_env *env);
void	exit10(void);
void	exit11(char *ptr);
void	echo_env1(t_env *env, char **str);
void	cd_home(t_env *env, char *arg);
void	cd_env(t_env *env, char	*str, char *arg);


/* --------------------------------- export --------------------------------- */

void	export_things(t_env **env, char	*find, t_arg *arg);
void	export_env(t_env **env, char *str, char **find, t_arg *arg);
int		check_equal(t_env *lst, char *str, t_arg *arg);
void	sorted_env(t_env *lst, t_arg *arg);

/* --------------------------------- duping --------------------------------- */

void	ft_dup(t_shell *shell, t_arg *arg, int j);

/* ------------------------- executing function ----------------------------- */

int		one_cmd(t_env	**env, t_arg *arg, t_shell *shell);
int		execute_builting(t_shell *lst, t_arg *arg, t_env **env);

void	exec_in_child(t_env	*env, t_arg *arg, t_shell *shell, int j);
char	**env_to_table(t_env *env);
void	converting_env(t_env *env, char	**envirement);
void	check_command(t_env	**env, t_arg *arg, t_shell *shell);
int		check_cmd1(t_env	*env, t_arg *arg, char *str);
int		cmd_token(t_shell *shell, t_arg *arg, t_env **env);
int		check_keys(t_env *lst, char *str, int *j, int i);
int		check_path(t_env *env, t_arg *arg);
void	execute_func(t_env	*env, t_arg *arg, t_shell *shell, int j);
void	signals(void);
void	handler(int signal);
void	show_ctrl(void);
void	hide_ctrl(void);

/* --------------------------------- her_doc --------------------------------- */

void	her_doc_logic(char	*str, int i, t_shell *shell);
int		her_doc(t_shell *shell, t_arg *arg);
int		her_doc_exec(t_shell *shell, t_arg *arg);

#endif
