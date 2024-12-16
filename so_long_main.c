/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:52 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 13:41:38 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/base/base.h"
#include "so_long.h"

static void	destroy_game(void *ptr)
{
	t_game	*game;

	game = ptr;
	if (game == NULL)
		return ;
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

static int	game_loop(t_game *game)
{
	update_entities(game);
	render_game(game);
	return (0);
}

static int	close_win(void *ptr)
{
	game_over(NULL);
	return (0);
}

static void start_game(t_game *game)
{
	game->entity_manager = create_entity_manager();
	load_sprites(game);
	init_player(game);
	init_enemies(game);
	init_coins(game);
	mlx_hook(game->win, 2, 1, key_hook, game);
	mlx_hook(game->win, 17, 0, close_win, NULL); // TODO: check the red cross work
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	// TODO: The management of your window must remain smooth (changing to another window, minimizing, and so forth
	// TODO:- Hide all or part of the window either by using another windowor by using the screen's borders, then minimize the windows and maximize it back. In all cases, the content of the window must remain consiste 
	// TOOD: moves should be rendered all the same
	if (argc < 2 || !ends_with(argv[1], ".ber"))
		error("Error\nUsage: ./so_long map.ber");
	game = get_game_instance();
	parse(game, argv[1]);
	track_resource(game, destroy_game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		error("Error\nmlx_init failed");
	game->win = mlx_new_window(game->mlx, game->dimensions.width * TILE_SIZE,
			game->dimensions.height * TILE_SIZE + TILE_SIZE, "so_long");
	if (game->win == NULL)
		error("Error\nmlx_new_window failed");
	start_game(game);
	free_all_resources();
	return (0);
}
