NAME = fdf

SRC = $(addprefix $(SRC_DIR), main.c draw.c draw_line.c read_input.c events.c helpers.c transform_vertex.c)

OBJ = $(addprefix $(OBJ_DIR), $(SRC:$(SRC_DIR)%.c=%.o))

SRC_DIR = src/
OBJ_DIR = obj/

HEADER = include/fdf.h

LIBFT = libft.a

MLX = mlx.a

INC = -I include -I libft -I minilibx-linux

LIBS = -lft -L libft -lmlx -L minilibx-linux -lXext -lX11 -L /opt/X11/lib

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INC) $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

$(LIBFT):
	@$(MAKE) -C libft

$(MLX):
	@$(MAKE) -C minilibx-linux

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft clean
	@$(MAKE) -C minilibx-linux clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all re clean fclean