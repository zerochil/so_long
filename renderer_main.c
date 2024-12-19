/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:52 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/19 10:52:58 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	layer_entities(t_game *game, t_image *images, t_point pos,
		int *layer_count)
{
	t_animated_entity	*entity;
	int					i;

	i = 0;
	while (i < game->entity_manager->entities.size)
	{
		entity = game->entity_manager->entities.data[i];
		if (entity->pos.x == pos.x && entity->pos.y == pos.y)
		{
			if (entity->type == ENTITY_COIN)
				images[(*layer_count)++] = game->sprites.coin
				[entity->anim.current_frame];
			else if (entity->type == ENTITY_ENEMY1)
				images[(*layer_count)++] = game->sprites.enemy1
				[entity->anim.current_frame];
			else if (entity->type == ENTITY_ENEMY2)
				images[(*layer_count)++] = game->sprites.enemy2
				[entity->anim.current_frame];
		}
		i++;
	}
}

static void	render_tile(t_game *game, int x, int y)
{
	void	*composed_image;
	t_image	images[10];
	int		layer_count;

	layer_count = 1;
	if (game->map[y][x] == WALL)
		images[0] = game->sprites.wall;
	else
		images[0] = game->sprites.floor;
	if (game->map[y][x] == EXIT)
		images[layer_count++] = game->sprites.door;
	if (x == game->player.pos.x && y == game->player.pos.y)
		images[layer_count++] = game->sprites.player
		[game->player.facing][game->player.frame];
	layer_entities(game, images, (t_point){x, y}, &layer_count);
	composed_image = compose_images(game, images, layer_count);
	mlx_put_image_to_window(game->mlx, game->win, composed_image, x * TILE_SIZE,
		y * TILE_SIZE);
	mlx_destroy_image(game->mlx, composed_image);
}

void	render_game(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->dimensions.height)
	{
		x = 0;
		while (x < game->dimensions.width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
}
