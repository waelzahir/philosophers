CC = gcc
PFLAGS = -Wall -Wextra -Werror -lpthread
NAME = philo
HEADER = mandatory/philosophers.h
MAIN = mandatory/main.c

SRC = mandatory/utils.c mandatory/evals.c mandatory/exit_func.c mandatory/philosophers.c mandatory/routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) $(MAIN)
	$(CC) $(MAIN) $(PFLAGS)  $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ) $(BONUS_obj)
fclean: clean
	rm -rf $(NAME) $(BONUS)

re: fclean all

BFLAGS = -Wall -Wextra -Werror
BONUS = philo_bonus
BONUS_header = bonus/philosophers.h
BONUS_MAIN = bonus/main.c

BONUS_src = bonus/evals.c bonus/utils.c

BONUS_obj = $(BONUS_src:.c=.o)

bonus: $(BONUS)

$(BONUS): $(BONUS_obj) $(BONUS_header) $(BONUS_MAIN)
	$(CC) $(BONUS_MAIN) $(BFLAGS)  $(BONUS_obj) -o $(BONUS)

.phony: all clean fclean re
