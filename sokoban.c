/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** sokoban
*/

#include <ncurses.h>
#include <stdlib.h>

struct Object
{
    int xPosition;
    int yPosition;
    unsigned char zn;
    chtype ozn;
};

#define N 10
struct Object obj[N] = {};

int wbox = 0;
int lev = 0;

int line_len(char *str)
{
    int i = 0;

    while (str[i] != '\n') {
        i++;
    }
    return (i + 1);
}

int col_count(char *str)
{
    int count = 0;

    for (int i = 0; 1; i++) {
        if (str[i] == '\0') {
            count++;
            break;
        }
        if (str[i] == '\n')
            count++;
    }
    return (count);
}

int contain_several(char c, char *str)
{
    int num = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            num++;
    }
    return (num);
}

int **malloc_2d_int(int col_num, int line_num)
{
    int **tab = (int **)malloc(sizeof(int *) * col_num);

    for (int i = 0; i < col_num; i++) {
        tab[i] = (int *)malloc(sizeof(int) * line_num);
    }
    return (tab);
}

void free_2d_int(int col_num, int **tab)
{
    for (int i = 0; i < col_num; i++) {
        free(tab[i]);
    }
    free(tab);
}
#define MAXCHAR 1000

char *file_to_string(char const *filepath) {
    char *buffer = 0;
    long length;
    FILE *f = fopen(filepath, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, f);
        }
    fclose(f);
    }

    if (buffer) {
        return (buffer);
    }
    return ("84");
}

int **convert_to_tab(char *str)
{
    int line = line_len(str) - 1;
    int col = col_count(str);
    int **tab = malloc_2d_int(col, line - 1);
    int u = 0;
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (j < line) {
            if (str[i] == ' ') tab[u][j] = 0;
            else if (str[i] == '#') tab[u][j] = 1;
            else if (str[i] == 'X') tab[u][j] = 4;
            else if (str[i] == 'P') tab[u][j] = 5;
            else if (str[i] == 'O') tab[u][j] = 2;
            else if (str[i] == '\n') u++;
            j++;
        } else {
            u++;
            j = 0;
        }
    }
    return (tab);
}

void levList(int *h, int *w, int *array, int y, int x, int n, char const *filepath)
{
    if (n == 0) {
        if (file_to_string(filepath)[0] == '8') {
            exit(1);
        }
        *h = col_count(file_to_string(filepath));
        *w = line_len(file_to_string(filepath)) - 1;
        int **mapX = convert_to_tab(file_to_string(filepath));
        *array = mapX[y][x];
    }
}

#define WALL_PAIR   1
#define SLOT_PAIR   2
#define PLAY_PAIR   3
#define EMPT_PAIR   4
#define BOXX_PAIR   5

void palette()
{
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
}

void Level(int n, char const *filepath)
{
    clear();
    mvprintw(1, 12, "MY_SOKOBAN MAP_%d", lev);
    mvprintw(2, 1, "Move-UP-DOWN-LEFT-RIGHT. Reset-R. Exit-E.");
    int x = 0, y = 0, h = 1, w = 1, map;

    wbox = 0;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            levList(&h, &w, &map, y, x, n, filepath);
            switch (map) {
                case 0: mvaddch(y + 4, x + 15, ' ' | COLOR_PAIR(EMPT_PAIR)); break;
                case 1: mvaddch(y + 4, x + 15, '#' | COLOR_PAIR(WALL_PAIR)); break;
                case 2: mvaddch(y + 4, x + 15, 'O' | COLOR_PAIR(SLOT_PAIR)); break;
                case 4:
                    mvaddch(y + 4, x + 15, ' ' | COLOR_PAIR(EMPT_PAIR));
                    wbox += 1;
                    obj[wbox].ozn = mvinch(y + 4, x + 15);
                    obj[wbox].yPosition = y + 4;
                    obj[wbox].xPosition = x + 15;
                    obj[wbox].zn = 'X';
                    mvaddch(obj[wbox].yPosition, obj[wbox].xPosition, obj[wbox].zn | COLOR_PAIR(BOXX_PAIR));
                    break;
                case 5:
                    mvaddch(y + 4, x + 15, ' ' | COLOR_PAIR(EMPT_PAIR));
                    obj[0].ozn = mvinch(y + 4, x + 15);
                    obj[0].yPosition = y + 4;
                    obj[0].xPosition = x + 15;
                    obj[0].zn = 'P';
                    mvaddch(obj[0].yPosition, obj[0].xPosition, obj[0].zn | COLOR_PAIR(PLAY_PAIR));
                    break;
            }
        }
    }
    move(obj[0].yPosition, obj[0].xPosition);
}

