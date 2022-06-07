#include "../lexer.h"

char lexer(char *line)
{
	if (check_qoutes(line))
		return (1);
	return (0);
}