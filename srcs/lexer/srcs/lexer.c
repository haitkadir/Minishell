#include "../lexer.h"


// static char check_operators(char *line)
// {
// 	int i;
// 	char flag;

// 	i = 0;
// 	flag = 0;
// 	while(line[i])
// 	{
// 		if (line[i] == '<' && !ft_isalnum(line[i + 1]))
// 			flag = !flag;
		
// 		i++;
// 	}
// 	return (0);
// }


char lexer(char *line)
{
	if (check_qoutes(line))
		return (1);
	return (0);
}