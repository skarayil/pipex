LIBFT_DIR		= library/libft
MANDATORY_DIR	= mandatory
BONUS_DIR		= bonus


CC				= clang
CFLAGS			= -Wall -Wextra -Werror
INCLUDES		= -I$(MANDATORY_DIR) -I$(LIBFT_DIR)


MANDATORY_SRCS	= $(MANDATORY_DIR)/pipex.c \
				  $(MANDATORY_DIR)/utils.c

MANDATORY_OBJS	= $(MANDATORY_SRCS:.c=.o)


NAME			= pipex
LIBFT			= $(LIBFT_DIR)/libft.a


all: $(LIBFT) $(NAME)


$(NAME): $(MANDATORY_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(MANDATORY_OBJS) $(LIBFT) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


$(LIBFT):
	@make -C $(LIBFT_DIR)


bonus: all
	@if [ -f "$(BONUS_DIR)/Makefile" ]; then \
		make -C $(BONUS_DIR); \
	else \
		echo "Bonus Makefile not found"; \
	fi


clean:
	@rm -f $(MANDATORY_OBJS)
	@make -C $(LIBFT_DIR) clean
	@if [ -f "$(BONUS_DIR)/Makefile" ]; then \
		make -C $(BONUS_DIR) clean; \
	fi


fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@if [ -f "$(BONUS_DIR)/Makefile" ]; then \
		make -C $(BONUS_DIR) fclean; \
	fi


re: fclean all


.PHONY: all bonus clean fclean re
