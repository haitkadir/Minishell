#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

int	open_file(char *filename, int macro)
{
	int file;

    file = -1;
    if (macro == RED_IN)
        file = open(filename, O_RDONLY);
    else if (macro == RED_OUT)
	    file = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0777);
    else if (macro == RED_APPEND)
        file = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
	return (file);
}

/*----------------------------------------------------------------------------*/

/*
    F_OK: Used to check for existence of file.

    R_OK: Used to check for read permission bit.

    W_OK: Used to check for write permission bit.

    X_OK: Used to check for execute permission bit.
*/


void    check_file_permession(char  *file, int macro)
{
    if (macro == RED_IN)
	{
		if (access(file, F_OK) != 0)
			put_error(file, "No such file of directory");
		else if (access(file, R_OK) != 0)
			put_error(file, "Permission denied");
	}
    if (macro == RED_OUT || macro == RED_APPEND)
		if (access(file, W_OK) != 0)
			put_error(file, "Permission denied");
}

/*----------------------------------------------------------------------------*/

void    process_operator(t_shell **shell, t_token **token)
{
    int file;
    int type;

    file = -1;
    type = -1;
    if ((*token)->token == RED_IN)
    {
        file = open_file((*token)->content, RED_IN);
        type = RED_IN;
    }
    else if ((*token)->token == RED_OUT)
    {
        file = open_file((*token)->content, RED_OUT);
        type = RED_OUT;
    }
    else if ((*token)->token == RED_APPEND)
    {
        file = open_file((*token)->content, RED_APPEND);
        type = RED_APPEND;
    }
    else if ((*token)->token == PIPE)
        type = PIPE;
    if (type != PIPE && file < 0)
    {
        check_file_permession((*token)->content, (*token)->token);
		shelladd_back(shell, shell_new(INVALID_FILE, NULL, NULL, -1));
		return ;
    }
	shelladd_back(shell, shell_new(type, NULL, NULL, file));
}