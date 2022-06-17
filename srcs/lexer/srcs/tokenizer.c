#include "../lexer.h"




char	tokenizer(t_token **token, char *line)
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
			get_here_doc(token, &i);
		else if (!qoute && line[i] == '<' && line[i + 1] != '<')
			get_red_in(token, &i);
		else if (!qoute && line[i] == '>' && line[i + 1] == '>')
			get_red_append(token, &i);
		else if (!qoute && line[i] == '>' && line[i + 1] != '>')
		{
			printf("=================Im here ===================\n");
			get_red_out(token, &i);
		}
		else if (!qoute && line[i] == '|' && line[i + 1] != '|')
			get_pipe(token, &i);
		else if (ft_isascii(line[i]) && !ft_strchr("#&();|<> \\`~/", line[i]))
		{
		printf("==before==%c===\n", line[i]);
			get_word(token, line, &i);
		printf("==after==%c===\n", line[i]);
		}
		else
			i++;
	}
	return (0);
}

/*

cat           <          infile        |        grep        -i        name          >    outfile

word space operator space word space pipe space word space word space word space operator word

cmd: "cat"          red_in: "infile"     pipe:       cmd: "grep -i name"  red_out: "outfile"

red_in: "infile"      cmd: "cat"         pipe:       cmd: "grep -i name"  red_out: "outfile"






*/