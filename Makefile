CC = gcc
FLAGS = -Wall -Wextra -Werror -lpthread
NAME = philo
HEADER = mandatory/philosophers.h
MAIN = mandatory/main.c

SRC = mandatory/utils.c mandatory/evals.c mandatory/exit_func.c mandatory/philosophers.c mandatory/routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) $(MAIN)
	$(CC) $(MAIN) $(FLAGS)  $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)

re: fclean all

.phony: all clean fclean re
