.DEFAULT_GOAL := all

NAME = cub3D
SRC_DIR = sources
OBJ_DIR = objects
LIBFT_DIR = libft
MINILIBX_DIR = minilibx-linux
LDFLAGS = -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd
INCLUDE = -I includes -I $(MINILIBX_DIR)

SRCS = \
	$(SRC_DIR)/parsing/check_if_map_is_closed.c \
	$(SRC_DIR)/parsing/parse_convert_map.c \
	$(SRC_DIR)/parsing/parse_player.c \
	$(SRC_DIR)/parsing/parse_textures.c \
	$(SRC_DIR)/parsing/parsing.c \
	$(SRC_DIR)/parsing/parsing_utils.c \
	$(SRC_DIR)/parsing/utils.c \
	$(SRC_DIR)/parsing/validataion_utils.c \
	$(SRC_DIR)/parsing/validation.c \
	$(SRC_DIR)/ray_casting/ray_casting.c \
	$(SRC_DIR)/ray_casting/ray_casting_utils.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/hooks/hook_handlers.c \
	$(SRC_DIR)/hooks/hooks.c \
	$(SRC_DIR)/init/init.c \
	$(SRC_DIR)/init/load_textures.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/mlx_utils/mlx_utils.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -g3 # -fsanitize=address
LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX = $(MINILIBX_DIR)/libmlx.a

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MINILIBX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
