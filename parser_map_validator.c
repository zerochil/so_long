/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:52 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 09:01:12 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	is_rectangular(char **map, int width)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		if (ft_strlen(map[i]) != width)
			error("Error\nParser: Map isn't rectangular");
		i++;
	}
}

static int	is_walled(t_point pos, t_dimensions dim, int value)
{
	if (pos.y == 0 || pos.y == dim.height - 1 || pos.x == 0
		|| pos.x == dim.width - 1)
		if (value != '1')
			return (0);
	return (1);
}

static int	is_allowed_char(t_point pos, t_dimensions dim, int value)
{
	if (ft_strchr("01CEP", (char)value) == NULL)
		return (0);
	return (1);
}

void	validate_map(t_game *game, void **map)
{
	int		count;
	t_point	exit_pos;

	is_rectangular((char **)map, game->dimensions.width);
	if (is_true_in_matrix(map, game->dimensions, is_allowed_char, 1) == 0)
		error("Error\nParser: Forbidden character");
	if (count_in_matrix(map, game->dimensions, EXIT, sizeof(char)) != 1)
		error("Error\nParser: There got to be exactly one exit");
	if (count_in_matrix(map, game->dimensions, PLAYER, sizeof(char)) != 1)
		error("Error\nParser: There got to be exactly one starting position");
	if (game->collectibles_count <= 0)
		error("Error\nParser: There got to be at least one collectible");
	if (is_true_in_matrix(map, game->dimensions, is_walled, sizeof(char)) == 0)
		error("Error\nParser: The map isn't walled");
	if (are_reachable(game) == 0)
		error("Error\nParser: Targets aren't reachable");
}
