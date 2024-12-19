/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:52 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 08:59:29 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_game *game)
{
	game->player.frame = 0;
	game->player.facing = DOWN;
	game->player.moves = 0;
	game->map[game->player.pos.y][game->player.pos.x] = EMPTY_SPACE;
}

void	init_coins(t_game *game)
{
	t_animation			coin_anim;
	t_animated_entity	*coin;
	t_point				pos;
	int					y;
	int					x;

	coin_anim = init_animation(game->sprites.coin, 4, FRAME_DELAY / 10);
	y = 0;
	while (y < game->dimensions.height)
	{
		x = 0;
		while (x < game->dimensions.width)
		{
			if (game->map[y][x] == COLLECTIBLE)
			{
				pos.x = x;
				pos.y = y;
				coin = init_entity(pos, coin_anim, ENTITY_COIN);
				add_entity(game->entity_manager, coin);
			}
			x++;
		}
		y++;
	}
}

static int	init_enemy_if_possible(t_game *game, t_animation animation,
		enum e_entity_type type, t_point pos)
{
	t_animated_entity	*enemy;

	if (game->map[pos.y][pos.x] != EMPTY_SPACE)
		return (0);
	if (abs(pos.x - game->player.pos.x) <= 1 && abs(pos.y
			- game->player.pos.y) <= 1)
		return (0);
	game->map[pos.y][pos.x] = 'X';
	if (!is_reachable(game, game->player.pos, game->exit_pos))
	{
		game->map[pos.y][pos.x] = '0';
		return (0);
	}
	game->map[pos.y][pos.x] = '0';
	enemy = init_entity(pos, animation, type);
	add_entity(game->entity_manager, enemy);
	if (type == ENTITY_ENEMY1)
		game->enemies_pos[0] = pos;
	else
		game->enemies_pos[1] = pos;
	return (1);
}

void	init_enemies(t_game *game)
{
	t_point				pos;
	int					count;
	int					max_attempts;
	t_animation			anim[2];
	enum e_entity_type	type[2];

	count = 0;
	max_attempts = 1000;
	anim[0] = init_animation(game->sprites.enemy1, 4, FRAME_DELAY / 10);
	anim[1] = init_animation(game->sprites.enemy2, 2, FRAME_DELAY / 10);
	type[0] = ENTITY_ENEMY1;
	type[1] = ENTITY_ENEMY2;
	game->obstacles = "1X";
	while (count < 2 && max_attempts > 0)
	{
		pos.x = arc4random() % game->dimensions.width;
		pos.y = arc4random() % game->dimensions.height;
		count += init_enemy_if_possible(game, anim[count], type[count], pos);
		max_attempts--;
	}
	game->obstacles = "1";
}
