/*
** EPITECH PROJECT, 2019
** my_charisnum.c
** File description:
** my_charisnum
*/

int my_charisnum(char c)
{
    if (c < 48 || c > 57)
        return (0);
    return (1);
}