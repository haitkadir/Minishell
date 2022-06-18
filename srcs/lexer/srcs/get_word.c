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

/*----------------------------------------------------------------------------*/

static	char	*get_chunk(char *line, int *i)
{
	int len;
	int start;

	len = 0;
	start = *i;
	while (line[*i])
	{
		if (ft_strchr("$\"", line[*i]))
			break ;
		len++;
		*i += 1;
	}
	if (!len)
		return (NULL);
	return (ft_substr(line, start, len));
}


char	*word_within_dqoutes(char *line, int *i)
{
	char	*string;
	char	*substring;
	char	*tmp;

	*i += 1;
	string = NULL;
	exit(0);
	while (line[(*i) + 1])
	{
		substring = NULL;
		if (line[*i] == '$')
			substring = expender(line, i);
		else
			substring = get_chunk(line, i);
		if (!string)
			string = substring;
		else
		{
			tmp = string;
			string = ft_strjoin(tmp, substring);
			free(tmp);
			tmp = NULL;
		}

		if (substring)
			free(substring);
	}
	return (string);
}






















// char	*word_within_dqoutes(char *line, int *i)
// {
// 	int		len;
// 	int		start;
// 	char	expend;
// 	char	*word;
// 	char	*tmp;

// 	len = 0;
// 	*i += 1;
// 	start = *i;
// 	word = NULL;
// 	while (line[*i])
// 	{
// 		if (ft_strchr("\"", line[*i]))
// 		{
// 			// *i += 1;
// 			break ;
// 		}
// 		else if (line[*i] == '$' && ft_isalnum(line[*i + 1]))
// 		{
// 			if (!word)
// 				word = ft_substr(line, start, len);
// 			else
// 			{
// 				tmp = word;
// 				word = ft_strjoin(tmp, ft_substr(line, start, len));
// 				free(tmp);
// 			}
// 			tmp = word;
// 			word = ft_strjoin(tmp, expender(line, i));
// 			free(tmp);
// 			continue;
// 		}
// 		len++;
// 		*i += 1;
// 	}
// 	if (!word)
// 		word = ft_substr(line, start, len);
// 	return (word);
// }

/*----------------------------------------------------------------------------*/

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
	return (ft_substr(line, start, len));
}

/*----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------*/

char get_word(t_token **token, char *line, int *i, char *qoute)
{
	char	*content;

	content = NULL;
	if (line[*i] == '\"')
	{
		content = word_within_dqoutes(line, i);
		*qoute = !*qoute;
	}
	else if (line[*i] == '\'')
	{
		content = word_within_sqoutes(line, i);
		*qoute = !*qoute;
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