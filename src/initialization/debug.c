/*
** EPITECH PROJECT, 2019
** debug.c
** File description:
** debug
*/

#include "../../include/tetris.h"

int get_key(void)
{
    int c = 0;
    struct timeval tv;

    fd_set fs;
    tv.tv_usec = tv.tv_sec = 0;
    FD_ZERO(&fs);
    FD_SET(STDIN_FILENO, &fs);
    select(STDIN_FILENO + 1, &fs, 0, 0, &tv);
    if (FD_ISSET(STDIN_FILENO, &fs))
        c = getchar();
    return c;
}

void wait_key_pressed(void)
{
    int c;
    struct termios old;
    struct termios new;

    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    while (!(c = get_key()));
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

char *rtn_key(char *str)
{
    char *nstr = "";
    char my_char[2];

    for (int i = 0; str[i]; i++) {
        if (str[i] == 27)
            nstr = my_strcat_two(nstr, "^E");
        else if (str[i] == ' ')
            nstr = my_strcat_two(nstr, "(space)");
        else {
            my_char[0] = str[i];
            my_char[1] = 0;
            nstr = my_strcat_two(nstr, my_char);
        }
    }
    return (nstr);
}

void print_debug(t_list *list, game_t *game)
{
    my_printf("*** DEBUG MODE ***\n");
    my_printf(DEBUG_KEYS_FORMAT,
    rtn_key(game->flags->keyleft), rtn_key(game->flags->keyright),
    rtn_key(game->flags->keyturn), rtn_key(game->flags->keydrop),
    rtn_key(game->flags->keyquit), rtn_key(game->flags->keypause));
    if (game->flags->without_next == 0)
        my_printf("Next : Yes\n");
    else
        my_printf("Next : No\n");
    my_printf("Level : %d\nSize : %d*%d\n", game->flags->level,
    game->flags->map_size.row, game->flags->map_size.col);
    if (list->lenght > 1)
        sort_alpha(list);
    print_list(list);
    my_printf("Press any key to start Tetris\n");
    wait_key_pressed();
}