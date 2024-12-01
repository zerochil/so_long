#include "so_long.h"

void render_game(t_game *game)
{
    int x, y;

    for (y = 0; y < game->map.height; y++)
    {
        for (x = 0; x < game->map.width; x++)
        {
            int screen_x = x * TILE_SIZE;
            int screen_y = y * TILE_SIZE;

            switch (game->map.grid[y][x])
            {
                case '1':
                    mlx_put_image_to_window(game->mlx, game->win, game->img_wall, screen_x, screen_y);
                    break;
                case 'C':
                    mlx_put_image_to_window(game->mlx, game->win, game->img_collectible, screen_x, screen_y);
                    break;
                case 'E':
                    mlx_put_image_to_window(game->mlx, game->win, game->img_exit, screen_x, screen_y);
                    break;
                // Add case for enemy if implemented
            }
        }
    }

    // Render player
    mlx_put_image_to_window(game->mlx, game->win, game->img_player, game->player.x * TILE_SIZE, game->player.y * TILE_