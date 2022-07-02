#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

char	is_redirection(t_token *token)
{
	return ((token->token == RED_IN)
		|| (token->token == RED_OUT)
		|| (token->token == RED_APPEND)
		|| (token->token == HERE_DOC));
}

/*----------------------------------------------------------------------------*/

char	check_operators_syntax(t_token *token)
{
	while (token)
	{
		if (is_redirection(token) && !token->content)
			return (1);
		token = token->next;
	}
	return (0);
}

/*----------------------------------------------------------------------------*/

char	check_errors(t_token *token)
{
	if (check_operators_syntax(token))
		return (put_error("syntax error", "near unexpected token `newline'", 258), 1);
	return (0);
}








































// /*----------------------------------------------------------------------------*/

// char check_in_out_operators(char *line, char oper)
// {
// 	int i;
// 	char flag;

// 	i = 0;
// 	flag = 0;
// 	while(line[i])
// 	{
// 		if (line[i] == oper && line[i + 1] == oper)
// 			i += 2;
// 		if (!flag && line[i] == oper)
// 			flag = !flag;
// 		else if (flag && line[i] == oper)
// 			return (1);
// 		if (flag && !ft_strchr("#&();|<> \\`~/", line[i]))
// 			flag = !flag;
// 		i++;
// 	}
// 	if (flag)
// 		return (1);
// 	return (0);
// }

// /*----------------------------------------------------------------------------*/

// char	check_errors(char *line)
// {
// 	if (check_qoutes(line))
// 		return (1);
// 	if (check_in_out_operators(line, '<'))
// 		return (1);
// 	if (check_in_out_operators(line, '>'))
// 		return (1);
// 	return (0);
// }