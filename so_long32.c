#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

#define TILE_SIZE 32
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_ESC 53

typedef struct s_game {
    void    *mlx;
    void    *win;
    void    *img_player;
    void    *img_wall;
    void    *img_collect;
    void    *img_exit;
    void    *img_ground;
    void    *img_enemy;
    char    **map;
    int     player_x;
    int     player_y;
    int     collectibles;
    int     moves;
    int     map_width;
    int     map_height;
}               t_game;

// Close game and free memory
int close_game(t_game *game) {
    for (int i = 0; i < game->map_height; i++)
        free(game->map[i]);
    free(game->map);
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
}

// Error handling and game exit
void error_exit(const char *msg) {
    printf("Error\n%s\n", msg);
    exit(EXIT_FAILURE);
}

// Dynamic map loading from a .ber file
char **load_map(const char *filename, t_game *game) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open map file");

    char *line;
    char **map = (char **)malloc(sizeof(char *) * 100); // assuming max 100 rows
    int i = 0;

    while ((line = get_next_line(fd)) != NULL) {
        map[i] = ft_strdup(line);
        free(line);
        i++;
    }
    map[i] = NULL; // null-terminate
    close(fd);

    game->map_width = ft_strlen(map[0]);
    game->map_height = i;
    
    return map;
}

// Map validation
void validate_map(t_game *game) {
    int exit_count = 0, player_count = 0, collectible_count = 0;
    
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            char tile = game->map[y][x];

            // Map must be surrounded by walls ('1')
            if (y == 0 || y == game->map_height - 1 || x == 0 || x == game->map_width - 1) {
                if (tile != '1')
                    error_exit("Map must be surrounded by walls");
            }

            // Count player, exit, collectibles
            if (tile == 'P') {
                player_count++;
                game->player_x = x;
                game->player_y = y;
            } else if (tile == 'E')
                exit_count++;
            else if (tile == 'C')
                collectible_count++;
        }
    }

    if (player_count != 1)
        error_exit("Map must have exactly one player position");
    if (exit_count != 1)
        error_exit("Map must have exactly one exit");
    if (collectible_count < 1)
        error_exit("Map must have at least one collectible");
    
    game->collectibles = collectible_count;
}

// Check if there's a valid path from the player to the exit and all collectibles
int flood_fill(char **map, int x, int y) {
    if (map[y][x] == '1' || map[y][x] == 'X')
        return 0;
    if (map[y][x] == 'E' || map[y][x] == 'C')
        return 1;
    
    map[y][x] = 'F'; // Mark as visited
    return flood_fill(map, x + 1, y) || flood_fill(map, x - 1, y) ||
           flood_fill(map, x, y + 1) || flood_fill(map, x, y - 1);
}

void check_valid_path(t_game *game) {
    char **tmp_map = (char **)malloc(sizeof(char *) * game->map_height);
    for (int i = 0; i < game->map_height; i++)
        tmp_map[i] = ft_strdup(game->map[i]);

    if (!flood_fill(tmp_map, game->player_x, game->player_y))
        error_exit("No valid path to exit or collectibles");

    for (int i = 0; i < game->map_height; i++)
        free(tmp_map[i]);
    free(tmp_map);
}

// Draw individual tiles based on the map content
void draw_tile(t_game *game, int x, int y, void *img) {
    mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y * TILE_SIZE);
}

// Render the entire map, including player and enemies
void render_map(t_game *game) {
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            char tile = game->map[y][x];
            if (tile == '1')
                draw_tile(game, x, y, game->img_wall);
            else if (tile == '0')
                draw_tile(game, x, y, game->img_ground);
            else if (tile == 'P')
                draw_tile(game, x, y, game->img_player);
            else if (tile == 'C')
                draw_tile(game, x, y, game->img_collect);
            else if (tile == 'E')
                draw_tile(game, x, y, game->img_exit);
            else if (tile == 'X')
                draw_tile(game, x, y, game->img_enemy);
        }
    }

    // Display move count and collectibles on screen
    char *move_str = ft_itoa(game->moves);
    char *collect_str = ft_itoa(game->collectibles);
    mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, "Moves: ");
    mlx_string_put(game->mlx, game->win, 80, 10, 0xFFFFFF, move_str);
    mlx_string_put(game->mlx, game->win, 10, 30, 0xFFFFFF, "Collectibles: ");
    mlx_string_put(game->mlx, game->win, 150, 30, 0xFFFFFF, collect_str);
    free(move_str);
    free(collect_str);
}

// Move player with collision detection and collectible/enemy/exit interaction
int move_player(t_game *game, int new_x, int new_y) {
    char next_tile = game->map[new_y][new_x];
    
    if (next_tile == '1') // Wall collision
        return 0;

    if (next_tile == 'C') { // Collect collectible
        game->collectibles--;
        printf("Collected! Remaining: %d\n", game->collectibles);
    }

    if (next_tile == 'X') { // Enemy collision
        printf("You were caught by an enemy! Game over.\n");
        close_game(game);
    }

    if (next_tile == 'E' && game->collectibles == 0) { // Exit after all collectibles collected
        printf("You won! Moves: %d\n", game->moves);
        close_game(game);
    }

    game->map[game->player_y][game->player_x] = '0'; // Clear old position
    game->map[new_y][new_x] = 'P';  // Set new position
    game->player_x = new_x;
    game->player_y = new_y;
    game->moves++;
    printf("Moves: %d\n", game->moves);
    return 1;
}

// Handle key presses for movement
int handle_keypress(int keycode, t_game *game) {
    if (keycode == KEY_ESC)
        close_game(game);

    int new_x = game->player_x;
    int new_y = game->player_y;

    if (keycode == KEY_W)
        new_y--;
    else if (keycode == KEY_A)
        new_x--;
    else if (keycode == KEY_S)
        new_y++;
    else if (keycode == KEY_D)
        new_x++;

    if (move_player(game, new_x, new_y))
        render_map(game);
    
    return 0;
}

// Function to load sprites
void load_sprites(t_game *game) {
    int img_width, img_height;
    game->img_player = mlx_xpm_file_to_image(game->mlx, "player.xpm", &img_width, &img_height);
    game->img_wall = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &img_width, &img_height);
    game->img_collect = mlx_xpm_file_to_image(game->mlx, "collectible.xpm", &img_width, &img_height);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "exit.xpm", &img_width, &img_height);
    game->img_ground = mlx_xpm_file_to_image(game->mlx, "ground.xpm", &img_width, &img_height);
    game->img_enemy = mlx_xpm_file_to_image(game->mlx, "enemy.xpm", &img_width, &img_height);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./so_long <map_file.ber>\n");
        return 1;
    }

    t_game game;
    game.mlx = mlx_init();
    
    game.map = load_map(argv[1], &game);
    validate_map(&game);
    check_valid_path(&game);

    game.moves = 0;
    
    game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE, game.map_height * TILE_SIZE, "So Long!");
    load_sprites(&game);
    
    render_map(&game);
    
    mlx_hook(game.win, 17, 0, close_game, &game); // Handle window close event
    mlx_key_hook(game.win, handle_keypress, &game); // Handle key press
    mlx_loop(game.mlx);

    return 0;
}

