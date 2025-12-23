CC   = cc

MAKEFLAGS	= --no-print-directory --silent

NAME	 = miniRT

CFLAGS	 =	-Wextra -Wall -Werror\
			-Wunreachable-code\
			-I include\
			-O3 -g3\

DEBUG	 =	-g3 -fsanitize=address

CPPFLAGS =	-MMD

LIBMLX	= ./inc/MLX42
LIBFT	= ./inc/libft

HEADERS = -I ./include -I $(LIBMLX)/include -I $(LIBFT)

LIBS	=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBS	+=	$(LIBFT)/libft.a

VPATH	=	src/:						\
			src/renderer/maths/:		\
			src/renderer/objects/:		\
			src/renderer/rays/:			\
			src/renderer/render/:		\
			src/interface/:	\
			src/renderer/utils/:		\
			src/parse/:					\
			src/parse/utils/:			\
			src/errors/:


SRCS =	main.c							\
		vector.c						\
		2vectors.c						\
		points.c						\
		normal.c						\
		lights.c						\
		camera.c						\
		plane.c							\
		sphere.c						\
		cylinder.c						\
		ambient.c						\
		difuse.c						\
		intersects.c					\
		light.c							\
		rays.c							\
		mlx_utils.c						\
		render_img.c					\
		pixel.c							\
		utils/ft_atolf.c				\
		utils/is_space_split.c			\
		add_vals.c						\
		check_format.c					\
		get_vars.c						\
		parse.c							\
		read_file.c						\
		ft_error.c						\
		change_obj_utils.c				\
		print_utils.c					\
		rotation.c						\
		take_input.c					\
		mem.c

TEST = parse_unit_tests.c				\

OBJS = $(patsubst %.c, objs/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

all: libmlx libft $(NAME) normi

libmlx:
	@cmake -DDEBUG=1 $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && printf "Linking: $(NAME)\n"

objs/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf objs
	@rm -rf $(LIBMLX)/build
	@make fclean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

-include $(DEPS)

gpush: # use: make gpush m="cambios rapidos"
	@if [ -z "$(m)" ]; then \
		echo "❌ Error: falta el mensaje. Usa: make gpush m=\"tu mensaje\""; \
	else \
		git add . && git commit -m "$(m)" && git push; \
	fi

test_parse: $(NAME)
	@for f in scn/error/*; do \
		printf "\n === Ejecutando: %s ===\n" "$$f";\
		./miniRT "$$f";\
		printf "\n[Presiona Enter para probar el siguiente archivo]\n";\
		read _;\
		printf "\n-------------------------------------------------\n";\
	done

all_scenes: $(NAME)
	@for f in scn/*/*; do \
		printf "\n === Ejecutando: %s ===\n" "$$f";\
		./miniRT "$$f";\
		printf "\n[Presiona Enter para probar el siguiente archivo]\n";\
		read _;\
		printf "\n-------------------------------------------------\n";\
	done

normi:
	norminette ./src/ $(LIBFT) ./inc/miniRT.h\

.PHONY: all clean fclean re libmlx libft gpush

