#include "so_long.h"

void init_player(t_game *game) {
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            if (game->map[y][x] == PLAYER) {
                game->player.pos.x = x;
                game->player.pos.y = y;
                game->player.frame = 0;
                game->player.facing = DOWN;
                game->player.moves = 0;
                game->map[y][x] = EMPTY_SPACE;
                return;
            }
        }
    }
}

void init_enemies(t_game *game) {
    t_animation enemy1_anim, enemy2_anim;
    t_point pos;
    t_animated_entity *enemy;
    int enemy_count = 0;
    int max_attempts = 100;

    enemy1_anim = create_animation(game->sprites.enemy1, TOTAL_FRAMES, FRAME_DELAY);
    enemy2_anim = create_animation(game->sprites.enemy2, TOTAL_FRAMES, FRAME_DELAY);

    while (enemy_count < 2 && max_attempts > 0) {
        pos.x = rand() % game->map_width;
        pos.y = rand() % game->map_height;

        if (game->map[pos.y][pos.x] == EMPTY_SPACE && 
            (abs(pos.x - game->player.pos.x) > 2 || 
             abs(pos.y - game->player.pos.y) > 2)) {
            
            enemy = create_entity(pos, 
                                enemy_count == 0 ? enemy1_anim : enemy2_anim,
                                enemy_count == 0 ? ENTITY_ENEMY1 : ENTITY_ENEMY2);
            add_entity(game->entity_manager, enemy);
            enemy_count++;
        }
        max_attempts--;
    }
}

void init_coins(t_game *game) {
    t_animation coin_anim;
    t_animated_entity *coin;
    t_point pos;

    coin_anim = create_animation(game->sprites.coin, 4, FRAME_DELAY);

    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            if (game->map[y][x] == COLLECTIBLE) {
                pos.x = x;
                pos.y = y;
                coin = create_entity(pos, coin_anim, ENTITY_COIN);
                add_entity(game->entity_manager, coin);
            }
        }
    }
}


