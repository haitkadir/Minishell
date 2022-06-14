#include "../lexer.h"

char	get_here_doc(t_token **token, int *i)
{
	if (tokenadd_back(token, tokennew(ft_strdup("<<"), HERE_DOC)))
		return (1);
	*i += 2;
	return (0);
}

char	get_red_in(t_token **token, int *i)
{
	if (tokenadd_back(token, tokennew(ft_strdup("<"), RED_IN)))
		return (1);
	*i += 1;
	return (0);
}

char	get_red_append(t_token **token, int *i)
{
	if (tokenadd_back(token, tokennew(ft_strdup(">>"), RED_APPEND)))
		return (1);
	*i += 2;
	return (0);
}

// char	get_red_out(t_token **token, char *line, int *i);
// char	get_red_append(t_token **token, char *line, int *i);
// char	get_pipe(t_token **token, char *line, int *i);





char get_word(t_token **token, char *line, int *i)
{
	int 		start;
	char		qoute;
	char		flag;
	int 		len;

	start = *i;
	qoute = 0;
	flag = 0;
	len = 0;
	if (ft_strchr("\'\"", line[*i]))
	{
		flag = !flag;
	}
	while (line[*i])
	{
		if (ft_strchr("\"\'", line[*i]))
		{
			if (len && flag)
			{
				len++;
				break;
			}
			else if (!flag &&!qoute)
			{
				len++;
				break;
			}
			qoute = !qoute;
		}
		if (!qoute && ft_strchr("<>| \"", line[*i]))
			break ;
		len++;
		*i += 1;
	}
	tokenadd_back(token, tokennew(ft_substr(line, start, len), WORD));
	return (0);
}
