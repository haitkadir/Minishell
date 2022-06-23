CC = gcc
# FLAGS = -Wall -Wextra -Werror
NAME = liblexer.a

SOURCES = $(addprefix srcs/,lexer.c tokenizer.c get_operators.c get_operators_util.c get_word.c get_word_util.c check_errors.c check_qoutes.c)

OBJECTS = $(SOURCES:%.c=%.o)

$(NAME) : $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)
	@echo "\033[1;32mLexer Compield successfuly\033[0m"

all: $(NAME)

%.o : %.c lexer.h
	@$(CC) $(FLAGS) -o $@ -c $<

.INTERMEDIATE: $(OBJECTS)


clean:
	@rm -f srcs/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re