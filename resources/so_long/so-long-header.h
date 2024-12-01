#ifndef SO_LONG_H
#define SO_LONG_H

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#define TILE_SIZE 32
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct s_player {
    int x;
    int y;
    int moves;
} t_player;

typedef struct s_map {
    char **grid;
    int width;
    int height;
    int collectibles;
} t_map;

typedef struct s_game {
    void *mlx;
    void *win;
    t_map map;
    t_player player;
    void *img_player;
    void *img_wall;
    void *img_collectible;
    void *img_exit;
    void *img_enemy;
} t_game;

// Function prototypes
int parse_map(t_game *game, char *filename);
int init_game(t_game *game);
int handle_input(int keycode, t_game *game);
void render_game(t_game *game);
int game_loop(t_game *game);
void cleanup(t_game *game);

// Utility functions
void ft_putstr(char *str);
void ft_putnbr(int n);
int ft_strcmp(const char *s1, const char *s2);

#endif
