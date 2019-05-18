/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** main
*/

#include "../include/tetris.h"

void end_destroys(game_t *game)
{
    destroy_ll(game->list);
    free(game->flags);
    free(game);
}

int main(int ac, char **av, char **env)
{
    game_t *game = malloc(sizeof(game_t));
    int gf = 0;
    int r = 0;

    game->list = initialisation_empty();
    if (!game || init_flags_struct(game, env) ||
        (gf = get_flags_tetris(ac, av, game)) == 84)
        return (84);
    else if (gf == -1)
        return (0);
    if (read_directory(game->list) == 84 ||
        open_tetriminos(game, game->list) == 84)
        return (84);
    if (game->flags->debug == 1)
        print_debug(game->list, game);
    end_destroys(game);
    return (r);
}