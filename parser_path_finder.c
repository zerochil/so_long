/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:53 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/19 10:51:43 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	valid_move(t_point pos)
{
	t_game	*game;

	game = get_game_instance();
	if (pos.x < 0 || pos.x >= game->dimensions.width || pos.y < 0
		|| pos.y >= game->dimensions.height)
		return (0);
	if (ft_strchr(game->obstacles, game->map[pos.y][pos.x]))
		return (0);
	return (1);
}

static int	same_pos(void *ptr1, void *ptr2)
{
	t_point	pos1;
	t_point	pos2;

	pos1 = *(t_point *)ptr1;
	pos2 = *(t_point *)ptr2;
	return (pos1.x == pos2.x && pos1.y == pos2.y);
}

int	is_reachable(t_game *game, t_point start, t_point target)
{
	t_array	visited;
	t_array	stack;
	t_point	pos;

	array_init(&visited);
	array_init(&stack);
	array_push(&stack, new_point(start.x, start.y));
	while (stack.size > 0)
	{
		pos = *(t_point *)array_pop(&stack);
		if (!valid_move(pos))
			continue ;
		if (array_find(&visited, &pos, same_pos))
			continue ;
		array_push(&visited, new_point(pos.x, pos.y));
		if (pos.x == target.x && pos.y == target.y)
			return (free_array(&stack), free_array(&visited), 1);
		array_push(&stack, new_point(pos.x + 1, pos.y));
		array_push(&stack, new_point(pos.x - 1, pos.y));
		array_push(&stack, new_point(pos.x, pos.y + 1));
		array_push(&stack, new_point(pos.x, pos.y - 1));
	}
	return (free_array(&stack), free_array(&visited), 0);
}

int	are_reachable(t_game *game)
{
	int	x;
	int	y;

	game->obstacles = "1";
	x = 0;
	while (x < game->dimensions.width)
	{
		y = 0;
		while (y < game->dimensions.height)
		{
			if (game->map[y][x] == COLLECTIBLE || game->map[y][x] == EXIT)
				if (is_reachable(game, game->player.pos, (t_point){x, y}) == 0)
					return (0);
			y++;
		}
		x++;
	}
	return (1);
}
