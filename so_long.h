/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:52 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 13:28:09 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "fcntl.h"
# include "libft/libft.h"
# include "time.h"
# include "unistd.h"
# include <mlx.h>

# define TOTAL_FRAMES 2
# define TILE_SIZE 50
# define FRAME_DELAY CLOCKS_PER_SEC
# define ENEMY_MOVE_DELAY CLOCKS_PER_SEC

# define GAME_OVER_MESSAGE "Game Over! You were caught by an enemy!"

enum					e_keys
{
	KEY_W = 119,
	KEY_S = 115,
	KEY_A = 97,
	KEY_D = 100,
	KEY_ESC = 65307,
	KEY_LEFT = 65361,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
};

enum					e_directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum					e_items
{
	EMPTY_SPACE = '0',
	WALL = '1',
	COLLECTIBLE = 'C',
	EXIT = 'E',
	PLAYER = 'P'
};

enum					e_entity_type
{
	ENTITY_ENEMY1,
	ENTITY_ENEMY2,
	ENTITY_COIN
};

typedef struct s_image
{
	void				*image;
	int					width;
	int					height;
}						t_image;

typedef struct s_sprites
{
	t_image				door;
	t_image				enemy1[4];
	t_image				enemy2[2];
	t_image				floor;
	t_image				player[4][TOTAL_FRAMES];
	t_image				coin[4];
	t_image				wall;
}						t_sprites;

typedef struct s_animation
{
	t_image				*frames;
	int					frame_count;
	int					current_frame;
	clock_t				last_update;
	int					update_interval;
}						t_animation;

typedef struct s_animated_entity
{
	t_point				pos;
	t_animation			anim;
	enum e_entity_type	type;
	clock_t				last_move;
}						t_animated_entity;

typedef struct s_entity_manager
{
	t_array				entities;
}						t_entity_manager;

typedef struct s_player
{
	t_point				pos;
	enum e_directions	facing;
	int					frame;
	int					moves;
}						t_player;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	char				**map;
	t_dimensions		dimensions;
	t_player			player;
	int					collectibles_count;
	t_sprites			sprites;
	t_entity_manager	*entity_manager;
	clock_t				game_start_time;
	t_point				enemies_pos[2];
	char				*obstacles;
	t_point				exit_pos;
}						t_game;

void					*get_game_instance(void);
void					game_over(char *message);

int						are_reachable(t_game *game);
int						is_reachable(t_game *game, t_point start,
							t_point target);
void					validate_map(t_game *game, void **map);
void					parse(t_game *game, char *map_filename);

void					update_entities(t_game *game);

t_animation				init_animation(t_image *frames, int frame_count,
							int update_interval);

t_animated_entity		*init_entity(t_point pos, t_animation anim,
							enum e_entity_type type);
void					add_entity(t_entity_manager *manager,
							t_animated_entity *entity);
void					remove_entity_at(t_entity_manager *manager, int x,
							int y, enum e_entity_type type);
t_animated_entity		*find_entity_at(t_entity_manager *manager, int x,
							int y);
t_entity_manager		*init_entity_manager(void);

void					render_game(t_game *game);
void					*compose_images(t_game *game, t_image *images,
							int count);

int						can_move_to(t_game *game, int new_x, int new_y);
int						key_hook(int keycode, t_game *game);

void					init_player(t_game *game);
void					init_coins(t_game *game);
void					init_enemies(t_game *game);
void					load_sprites(t_game *game);

void					*create_empty_image(void *mlx, int width, int height);

void					move_enemy(t_game *game, t_animated_entity *entity);

#endif
