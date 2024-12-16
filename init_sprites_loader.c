/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:52 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 08:43:26 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_image(void *img)
{
	t_game	*game;

	game = get_game_instance();
	mlx_destroy_image(game->mlx, img);
}

static t_image	load_image(void *mlx, char *filepath)
{
	t_image	image;
	char	pathname[256];

	pathname[0] = '\0';
	ft_strcat(pathname, "sprites/");
	ft_strcat(pathname, filepath);
	image.image = mlx_xpm_file_to_image(mlx, pathname, &image.width,
			&image.height);
	if (!image.image)
		error("Error\nFailed to read image");
	track_resource(image.image, destroy_image);
	return (image);
}

void	load_sprites(t_game *game)
{
	t_sprites	*sprites;

	sprites = &game->sprites;
	sprites->door = load_image(game->mlx, "door.xpm");
	sprites->enemy1[0] = load_image(game->mlx, "enemy-1-1.xpm");
	sprites->enemy1[1] = load_image(game->mlx, "enemy-1-2.xpm");
	sprites->enemy1[2] = load_image(game->mlx, "enemy-1-3.xpm");
	sprites->enemy1[3] = load_image(game->mlx, "enemy-1-4.xpm");
	sprites->enemy2[0] = load_image(game->mlx, "enemy-2-1.xpm");
	sprites->enemy2[1] = load_image(game->mlx, "enemy-2-2.xpm");
	sprites->floor = load_image(game->mlx, "floor.xpm");
	sprites->player[UP][0] = load_image(game->mlx, "player-up-1.xpm");
	sprites->player[UP][1] = load_image(game->mlx, "player-up-2.xpm");
	sprites->player[DOWN][0] = load_image(game->mlx, "player-down-1.xpm");
	sprites->player[DOWN][1] = load_image(game->mlx, "player-down-2.xpm");
	sprites->player[LEFT][0] = load_image(game->mlx, "player-left-1.xpm");
	sprites->player[LEFT][1] = load_image(game->mlx, "player-left-2.xpm");
	sprites->player[RIGHT][0] = load_image(game->mlx, "player-right-1.xpm");
	sprites->player[RIGHT][1] = load_image(game->mlx, "player-right-2.xpm");
	sprites->coin[0] = load_image(game->mlx, "coin_f0.xpm");
	sprites->coin[1] = load_image(game->mlx, "coin_f1.xpm");
	sprites->coin[2] = load_image(game->mlx, "coin_f2.xpm");
	sprites->coin[3] = load_image(game->mlx, "coin_f3.xpm");
	sprites->wall = load_image(game->mlx, "wall.xpm");
}
