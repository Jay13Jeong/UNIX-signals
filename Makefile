NAME = server client
LIBFT_A = libft/libft.a
HEADER = minitalk.h
CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: $(NAME)

server: libft
	$(CC) $(FLAGS) -c $@.c -I$(HEADER)
	$(CC) $(FLAGS) -o $@ $@.o $(LIBFT_A)

client: libft
	$(CC) $(FLAGS) -c $@.c -I$(HEADER)
	$(CC) $(FLAGS) -o $@ $@.o $(LIBFT_A)

libft:
	make -C libft

clean:
	rm -rf *.o
	make -C libft clean

fclean: clean
	rm -rf $(NAME) $(LIBFT)

re: fclean all

.PHONY: all bonus libft clean fclean re
