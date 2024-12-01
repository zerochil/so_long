#include "so_long.h"

static int validate_map(t_game *game)
{
    int i, j;
    int player_count = 0, exit_count = 0;

    for (i = 0; i < game->map.height; i++)
    {
        for (j = 0; j < game->map.width; j++)
        {
            if (i == 0 || i == game->map.height - 1 || j == 0 || j == game->map.width - 1)
            {
                if (game->map.grid[i][j] != '1')
                    return 0; // Map not surrounded by walls
            }
            if (game->map.grid[i][j] == 'P')
            {
                player_count++;
                game->player.x = j;
                game->player.y = i;
            }
            else if (game->map.grid[i][j] == 'E')
                exit_count++;
            else if (game->map.grid[i][j] == 'C')
                game->map.collectibles++;
            else if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1')
                return 0; // Invalid character in map
        }
    }

    return (player_count == 1 && exit_count == 1 && game->map.collectibles > 0);
}

int parse_map(t_game *game, char *filename)
{
    int fd, i, j;
    char buffer[1024];
    ssize_t bytes_read;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return 0;

    game->map.height = 0;
    game->map.width = 0;
    game->map.collectibles = 0;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (i = 0; i < bytes_read; i++)
        {
            if (buffer[i] == '\n')
            {
                game->map.height++;
                if (game->map.width == 0)
                    game->map.width = i;
                else if (i != game->map.width)
                    return 0; // Map is not rectangular
            }
        }
    }

    if (bytes_read == -1)
    {
        close(fd);
        return 0;
    }

    game->map.grid = (char **)malloc(sizeof(char *) * game->map.height);
    if (!game->map.grid)
    {
        close(fd);
        return 0;
    }

    lseek(fd, 0, SEEK_SET);
    for (i = 0; i < game->map.height; i++)
    {
        game->map.grid[i] = (char *)malloc(sizeof(char) * (game->map.width + 1));
        if (!game->map.grid[i])
        {
            for (j = 0; j < i; j++)
                free(game->map.grid[j]);
            free(game->map.grid);
            close(fd);
            return 0;
        }
        read(fd, game->map.grid[i], game->map.width + 1);
        game->map.grid[i][game->map.width] = '\0';
    }

    close(fd);
    return validate_map(game);
}
