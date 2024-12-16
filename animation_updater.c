/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_updater.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:06:36 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 10:46:00 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_animation	create_animation(t_image *frames, int frame_count,
		int update_interval)
{
	t_animation	anim;

	anim.frames = frames;
	anim.frame_count = frame_count;
	anim.current_frame = 0;
	anim.last_update = clock();
	anim.update_interval = update_interval;
	return (anim);
}

void	update_animation(t_animation *anim)
{
	clock_t	current_time;

	current_time = clock();
	if ((current_time - anim->last_update) >= anim->update_interval)
	{
		anim->current_frame = (anim->current_frame + 1) % anim->frame_count;
		anim->last_update = current_time;
	}
}

static void	update_enemy_position(t_game *game, t_animated_entity *entity,
		int last_enemy_move)
{
	clock_t	current_time;
	t_point	distance;
	t_point	new_pos;

	current_time = clock();
	if ((current_time - last_enemy_move) >= ENEMY_MOVE_DELAY)
	{
		distance.x = game->player.pos.x - entity->pos.x;
		distance.y = game->player.pos.y - entity->pos.y;
		new_pos.x = entity->pos.x;
		new_pos.y = entity->pos.y;
		if (abs(distance.x) > abs(distance.y))
			new_pos.x += if_else((distance.x > 0), 1, -1);
		else
			new_pos.y += if_else((distance.y > 0), 1, -1);
		if (can_move_to(game, new_pos.x, new_pos.y))
		{
			entity->pos.x = new_pos.x;
			entity->pos.y = new_pos.y;
		}
		if (entity->pos.x == game->player.pos.x
			&& entity->pos.y == game->player.pos.y)
			game_over("Game Over! You were caught by an enemy!");
	}
}

void	update_entities(t_game *game)
{
	t_animated_entity	*entity;
	static clock_t		last_enemy_move = 0;
	clock_t				current_time;
	int					i;

	current_time = clock();
	i = 0;
	while (i < game->entity_manager->entities.size)
	{
		entity = game->entity_manager->entities.data[i];
		update_animation(&entity->anim);
		if (entity->type == ENTITY_ENEMY1 || entity->type == ENTITY_ENEMY2)
			update_enemy_position(game, entity, last_enemy_move);
		i++;
	}
	if ((current_time - last_enemy_move) >= ENEMY_MOVE_DELAY)
		last_enemy_move = current_time;
}
