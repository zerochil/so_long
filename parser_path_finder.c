/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:53 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 09:02:36 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	can_move(t_game *game, int x, int y, t_array *visited)
{
	t_point	*pos;
	size_t	i;

	if (x < 0 || x >= game->dimensions.width || y < 0
		|| y >= game->dimensions.height)
		return (0);
	if (game->map[y][x] == '1')
		return (0);
	i = 0;
	while (i < visited->size)
	{
		pos = visited->data[i];
		if (pos->x == x && pos->y == y)
			return (0);
		i++;
	}
	return (1);
}

static int	flood(t_game *game, t_point current, t_point target,
		t_array *visited)
{
	static int	dx[4] = {-1, 1, 0, 0};
	static int	dy[4] = {0, 0, -1, 1};
	int			i;
	t_point		*pos;

	if (current.x == target.x && current.y == target.y)
		return (1);
	pos = new_point(current.x, current.y);
	array_push(visited, pos);
	i = 0;
	while (i < 4)
	{
		current.x += dx[i];
		current.y += dy[i];
		if (can_move(game, current.x, current.y, visited))
			if (flood(game, current, target, visited))
				return (1);
		current.x -= dx[i];
		current.y -= dy[i];
		i++;
	}
	return (0);
}

static int	is_reachable(t_game *game, t_point start, t_point target)
{
	t_array	visited;
	int		found;

	array_init(&visited);
	found = flood(game, start, target, &visited);
	array_destroy(&visited);
	// TODO: destroy visited and all the points
	// TODO: E can block C
	return (found);
}

int	are_reachable(t_game *game)
{
	int	x;
	int	y;

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
