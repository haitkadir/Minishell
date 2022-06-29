#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

char	filetype(char *input)
{
    struct stat    file_stat;

    if (stat(input, &file_stat))
        return (0);
	if (!S_ISREG(file_stat.st_mode) && S_ISDIR(file_stat.st_mode))
	{
        put_error(input, "Is a directory");
		return (1);
	}
	return (0);
}


/*----------------------------------------------------------------------------*/

void    check_file_permession(char  *file, int macro)
{
	if (!filetype(file))
	{
		if (macro == RED_IN)
		{
			if (access(file, F_OK) != 0)
				put_error(file, "No such file of directory");
			else if (access(file, R_OK) != 0)
				put_error(file, "Permission denied");
		}
		else if (macro == RED_OUT || macro == RED_APPEND)
			if (access(file, W_OK) != 0)
				put_error(file, "Permission denied");
	}
}

/*----------------------------------------------------------------------------*/

int	open_file(char *filename, int macro)
{
	int file;
	int	type;

    file = -1;
	type = -1;
    if (macro == RED_IN)
	{
        file = open(filename, O_RDONLY);
		type = RED_IN;
	}
    else if (macro == RED_OUT)
	{
	    file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		type = RED_OUT;
	}
    else if (macro == RED_APPEND)
	{
        file = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
		type = RED_APPEND;
	}
	if (type && file < 0)
		check_file_permession(filename, type);
	return (file);
}

/*----------------------------------------------------------------------------*/