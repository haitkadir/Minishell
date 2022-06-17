#include "../lexer.h"

char	*expender(char *line, int *i)
{
	char	*env;
	int 	len;
	int 	start;

	len = 0;
	*i += 1;
	start = *i;
	env = NULL;
	while (line[*i])
	{
		if (ft_strchr("\"\' $", line[*i]))
		{
			// *i += 1;
			break ;
		}
		len++;
		*i += 1;
	}
	env = ft_substr(line, start, len);
	return (getenv(env));
}

char	*word_within_dqoutes(char *line, int *i)
{
	int		len;
	int		start;
	char	expend;

	len = 0;
	*i += 1;
	start = *i;
	while (line[*i])
	{
		if (ft_strchr("\"", line[*i]))
		{
			// *i += 1;
			break ;
		}
		// else if (line[*i] == '$' && ft_isalnum(line[*i + 1]))
		// {
 
		// }
		len++;
		*i += 1;
	}
	return (ft_substr(line, start, len));
}

char	*word_within_sqoutes(char *line, int *i)
{
	int len;
	int start;

	len = 0;
	*i += 1;
	start = *i;
	while (line[*i])
	{
		if (line[*i] == '\'')
		{
			*i += 1;
			break ;
		}
		len++;
		*i += 1;
	}
	printf("====%s===\n", ft_substr(line, start, len));
	printf("====%c===\n", line[*i]);
	return (NULL);
}

char	*word(char *line, int *i)
{
	int len;
	int start;

	len = 0;
	start = *i;
	while (line[*i])
	{
		if (ft_strchr("<>| \'\"", line[*i]))
			break ;
		len++;
		*i += 1;
	}
	return (ft_substr(line, start, len));
}



char get_word(t_token **token, char *line, int *i)
{
	char	*content;

	content = NULL;
	if (line[*i] == '\"')
		content = word_within_dqoutes(line, i);
	else if (line[*i] == '\'')
	{
		content = word_within_sqoutes(line, i);
	
	printf("==b==%c===\n", line[*i]);
	}
	else if (line[*i] == '$' && ft_isalnum(line[(*i) + 1]))
		content = expender(line, i);
	else
		content = word(line, i);
	if (!content)
		return (1);
	tokenadd_back(token, tokennew(content, WORD));
	return (0);
}