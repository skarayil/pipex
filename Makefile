LIBFT_DIR       = library/libft
MANDATORY_DIR   = mandatory
BONUS_DIR       = bonus

CC              = clang
CFLAGS          = -Wall -Wextra -Werror
INCLUDES        = -I$(MANDATORY_DIR) -I$(LIBFT_DIR)

MANDATORY_SRCS  = $(MANDATORY_DIR)/pipex.c \
                  $(MANDATORY_DIR)/utils.c

MANDATORY_OBJS  = $(MANDATORY_SRCS:.c=.o)

NAME            = pipex
LIBFT           = $(LIBFT_DIR)/libft.a

.SILENT:

all: $(LIBFT) $(NAME)

$(NAME): $(MANDATORY_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(MANDATORY_OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -sC $(LIBFT_DIR)

bonus: all
	if [ -f "$(BONUS_DIR)/Makefile" ]; then \
		make -sC $(BONUS_DIR); \
	fi

clean:
	rm -f $(MANDATORY_OBJS)
	make -sC $(LIBFT_DIR) clean
	if [ -f "$(BONUS_DIR)/Makefile" ]; then \
		make -sC $(BONUS_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME)
	make -sC $(LIBFT_DIR) fclean
	if [ -f "$(BONUS_DIR)/Makefile" ]; then \
		make -sC $(BONUS_DIR) fclean; \
	fi

re: fclean all

.PHONY: all bonus clean fclean re