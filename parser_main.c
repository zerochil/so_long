/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:53 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 10:27:43 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	read_map(t_game *game, char *map_filename)
{
	int		fd;
	char	*line;
	t_array	lines;
	char	**map;
	int		length;

	fd = track_open(map_filename, O_RDONLY, 0, "Error\nCan't open map");
	array_init(&lines);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL || *line == '\0')
			break ;
		length = ft_strlen(line);
		if (line[length - 1] == '\n')
			line[length - 1] = '\0';
		array_push(&lines, line);
	}
	if (lines.size == 0)
		error("Error\nEmpty map");
	game->map = array_dup(&lines);
	game->dimensions.width = ft_strlen(game->map[0]);
	game->dimensions.height = lines.size;
	array_destroy(&lines);
	free_resource(int_to_void(fd));
}

void	parse(t_game *game, char *map_filename)
{
	int		width;
	int		height;
	void	**map;

	read_map(game, map_filename);
	map = (void **)game->map;
	game->collectibles_count = count_in_matrix(map, game->dimensions,
			COLLECTIBLE, 1);
	game->player.pos = find_in_matrix(map, game->dimensions, PLAYER, 1);
	game->exit_pos = find_in_matrix(map, game->dimensions, EXIT, 1);
	validate_map(game, map);
}
