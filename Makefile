NAME        = pipex
BONUS_NAME  = pipex_bonus

CC          = clang
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I./mandatory -I./library/libft -I./library/get_next_line -I./bonus

SRC_DIR     = mandatory
BONUS_DIR   = bonus
OBJ_DIR     = objects
BONUS_OBJ_DIR = objects_bonus

LIBFT_DIR   = library/libft
LIBFT       = $(LIBFT_DIR)/libft.a

GNL_DIR     = library/get_next_line
GNL_SRC     = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJ     = $(GNL_SRC:$(GNL_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

SRCS        = $(SRC_DIR)/pipex.c \
              $(SRC_DIR)/utils.c

BONUS_SRCS  = $(BONUS_DIR)/pipex_bonus.c \
              $(BONUS_DIR)/utils_bonus.c

OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS  = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null 2>&1

bonus: $(LIBFT) $(BONUS_OBJS)
	@if [ -f "$(BONUS_DIR)/Makefile" ]; then \
		make -C $(BONUS_DIR) > /dev/null 2>&1; \
	else \
		$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME); \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -I$(GNL_DIR) -c $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@if [ -f "$(BONUS_DIR)/Makefile" ]; then \
		make -C $(BONUS_DIR) clean > /dev/null 2>&1; \
	fi

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@if [ -f "$(BONUS_DIR)/Makefile" ]; then \
		make -C $(BONUS_DIR) fclean > /dev/null 2>&1; \
	fi

re: fclean all

.PHONY: all bonus clean fclean re