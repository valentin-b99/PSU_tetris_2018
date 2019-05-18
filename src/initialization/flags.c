/*
** EPITECH PROJECT, 2019
** flags.c
** File description:
** flags
*/

#include "../../include/tetris.h"
#include "../../include/flags.h"

int verif_arg(int c)
{
    int row = 0;
    int col = 0;
    int com = 0;

    if (c == 'L' && !my_str_isnum(optarg))
        return (my_printf("Error: Argument %s not valid\n", optarg));
    if (c == 'm') {
        for (int i = 0; optarg[i]; i++) {
            (!row && my_charisnum(optarg[i])) ? (row += 1) : (0);
            (row && optarg[i] == ',') ? (com += 1) : (0);
            (row && com && !col && my_charisnum(optarg[i])) ? (col += 1) : (0);
        }
        if (!row || com != 1 || !col)
            return (my_printf("Error: Argument %s not valid\n", optarg));
    }
    if ((c == 'l' || c == 'r' || c == 't' || c == 'd' || c == 'q' || c == 'p')
        && optarg[0] == 0)
        return (my_printf("Error: Argument not valid\n"));
    return (0);
}

void sc_keys(int c, flags_t *flags)
{
    (c == 'l') ? (flags->keyleft = optarg) : (0);
    (c == 'r') ? (flags->keyright = optarg) : (0);
    (c == 't') ? (flags->keyturn = optarg) : (0);
    (c == 'd') ? (flags->keydrop = optarg) : (0);
    (c == 'q') ? (flags->keyquit = optarg) : (0);
    (c == 'p') ? (flags->keypause = optarg) : (0);
}

int switch_case(int c, flags_t *flags, char *exe)
{
    if (verif_arg(c))
        return (1);
    (c == 'L') ? (flags->level = my_getnbr(optarg)) : (0);
    sc_keys(c, flags);
    if (c == 'm') {
        flags->map_size.row = my_getnbr(optarg);
        flags->map_size.col = my_getnbr(optarg +
        my_strlen(my_int_to_str(my_getnbr(optarg))) + 1);
    }
    (c == 'w') ? (flags->without_next = 1) : (0);
    (c == 'D') ? (flags->debug = 1) : (0);
    if (c == 'h') {
        my_printf(HELP_MSG, exe);
        return (-1);
    }
    for (int i = 0; i < 12; i++)
        if (long_options[i].val == c)
            return (0);
    return (1);
}

int non_args(int ac, char **av, game_t *game)
{
    my_printf("Error: The following arguments aren't options: ");
    while (optind < ac)
        my_printf("%s ", av[optind++]);
    my_putchar('\n');
    free(game->flags);
    free(game);
    return (84);
}

int get_flags_tetris(int ac, char **av, game_t *game)
{
    int option_index = -1;
    int c = 0;
    int sc = 0;

    if (test_good_short_flag(ac, av))
        return (84);
    while (c > -1) {
        c = getopt_long(ac, av, "L:l:r:t:d:q:p:wD",
        long_options, &option_index);
        if (c > -1 && (sc = switch_case(c, game->flags, av[0])) == 1)
            return (84);
        else if (sc == -1)
            return (-1);
    }
    if (optind < ac)
        return (non_args(ac, av, game));
    for (int i = 0; i < ac; i++)
        if (test_good_long_flag(av[i]))
            return (84);
    return (0);
}