#include "../lexer.h"




char	tokenizer(t_token *shell, char *line)
{
	int i;
	char	qoute;
	
	qoute = 0;
	i = 0;
	while (line[i])
	{
		if (ft_strchr("\"\'", line[i]))
			qoute = !qoute;
		if (!qoute && line[i] == '<' && line[i + 1] == '<')
		{
			printf("here_doc\n");
			i += 2;
		}
		else if (!qoute && line[i] == '<' && line[i + 1] != '<')
		{
			printf("in_redirection\n");
			i++;
		}
		else if (!qoute && line[i] == '>' && line[i + 1] == '>')
		{
			printf("append_redirection\n");
			i += 2;
		}
		else if (!qoute && line[i] == '>' && line[i + 1] != '>')
		{
			printf("out_redirection\n");
			i++;
		}
		else if (ft_isalpha(line[i]))
			get_cmd(shell, line, &i);
		i++;
	}
	return (0);
}