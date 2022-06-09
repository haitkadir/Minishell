CC = gcc
FLAGS = -lreadline
NAME = minishell

LIBFT = -L ./libft/  -lft
LEXER = -L ./srcs/lexer/  -llexer
PARSER = -L ./srcs/parser/  -lparser


SOURCES = $(addprefix srcs/linked_lists/,tokennew.c tokenadd_front.c tokenadd_back.c tokensize.c tokenlast.c)

.PHONY: srcs/lexer/liblexer.a

all: dependencies $(NAME)

srcs/lexer/liblexer.a:
	@make -sC srcs/lexer/

$(NAME): srcs/lexer/liblexer.a
	@$(CC) $(FLAGS) minishell.c $(SOURCES) $(LIBFT) $(LEXER) -o $(NAME) -g
	@echo "\033[1;34mMinishell Compield successfuly\033[0m"


dependencies:
	@make -sC ./libft/
	@make -sC ./srcs/lexer/

clean:
	@make clean -sC ./libft/
	@make clean -sC ./srcs/lexer/

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC ./libft/
	@make fclean -sC ./srcs/lexer/

re: fclean all

.PHONY: all clean fclean re