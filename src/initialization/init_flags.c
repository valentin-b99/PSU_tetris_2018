/*
** EPITECH PROJECT, 2019
** init_flags.c
** File description:
** init_flags
*/

#include "../../include/tetris.h"

void set_keys(game_t *game)
{
    game->flags->keyleft = tigetstr("kcub1");
    game->flags->keyright = tigetstr("kcuf1");
    game->flags->keyturn = tigetstr("kcuu1");
    game->flags->keydrop = tigetstr("kcud1");
    game->flags->keyquit = my_strdup("q");
    game->flags->keypause = my_strdup("(space)");
}

int init_flags_struct(game_t *game, char **env)
{
    int i = 0;

    if (!env[0])
        return (my_printf("Error: invalid environement.\n"));
    while (env[++i] && my_strncmp(env[i], "TERM=", 4));
    if (!env[i])
        return (my_printf("Error: invalid parameter.\n"));
    setupterm(&env[i][5], 1, NULL);
    if ((game->flags = malloc(sizeof(flags_t))) == NULL)
        return (84);
    game->flags->level = 1;
    set_keys(game);
    game->flags->map_size.row = 20;
    game->flags->map_size.col = 10;
    game->flags->without_next = 0;
    game->flags->debug = 0;
    return (0);
}