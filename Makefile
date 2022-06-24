NAME = minishell

CC = gcc

CFLAGS = -lreadline -fsanitize=address -static-libasan -I includes/ -I libft/includes/

LIBFT = -L libft -lft

HEADER = minishell.h

# BUILTINS = cd echo env exit export pwd unset

ENV = get_env

# EXEC = bin builtin exec

MAIN = minishell

LEXER = lexer tokenizer get_operators get_operators_util get_word get_word_util check_errors check_qoutes

PARSER = parser process_data get_cmd

TOOLS = tokennew tokenadd_front tokenadd_back tokensize tokenlast tokendelone shell_new shell_last shell_size shelladd_back shelladd_front

SRC = $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/lexer/, $(LEXER))) \
	  $(addsuffix .c, $(addprefix srcs/parser/, $(PARSER))) \
	  $(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make bonus -sC libft/
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -sC libft/
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -sC libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: all
	./minishell

norm:
	norminette $(SRC) $(HEADER)

.PHONY: clean fclean re test norm













# CC = gcc
# FLAGS = -lreadline -fsanitize=address -static-libasan
# NAME = minishell


# .PHONY: all clean fclean re libft/libft.a \
# 		srcs/lexer/liblexer.a srcs/lexer/libparser.a

# all: $(NAME)

# libft/libft.a:
# 	@make bonus -sC libft/

# srcs/lexer/liblexer.a:
# 	@make -sC srcs/lexer/

# srcs/lexer/libparser.a:
# 	@make -sC srcs/parser/

# $(NAME): libft/libft.a srcs/lexer/liblexer.a srcs/lexer/libparser.a minishell $(ENVSRCS) $(LIST_FUNCS)
# 	@$(CC) $(FLAGS) minishell $(LIBFT) $(ENVSRCS) $(LIST_FUNCS) \
# 	$(PARSER) $(LEXER) -o $(NAME) -g
# 	@echo "\033[1;34mMinishell Compield successfuly\033[0m"

# clean:
# 	@make clean -sC ./libft/
# 	@make clean -sC ./srcs/lexer/
# 	@make clean -sC ./srcs/parser/

# fclean: clean
# 	@rm -f $(NAME)
# 	@make fclean -sC ./libft/
# 	@make fclean -sC ./srcs/lexer/
# 	@make fclean -sC ./srcs/parser/

# re: fclean all
