#include "../parser.h"


tokenizer(t_token *token, char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		
	}
}



t_token	*parser(char *line)
{
	t_token *token;

	token = NULL;
	tokenizer(&token, line);
	return (token);
}