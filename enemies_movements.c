/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_movments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:50:11 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/19 10:50:11 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_enemy_position(t_game *game, t_animated_entity *entity,
		t_point new_pos)
{
	entity->pos.x = new_pos.x;
	entity->pos.y = new_pos.y;
	if (entity->type == ENTITY_ENEMY1)
		game->enemies_pos[0] = entity->pos;
	else
		game->enemies_pos[1] = entity->pos;
}

static t_point	new_random_position(t_point pos)
{
	t_point	new_pos;
	int		random;

	random = arc4random_uniform(2) * 2 - 1;
	new_pos = pos;
	if (random >= 0)
		new_pos.x += arc4random_uniform(2) * 2 - 1;
	else
		new_pos.y += arc4random_uniform(2) * 2 - 1;
	return (new_pos);
}

void	move_enemy(t_game *game, t_animated_entity *entity)
{
	clock_t	current_time;
	t_point	distance;
	t_point	new_pos;

	current_time = clock();
	if (game->game_start_time == 0 || current_time < game->game_start_time
		+ CLOCKS_PER_SEC)
		return ;
	if ((current_time - entity->last_move) < CLOCKS_PER_SEC / 10)
		return ;
	entity->last_move = current_time;
	distance.x = game->player.pos.x - entity->pos.x;
	distance.y = game->player.pos.y - entity->pos.y;
	new_pos = entity->pos;
	if (abs(distance.x) > abs(distance.y))
		new_pos.x += if_else((distance.x > 0), 1, -1);
	else
		new_pos.y += if_else((distance.y > 0), 1, -1);
	if (game->map[new_pos.y][new_pos.x] == WALL)
		new_pos = new_random_position(entity->pos);
	if (can_move_to(game, new_pos.x, new_pos.y))
		update_enemy_position(game, entity, new_pos);
	if (entity->pos.x == game->player.pos.x
		&& entity->pos.y == game->player.pos.y)
		game_over(GAME_OVER_MESSAGE);
}
