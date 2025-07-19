NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -f

SRC = init.c main.c monitor.c routine.c s_function.c utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
