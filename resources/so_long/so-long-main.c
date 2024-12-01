#include "so_long.h"

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
    {
        ft_putstr("Error\nUsage: ./so_long map_file.ber\n");
        return (1);
    }

    if (!parse_map(&game, argv[1]))
    {
        ft_putstr("Error\nInvalid map\n");
        return (1);
    }

    if (!init_game(&game))
    {
        ft_putstr("Error\nFailed to initialize game\n");
        cleanup(&game);
        return (1);
    }

    mlx_key_hook(game.win, handle_input, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);

    cleanup(&game);
    return (0);
}

int game_loop(t_game *game)
{
    render_game(game);
    return (0);
}

void cleanup(t_game *game)
{
    int i;

    if (game->map.grid)
    {
        for (i = 0; i < game->map.height; i++)
            free(game->map.grid[i]);
        free(game->map.grid);
    }

    if (game->mlx && game->win)
        mlx_destroy_window(game->mlx, game->win);

    // Free textures if they were loaded
    // Add more cleanup as necessary
}
