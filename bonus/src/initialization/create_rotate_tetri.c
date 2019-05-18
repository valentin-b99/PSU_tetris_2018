/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** create_rotate_tetri
*/

#include "../../include/tetris.h"

void create_rotate_tetri_next(int *co, int height, char **r_tetri, char **tetri)
{
    if (tetri[co[1]][co[0]] == '*')
        r_tetri[co[0]][height - 1 - co[1]] = tetri[co[1]][co[0]];
    else
        r_tetri[co[0]][height - 1 - co[1]] = ' ';
}

char **create_rotate_tetri(char **tetri, int width, int height)
{
    char **r_tetri = malloc(sizeof(char *) * (width + 1));
    int co[2];

    for (int i = 0; i < width; i++) {
        r_tetri[i] = malloc(sizeof(char) * (height + 1));
        fill_str(r_tetri[i], height + 1);
    }
    r_tetri[width] = NULL;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            co[0] = x;
            co[1] = y;
            create_rotate_tetri_next(co, height, r_tetri, tetri);
        }
    }
    return (r_tetri);
}