#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_of_lines.h"


void print_arena(char **arena, int arenasizex, int arenasizey) {
    for (int i = 0; i < arenasizey; i++) {
        for (int j = 0; j < arenasizex; j++) {
            printf("%c ", arena[i][j]);
        }
        printf("\n");
    }
}

void update_arena(char **arena, int xMove, int arenasizex, int arenasizey, int whose_turn, int *validMove) {
    if (xMove >= 1 && xMove <= arenasizex) {
        int yMove = xMove - 1;
        for (int i = arenasizey - 1; i >= 0; --i) {
            if (arena[i][yMove] == '_') {
                *validMove = 1;
                if (whose_turn == 1) {
                    arena[i][yMove] = 'X';
                    break;
                } else {
                    arena[i][yMove] = 'O';
                    break;
                }
        }
      }
    } else{
        *validMove = 0;
        printf("Invalid move, try again\n");
    }
}

int isWinner(char **arena, int arenasizex, int arenasizey, int size_of_winline) {
    for (int i = 0; i < arenasizey; i++) {
        for (int j = 0; j < arenasizex; j++) {
            if (arena[i][j] != '_') {
                if (j + size_of_winline <= arenasizex) {
                    int k;
                    for (k = 1; k < size_of_winline; k++) {
                        if (arena[i][j] != arena[i][j + k]){
                            break;
                        }
                    }
                    if (k == size_of_winline){
                        return arena[i][j] == 'X' ? 1 : 2;
                    }
                }

                // Check down
                if (i + size_of_winline <= arenasizey) {
                    int k;
                    for (k = 1; k < size_of_winline; k++) {
                        if (arena[i][j] != arena[i + k][j]){
                            break;
                        }
                    }
                    if (k == size_of_winline){
                        return arena[i][j] == 'X' ? 1 : 2;
                    }
                }

                if (i + size_of_winline <= arenasizey && j + size_of_winline <= arenasizex) {
                    int k;
                    for (k = 1; k < size_of_winline; k++) {
                        if (arena[i][j] != arena[i + k][j + k]){
                            break;
                        }
                    }
                    if (k == size_of_winline){
                        return arena[i][j] == 'X' ? 1 : 2;
                    }
                }

                if (i + size_of_winline <= arenasizey && j - size_of_winline >= -1) {
                    int k;
                    for (k = 1; k < size_of_winline; k++) {
                        if (arena[i][j] != arena[i + k][j - k]) {
                            break;
                        }
                    }
                    if (k == size_of_winline) {
                        return arena[i][j] == 'X' ? 1 : 2;
                    }
                }
            }
        }
    }
    return -1;
}

int main(void) {
    int arenasizex, arenasizey, wincon, valid_settings = 0;
    char playertype;

    while (valid_settings == 0) {
        scan_settings(&arenasizex, &arenasizey, &wincon, &playertype, &valid_settings);
    }

    if (valid_settings == 1) {
        game_of_lines(playertype, arenasizex, arenasizey, wincon);
    }

    return 0;
}

void scan_settings(int *arenasizex, int *arenasizey, int *wincon, char *playertype, int *valid_settings) {
    char validarena;
    *playertype = ' ';
    *arenasizex = 0;
    *arenasizey = 0;
    *wincon = 0;

    printf("Opponent: AI or Real person?(A/P)\n");
    scanf(" %c", playertype);

    if (*playertype == 'A' || *playertype == 'P' || *playertype == 'a' || *playertype == 'p') {
        printf("What size arena do you want to play in?(2x2, 3x3 etc.)\n");
        scanf("%d %c %d", arenasizex, &validarena, arenasizey);

        if ((*arenasizex > 0 && *arenasizey > 0 && *arenasizex == *arenasizey) && validarena == 'x') {
            printf("How long should a winning line be?\n");
            scanf("%d", wincon);

            if (*wincon > 2) {
                *valid_settings = 1;
            } else {
                printf("Invalid input, has to be 3 minimum\n");
            }
        } else {
            printf("Invalid arena size, please input two of the same numbers\n like 2x2, 3x3 etc.\n");
        }
    } else {
        printf("Invalid opponent input\n");
    }
}

void game_of_lines(char playertype, int arenasizex, int arenasizey, int size_of_win_line) {
    char **arena = (char **) malloc(arenasizey * sizeof(char *));
    for (int i = 0; i < arenasizey; ++i) {
        arena[i] = (char *) malloc(arenasizex * sizeof(char));
    }

    for (int i = 0; i < arenasizey; ++i) {
        for (int j = 0; j < arenasizex; ++j) {
            arena[i][j] = '_';
        }
    }

    print_arena(arena, arenasizex, arenasizey);

    printf("\n");

    int xMove, yMove;
    int whose_turn = 1;
    int the_winner = -1;
    int validMove = 0;
    srand(time(NULL));
    do {
        if (playertype == 'A' || playertype == 'a') {
            while (whose_turn == 1) {
                validMove = 0;
                printf("\nPlayer 1\n>");
                scanf("%d", &xMove);

                update_arena(arena, xMove, arenasizex, arenasizey, whose_turn, &validMove);
                print_arena(arena, arenasizex, arenasizey);
                the_winner = isWinner(arena, arenasizex, arenasizey, size_of_win_line);
                if (the_winner != -1) {
                    break;
                } else {
                    whose_turn = 2;
                }
            }
            while (whose_turn == 2) {
                validMove = 0;
                printf("\n");
                int randomNumber = 1 + rand() % arenasizex;
                xMove = randomNumber;
                update_arena(arena, xMove, arenasizex, arenasizey, whose_turn, &validMove);
                print_arena(arena, arenasizex, arenasizey);
                the_winner = isWinner(arena, arenasizex, arenasizey, size_of_win_line);
                if (the_winner != -1) {
                    break;
                } else {
                    whose_turn = 1;
                }

            }
        }

        if (playertype == 'P' || playertype == 'p') {
            while (whose_turn == 1) {
                validMove = 0;
                do {
                    printf("\nPlayer 1\n>");
                    scanf("%d", &xMove);
                    update_arena(arena, xMove, arenasizex, arenasizey, whose_turn, &validMove);
                } while (!validMove);
                print_arena(arena, arenasizex, arenasizey);
                the_winner = isWinner(arena, arenasizex, arenasizey, size_of_win_line);
                if (the_winner != -1) {
                    break;
                } else {
                    whose_turn = 2;
                }

            }
            while (whose_turn == 2) {
                do {
                    validMove = 0;
                    printf("\nPlayer 2\n>");
                    scanf("%d", &xMove);
                    update_arena(arena, xMove, arenasizex, arenasizey, whose_turn, &validMove);
                } while (!validMove);
                print_arena(arena, arenasizex, arenasizey);
                the_winner = isWinner(arena, arenasizex, arenasizey, size_of_win_line);
                if (the_winner != -1) {
                    break;
                } else {
                    whose_turn = 1;
                }
            }
        }
    }while (the_winner == -1);


        if (the_winner != -1) {
            printf("Player %d is the winner", the_winner);
        } else {
            printf("The game is a draw");
        }

        for (int i = 0; i < arenasizey; ++i) {
            free(arena[i]);
        }
        free(arena);
    }