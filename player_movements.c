/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:52 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 13:40:09 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include "so_long.h"

static void	print_moves(t_game *game, char *s1, int moves)
{
	char	*moves_str;
	char	output[256];
	void	*img;

	moves_str = ft_itoa(moves);
	if (!moves_str)
		error("failed allocation");
	output[0] = '\0';
	ft_strcat(output, s1);
	ft_strcat(output, moves_str);
	ft_putendl_fd(output, 1);
	img = create_empty_image(game->mlx, TILE_SIZE * 2, TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->win, img, TILE_SIZE,
		game->dimensions.height * TILE_SIZE);
	mlx_string_put(game->mlx, game->win, TILE_SIZE, game->dimensions.height
		* TILE_SIZE + TILE_SIZE / 2, 0x00FFFFFF, output);
	mlx_destroy_image(game->mlx, img);
	free(moves_str);
}

static void	handle_collision(t_game *game, int new_x, int new_y)
{
	char	*moves;
	char	*output;

	if (game->map[new_y][new_x] == COLLECTIBLE)
	{
		game->map[new_y][new_x] = EMPTY_SPACE;
		game->collectibles_count--;
		remove_entity_at(game->entity_manager, new_x, new_y, ENTITY_COIN);
	}
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
	game->player.moves++;
	print_moves(game, "Moves: ", game->player.moves);
	if (game->map[new_y][new_x] == EXIT && game->collectibles_count == 0)
	{
		game_over("Congrats! you won the game.");
	}
}

static void	move_player(t_game *game, enum e_directions direction)
{
	int	new_x;
	int	new_y;

	new_x = game->player.pos.x;
	new_y = game->player.pos.y;
	if (game->player.facing == direction)
		game->player.frame = (game->player.frame + 1) % TOTAL_FRAMES;
	else
	{
		game->player.facing = direction;
		game->player.frame = 0;
	}
	if (direction == UP)
		new_y--;
	else if (direction == DOWN)
		new_y++;
	else if (direction == LEFT)
		new_x--;
	else if (direction == RIGHT)
		new_x++;
	if (can_move_to(game, new_x, new_y))
		handle_collision(game, new_x, new_y);
}

int	can_move_to(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->dimensions.width || new_y < 0
		|| new_y >= game->dimensions.height)
		return (0);
	if (game->map[new_y][new_x] == WALL)
		return (0);
	return (1);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, UP);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, DOWN);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, LEFT);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, RIGHT);
	if (keycode == KEY_ESC)
		game_over("");
	return (0);
}
