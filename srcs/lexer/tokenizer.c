#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

char	get_space(t_token **token, char *line, int *i)
{
	if (tokenadd_back(token, tokennew(ft_strdup(" "), SPACE_)))
		return (1);
	while (ft_isspace(line[*i]))
		*i += 1;
	return (0);
}

/*----------------------------------------------------------------------------*/

char	check_last(t_token *token, int	macro)
{
	if (token)
	{
		if (tokenlast(token)->token == macro)
			return (1);
	}
	return (0);
}

/*----------------------------------------------------------------------------*/

char	is_last_operator(t_token *token)
{
	int	last;

	if (token)
	{
		last = tokenlast(token)->token;
		return ((last == RED_IN)
			|| (last == RED_OUT)
			|| (last == RED_APPEND)
			|| (last == HERE_DOC)
			|| (last == PIPE));
	}
	return (0);
}

/*----------------------------------------------------------------------------*/

char	tokenizer(t_token **token, char *line, t_env *env)
{
	int i;
	char	qoute;
	int		err;

	qoute = 0;
	err = 0;
	i = 0;
	while (line[i])
	{
		if (ft_strchr("\"\'", line[i]))
			qoute = !qoute;
		if (!qoute && is_operators(qoute, line[i], line[i + 1]))
			err += get_operator(token, line, &i);
		else if (ft_isascii(line[i]) && !ft_strchr("| <>", line[i]))
		{
			if (ft_strchr("\"\'", line[i]))
				qoute = !qoute;
			err += get_word(token, line, &i, env);
		}
		else if (!qoute && !is_last_operator(*token) && ft_isspace(line[i]))
			err += get_space(token, line, &i);
		else
			i++;
	}
	return (err);
}

/*

cat           <          infile        |        grep        -i        name          >    outfile

word space operator space word space pipe space word space word space word space operator word

cmd: "cat"          red_in: "infile"     pipe:       cmd: "grep -i name"  red_out: "outfile"

red_in: "infile"      cmd: "cat"         pipe:       cmd: "grep -i name"  red_out: "outfile"


*/