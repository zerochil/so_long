#include "so_long.h"

int init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return 0;

    game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "so_long");
    if (!game->win)
        return 0;

    // Load textures
    int width, height;
    game->img_player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &width, &height);
    game->img_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &width, &height);
    game->img_collectible = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &width, &height);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &width, &height);
    game->img_enemy = mlx_xpm_file_to_image(game->mlx, "textures/enemy.xpm", &width, &height);

    if (!game->img_player || !game->img_wall || !game->img_collectible || !game->img_exit || !game->img_enemy)
        return 0;

    game->player.moves = 0;

    return 1;
}

static int is_valid_move(t_game *game, int new_x, int new_y)
{
    if (new_x < 0 || new_x >= game->map.width || new_y < 0 || new_y >= game->map.height)
        return 0;

    if (game->map.grid[new_y][new_x] == '1')
        return 0;

    return 1;
}

int handle_input(int keycode, t_game *game)
{
    int new_x = game->player.x;
    int new_y = game->player.y;

    if (keycode == 13 || keycode == 126) // W or Up arrow
        new_y--;
    else if (keycode == 1 || keycode == 125) // S or Down arrow
        new_y++;
    else if (keycode == 0 || keycode == 123) // A or Left arrow
        new_x--;
    else if (keycode == 2 || keycode == 124) // D or Right arrow
        new_x++;
    else if (keycode == 53) // ESC
    {
        cleanup(game);
        exit(0);
    }

    if (is_valid_move(game, new_x, new_y))
    {
        game->player.x = new_x;
        game->player.y = new_y;
        game->player.moves++;

        ft_putstr("Moves: ");
        ft_putnbr(game->player.moves);
        ft_putstr("\n");

        if (game->map.grid[new_y][new_x] == 'C')
        {
            game->map.grid[new_y][new_x] = '0';
            game->map.collectibles--;
        }
        else if (game->map.grid[new_y][new_x] == 'E' && game->map.collectibles == 0)
        {
            ft_putstr("Congratulations! You've completed the game!\n");
            cleanup(game);
            exit(0);
        }
    }

    return 0;
}
