void scan_settings(int *arenasizex, int *arenasizey, int *wincon, char *playertype, int *valid_settings);
void game_of_lines(char playertype, int arenasizex, int arenasizey, int size_of_winline);
void print_arena(char **arena, int arenasizex, int arenasizey);
void update_arena(char **arena, int xMove, int arenasizex, int arenasizey, int whose_turn, int *validMove);
int isWinner(char **arena, int arenasizex, int arenasizey, int size_of_winline);

// Define function prototypes, (and new datatypes if you need it).
