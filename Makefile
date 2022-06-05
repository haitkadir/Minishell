CC = gcc
FLAGS = -lreadline
NAME = minishell

LIBFT = -L ./libft/  -lft
LEXER = -L ./srcs/lexer/  -llexer
PARSER = -L ./srcs/parser/  -lparser


SOURCES = minishell.c

all: $(NAME)

dependencies:
	@make -sC ./libft/
	@make -sC ./srcs/lexer/

$(NAME): dependencies
	@$(CC) $(FLAGS) $(SOURCES) $(LIBFT) $(LEXER) -o $(NAME)
	@echo "\033[1;34mMinishell Compield successfuly\033[0m"


clean:
	@make clean -sC ./libft/
	@make clean -sC ./srcs/lexer/

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC ./libft/
	@make fclean -sC ./srcs/lexer/

re: fclean all

.PHONY: all clean fclean re