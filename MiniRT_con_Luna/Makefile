# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                   +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/01/01                               #+#    #+#             #
#    Updated: 2025/01/01                               ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME        = miniRT

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# ===================== #
# ===== DIRECTORIES ==== #
# ===================== #

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = includes

LIBFT_DIR   = libft
MLX_DIR     = minilibx-linux   # <-- Cambiado a la minilibx clásica

# ===================== #
# ===== LIBRARIES ===== #
# ===================== #

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = minilibx-linux/libmlx.a

# Para Linux: se necesita -lX11 -lXext -lm
LIBS        = $(LIBFT) $(MLX)
MLX_FLAGS   = -lX11 -lXext -lm

# ===================== #
# ===== SOURCES ======= #
# ===================== #

SRC_FILES   = \
    main.c \
    ft_error.c \
    utils.c \
    objects.c \
    \
    maths/vectors.c \
    maths/vectors_utils.c \
    maths/object_utils.c \
    maths/camera_utils.c \
    maths/light_utils.c\
    \
    parse/ft_parse.c \
    parse/ft_parse_tokens.c \
    parse/ft_parse_value.c \
    parse/ft_utils_parse.c \
    parse/ft_utils_parse_2.c \
    parse/read_life.c\
    \
    raytracing/intersect_cylinder.c \
    raytracing/intersect_plane.c \
    raytracing/intersect_sphere.c \
    raytracing/ray.c \
    raytracing/intersect.c \
    raytracing/normals.c \
    raytracing/lighting.c \
    raytracing/raytrace.c  \
    raytracing/pixel.c

SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ===================== #
# ===== RULES ========= #
# ===================== #

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/maths
	mkdir -p $(OBJ_DIR)/parse
	mkdir -p $(OBJ_DIR)/raytracing

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -c $< -o $@

# ===================== #
# ===== LIB RULES ===== #
# ===================== #

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

# ===================== #
# ===== CLEAN ========= #
# ===================== #

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
