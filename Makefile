.DEFAULT_GOAL := all

NAME = cub3D
SRC_DIR = src
LIBFT_DIR = libft
MINILIBX_DIR = minilibx-linux
LDFLAGS = -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd
INCLUDE = -I includes -I $(MINILIBX_DIR)

SRCS = $(shell find $(SRC_DIR) -maxdepth 1 -name "*.c")
OBJS = $(SRCS:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX = $(MINILIBX_DIR)/libmlx.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MINILIBX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
