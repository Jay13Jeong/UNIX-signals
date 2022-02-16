NAME = server client
LIBFT_A = libft.a
HEADER = minitalk.h
SRC 		= client.c
SRC2 		= server.c
OBJ 		= $(SRC:%.c=%.o)
OBJ2 		= $(SRC2:%.c=%.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: all

server: $(LIBFT_A) $(OBJ2)
	$(CC) $(FLAGS) -o $@ $(OBJ2) -I$(HEADER) $(LIBFT_A)

client: $(LIBFT_A) $(OBJ)
	$(CC) $(FLAGS) -o $@ $(OBJ) -I$(HEADER) $(LIBFT_A)

$(LIBFT_A):
	cd libft; make
	cp libft/$(LIBFT_A) ./

clean:
	rm -rf $(OBJ) $(OBJ2)
	cd libft; make clean

fclean: clean
	rm -rf $(NAME) $(LIBFT_A)

re: fclean all

.PHONY: all bonus clean fclean re