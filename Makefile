CC = gcc
FLAGS = -lpthread
NAME = philo
HEADER = philosophers.h
MAIN = main.c

SRC = utils.c evals.c exit_func.c philosophers.c

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
