/*
** EPITECH PROJECT, 2019
** epitech
** File description:
** tetris
*/

#ifndef TETRIS_H
#define TETRIS_H

#include "../lib/my/mylib.h"
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <stdio.h>
#include <termios.h>
#include <time.h>
#include <term.h>

typedef struct t_element t_element;
struct t_element
{
    char *name;
    char ***tetri;
    int width;
    int height;
    int color_code;
    int is_error;
    t_element *next;
    t_element *prev;
};

typedef struct t_list t_list;
struct t_list
{
    t_element *first;
    t_element *last;
    int lenght;
};

typedef struct msize_t
{
    int row;
    int col;
} msize_t;

typedef struct coords_s
{
    int x;
    int y;
} coords_t;

typedef struct flags_s
{
    int level;
    char *keyleft;
    char *keyright;
    char *keyturn;
    char *keydrop;
    char *keyquit;
    char *keypause;
    msize_t map_size;
    char without_next;
    char debug;
} flags_t;

typedef struct game_s
{
    flags_t *flags;
    t_list *list;
} game_t;

#define HELP_MSG "Usage:\t%s [options]\nOptions:\n\t--help\t\t\
Display this help\n\t-L --level={num}\tStart Tetris at level num (def: \
1)\n\t-l --key-left={K}\tMove the tetrimino LEFT using the K key (def: \
left arrow)\n\t-r --key-right={K}\tMove the tetrimino RIGHT using the K \
key (def: right arrow)\n\t-t --key-turn={K}\tTURN the tetrimino clockwise\
90d using the K key (def: top arrow)\n\t-d --key-drop={K}\tDROP the \
tetrimino using the K key (def: down arrow)\n\t-q --key-quit={K}\t\
QUIT the game using the K key (def: 'q' key)\n\t-p --key-pause={K}\t\
PAUSE/RESTART the game using the K key (def: space bar)\n\t\
--map-size={row,col}\tSet the numbers of the rows and columns of the map \
(def: 20,10)\n\t-w --without-next\tHide next tetrimino (def: false)\n\t\
-D --debug\t\tDebug mode (def: false)\n"

#define DEBUG_KEYS_FORMAT "Key Left : %s\nKey Right : %s\nKey Turn : %s\
\nKey Drop : %s\nKey Quit : %s\nKey Pause : %s\n"

/* main.c */
void end_destroys(game_t *game);
int main(int ac, char **av, char **env);

/* src/initialization/create_rotate_tetri.c */
void create_rotate_tetri_next(int *co, int height, char **r_tetri,
char **tetri);
char **create_rotate_tetri(char **tetri, int width, int height);

/* src/initialization/debug.c */
int get_key(void);
void wait_key_pressed(void);
char *rtn_key(char *str);
void print_debug(t_list *list, game_t *game);

/* src/initialization/flags.c */
int verif_arg(int c);
void sc_keys(int c, flags_t *flags);
int switch_case(int c, flags_t *flags, char *exe);
int non_args(int ac, char **av, game_t *game);
int get_flags_tetris(int ac, char **av, game_t *game);

/* src/initialization/init_flags.c */
void set_keys(game_t *game);
int init_flags_struct(game_t *game, char **env);

/* src/initialization/linked_lists.c */
t_element *insertion_end(t_list *list, char *str);
void print_list(t_list *list);
void destroy_ll(t_list *list);
t_list *initialisation_empty(void);
void delete_middle(t_list *list, t_element *to_delete);

/* src/initialization/my_malloc.c */
void *my_malloc(size_t size);

/* src/initialization/read_directory.c */
int open_tetriminos(game_t *g, t_list *list);
int is_good_extension(struct dirent *r_f);
int read_directory(t_list *list);

/* src/initialization/sort_alpha_functions.c */
void swap_s(t_list *list);
void rotate_rr(t_list *list);
void rotate_r(t_list *list);
void exchange_p(t_list *src, t_list *dest);
void exchange_p_following(t_list *src, t_list *dest);

/* src/initialization/sort_alpha.c */
void sort(t_list *l_a, t_list *l_b);
void end_sort(t_list *l_a, t_list *l_b);
void sort_alpha(t_list *l_a);

/* src/initialization/test_good_flag.c */
int test_good_long_flag(char *str);
int test_good_short_flag(int ac, char **av);

/* src/initialization/verify_tetriminos.c */
void set_tetri(t_element *actual, int fd);
int tetri_is_error(game_t *g, t_list *list, t_element *actual,
char **first_line);
int verify_tetriminos(game_t *g, t_list *list, t_element *actual, int fd);

#endif