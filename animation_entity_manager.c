/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:52 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 08:43:27 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/containers/containers.h"
#include "so_long.h"

t_entity_manager	*create_entity_manager(void)
{
	t_entity_manager	*manager;

	manager = track_malloc(sizeof(t_entity_manager));
	array_init(&manager->entities);
	return (manager);
}

t_animated_entity	*create_entity(t_point pos, t_animation anim,
		enum e_entity_type type)
{
	t_animated_entity	*entity;

	entity = track_malloc(sizeof(t_animated_entity));
	entity->pos = pos;
	entity->anim = anim;
	entity->type = type;
	entity->facing = DOWN;
	entity->moves = 0;
	return (entity);
}

void	add_entity(t_entity_manager *manager, t_animated_entity *entity)
{
	array_push(&manager->entities, entity);
}

t_animated_entity	*find_entity_at(t_entity_manager *manager, int x, int y)
{
	t_animated_entity	*entity;
	int					i;

	i = 0;
	while (i < manager->entities.size)
	{
		entity = manager->entities.data[i];
		if (entity->pos.x == x && entity->pos.y == y)
			return (entity);
		i++;
	}
	return (NULL);
}

void	remove_entity_at(t_entity_manager *manager, int x, int y,
		enum e_entity_type type)
{
	t_animated_entity	*entity;
	int					i;

	i = 0;
	while (i < manager->entities.size)
	{
		entity = manager->entities.data[i];
		if (entity->pos.x == x && entity->pos.y == y && entity->type == type)
		{
			array_remove(&manager->entities, i);
			break ;
		}
		i++;
	}
}
