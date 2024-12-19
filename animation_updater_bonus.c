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

t_animation	init_animation(t_image *frames, int frame_count,
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

void	update_entities(t_game *game)
{
	t_animated_entity	*entity;
	clock_t				current_time;
	int					i;

	current_time = clock();
	i = 0;
	while (i < game->entity_manager->entities.size)
	{
		entity = game->entity_manager->entities.data[i];
		update_animation(&entity->anim);
		if (entity->type == ENTITY_ENEMY1 || entity->type == ENTITY_ENEMY2)
			move_enemy(game, entity);
		i++;
	}
}