void Play(int input, char const *filepath)
{
    noecho();
    bool restart = FALSE;
    chtype up, lf, dw, rg, oup, olf, odw, org;

    up = (mvinch(obj[0].yPosition - 1, obj[0].xPosition) & A_CHARTEXT);
    lf = (mvinch(obj[0].yPosition, obj[0].xPosition - 1) & A_CHARTEXT);
    dw = (mvinch(obj[0].yPosition + 1, obj[0].xPosition) & A_CHARTEXT);
    rg = (mvinch(obj[0].yPosition, obj[0].xPosition + 1) & A_CHARTEXT);
    oup = (mvinch(obj[0].yPosition - 2, obj[0].xPosition) & A_CHARTEXT);
    olf = (mvinch(obj[0].yPosition, obj[0].xPosition - 2) & A_CHARTEXT);
    odw = (mvinch(obj[0].yPosition + 2, obj[0].xPosition) & A_CHARTEXT);
    org = (mvinch(obj[0].yPosition, obj[0].xPosition + 2) & A_CHARTEXT);

    for (int o = 0; o <= wbox; o++) {
        mvaddch(obj[o].yPosition, obj[o].xPosition, obj[o].ozn);
    }

    switch (input) {
        case 'z':
        case 65:
            if (up != 35) {
                if (up == 88 && (oup == 32 || oup == 79)) {
                    obj[0].yPosition -= 1;
                    for (int o = 1; o <= wbox; o++) {
                        if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition)) {
                            obj[o].yPosition -= 1;
                        }
                    }
                } else if (up != 88) obj[0].yPosition -= 1;
            }
            break;
        case 's':
        case 66:
            if (dw != 35) {
                if (dw == 88 && (odw == 32 || odw == 79)) {
                    obj[0].yPosition += 1;
                    for (int o = 1; o <= wbox; o++) {
                        if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition)) {
                            obj[o].yPosition += 1;
                        }
                    }
                } else if (dw != 88) obj[0].yPosition += 1;
            }
            break;
        case 'q':
        case 68:
            if (lf != 35) {
                if (lf == 88 && (olf == 32 || olf == 79)) {
                    obj[0].xPosition -= 1;
                    for (int o = 1; o <= wbox; o++) {
                        if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition)) {
                            obj[o].xPosition -= 1;
                        }
                    }
                } else if (lf != 88) obj[0].xPosition -= 1;
            }
            break;
        case 'd':
        case 67:
            if (rg != 35) {
                if (rg == 88 && (org == 32 || org == 79)) {
                    obj[0].xPosition += 1;
                    for (int o = 1; o <= wbox; o++) {
                        if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition)) {
                            obj[o].xPosition += 1;
                        }
                    }
                } else if (rg != 88) obj[0].xPosition += 1;
            }
            break;
        case ' ':
        case 'r':
            restart = TRUE;
            Level(lev, filepath);
            break;
        default:
            break;
    }
    if (!restart) {
        for (int o = 0; o <= wbox; o++) {
            obj[o].ozn = mvinch(obj[o].yPosition, obj[o].xPosition);
            mvaddch(obj[o].yPosition, obj[o].xPosition, obj[o].zn | ((o == 0) ? COLOR_PAIR(3) : COLOR_PAIR(5)));
        }
        move(obj[0].yPosition, obj[0].xPosition);
    } else restart = FALSE;
}

int check_map(char *map)
{
    int line_length = line_len(map) - 1;
    int column_count = col_count(map);

    if (contain_several('X', map) != contain_several('O', map))
        return (0);
    
    if (contain_several('P', map) != 1)
        return (0);
    
    for (int i = 0; i < column_count + 1; i++) {
        if (map[i * (line_length + 1)] != '#' && i < column_count)
            return (0);
    }

    for (int i = 0; i < line_length; i++) {
        if (map[i] != '#')
            return (0);
    }

    for (int i = (column_count - 1) * (line_length + 2) + 1; map[i] != '\0'; i++) {
        if (map[i] != '#')
            return (0);
    }

    return (1);
}

int main(int argc, char **argv)
{
    int ch;
    char *filepath = argv[1];

    if (argc < 2) {
        printf("Please provide a map.\n");
        return (84);
    } else if (argc > 2) {
        printf("Too many arguments.\n");
        return (84);
    }
    if (check_map(file_to_string(filepath)) == 0) {
        printf("Invalid map.\n");
        return (84);
    }

    initscr();
    noecho();

    if (!has_colors()) {
        endwin();
        printf("The terminal do not support colors\n");
        exit(1);
    }
    start_color();
    palette();
    Level(lev, filepath);

    while ((ch = getch()) != 'e') {
        Play(ch, filepath);
    }
    endwin();
    return (0);
}