CC = gcc
# FLAGS = -Wall -Wextra -Werror
NAME = libparser.a

SOURCES = $(addprefix srcs/,parser.c process_data.c get_cmd.c)

OBJECTS = $(SOURCES:%.c=%.o)

$(NAME) : $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)
	@echo "\033[1;32mParser Compield successfuly\033[0m"

all: $(NAME)

%.o : %.c parser.h
	@$(CC) $(FLAGS) -o $@ -c $<

.INTERMEDIATE: $(OBJECTS)


clean:
	@rm -f srcs/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re