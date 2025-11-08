CC      := cc
CFLAGS  := -Wall -Wextra -Werror
NAME_C  := client
NAME_S  := server
SRC_C   := client_sig.c client_tx.c utils.c
SRC_S   := server.c server_sig.c utils.c
HEAD    := minitalk.h

.PHONY: all clean fclean re bonus

all: $(NAME_C) $(NAME_S)

$(NAME_C): $(SRC_C) $(HEAD)
	$(CC) $(CFLAGS) -o $@ $(SRC_C)

$(NAME_S): $(SRC_S) $(HEAD)
	$(CC) $(CFLAGS) -o $@ $(SRC_S)

bonus: all

clean:
	@echo "nothing to clean"

fclean: clean
	$(RM) $(NAME_C) $(NAME_S)

re: fclean all
