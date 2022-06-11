#include "../lexer.h"

char get_cmd(t_token *shell, char *line, int *i)
{
	int start;
	int len;
	char	qoute;

	start = *i;
	qoute = 0;
	len = 0;
	while (line[*i])
	{
		if (ft_strchr("\"\'", line[*i]))
			qoute = !qoute;
		if (!qoute && ft_strchr("<>|", line[*i]))
			break ;
		len++;
		*i += 1;
	}
	printf("cmd:%s:\n", ft_substr(line, start, len));
	return (0);
}
