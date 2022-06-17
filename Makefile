CC = gcc
FLAGS = -lreadline -fsanitize=address
NAME = minishell

LIBFT = -L ./libft/  -lft
LEXER = -L ./srcs/lexer/  -llexer


ENVSRCS = $(addprefix srcs/env/, get_env.c)
TOKENSRCS = $(addprefix srcs/linked_lists/, tokennew.c tokenadd_front.c tokenadd_back.c tokensize.c tokenlast.c)

.PHONY: all clean fclean re libft/libft.a srcs/lexer/liblexer.a

all: $(NAME)

libft/libft.a:
	@make bonus -sC libft/

srcs/lexer/liblexer.a:
	@make -sC srcs/lexer/


$(NAME): libft/libft.a srcs/lexer/liblexer.a
	@$(CC) $(FLAGS) minishell.c $(LIBFT) $(ENVSRCS) $(TOKENSRCS) $(LEXER) -o $(NAME) -g
	@echo "\033[1;34mMinishell Compield successfuly\033[0m"


# dependencies:
# 	@make -sC ./libft/
# 	@make -sC ./srcs/lexer/

clean:
	@make clean -sC ./libft/
	@make clean -sC ./srcs/lexer/

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC ./libft/
	@make fclean -sC ./srcs/lexer/

re: fclean all
