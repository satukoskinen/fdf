NAME = fdf

SRC = $(addprefix $(SRC_DIR), main.c draw.c draw_line.c read_input.c events.c helpers.c transform_vertex.c)

OBJ = $(addprefix $(OBJ_DIR), $(SRC:$(SRC_DIR)%.c=%.o))

SRC_DIR = src/
OBJ_DIR = obj/

HEADER = include/fdf.h

LIBFT = libft.a

MLX = mlx.a

INC = -I include -I libft -I minilibx

LIBS = -lft -L libft -lmlx -L minilibx -lXext -lX11 -L /opt/X11/lib

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INC) $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C libft

$(MLX):
	@$(MAKE) -C minilibx

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C libft clean
	@$(MAKE) -C minilibx clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all re clean fclean
