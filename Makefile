NAME = so_long
SRCS = so_long_main.c utils.c \
	   init_entities.c init_sprites_loader.c \
	   parser_main.c parser_map_validator.c parser_path_finder.c \
	   player_movements.c enemies_movements.c\
	   renderer_image_composer.c renderer_main.c \
	   animation_entity_manager_bonus.c animation_updater_bonus.c
OBJS_DIR = ._objects/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	$(CC) $(OBJS) -L/usr/lib -lmlx -lXext -lX11 -lm -lz -Llibft -lft -o $(NAME)

$(LIBFT): FORCE
	@make -C libft --no-print-directory
	
FORCE:

$(OBJS_DIR)%.o: %.c so_long.h
	$(CC) -I/usr/include -O3 -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
	@make -C libft --no-print-directory clean

fclean: clean
	rm -rf $(NAME)
	@make -C libft --no-print-directory fclean

re: fclean all

.PHONY: all clean fclean re FORCE
