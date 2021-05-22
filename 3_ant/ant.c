// Sameh Shahin ew20b001

#include <stdio.h>

typedef struct
{
    int x;
    int y;
    int d;
} langton_ant;

enum directions
{
    north,
    right,
    south,
    left
};

void print_board(int l, char board[l][l]);
void change_color_and_direction(langton_ant *ant, char *board);
void move(langton_ant *ant);
int get_pos_int(int i);

int main()
{
    // define variables
    langton_ant ant = {.d = left}; // default direction left
    int turns;
    int board_size = 10;
    char board[board_size][board_size];

    // read and assign input
    printf("Enter number of turns: ");
    scanf("%d", &turns);
    printf("Enter start position: ");
    scanf("%d %d", &ant.y, &ant.x);

    board[ant.x][ant.y] = 'a'; // place the ant

    for (int moves = 0; moves < turns; moves++)
    {

        change_color_and_direction(&ant, &board[ant.x][ant.y]);
        move(&ant);

        if (ant.x >= 0 && ant.x < 10 && ant.y >= 0 && ant.y < 10)
        {
            board[ant.x][ant.y] = board[ant.x][ant.y] == '#' ? 'A' : 'a';
        }
        else
        {
            break;
        }
    }

    print_board(board_size, board);
}

//****** Procedures ******//

// change direction and square color directly using pointers
void change_color_and_direction(langton_ant *ant, char *board)
{
    if (*board != '#' && *board != 'A')
    {
        *board = '#';
        ant->d++; //turn right (clockwise)
    }
    else
    {
        *board = '.';
        ant->d--; //turn left (anticlockwise)
    }
}

// move to the next square by changing the ant's coordinates
void move(langton_ant *ant)
{
    switch (get_pos_int(ant->d) % 4)
    {
    case north:
        ant->x--;
        break;
    case right:
        ant->y++;
        break;
    case south:
        ant->x++;
        break;
    case left:
        ant->y--;
        break;
    }
}

int get_pos_int(int i)
{
    return i < 0 ? i * -1 : i;
}

void print_board(int l, char board[l][l])
{
    for (int d1 = 0; d1 < l; d1++)
    {
        for (int d2 = 0; d2 < l; d2++)
        {
            if (board[d1][d2] != '#' && board[d1][d2] != 'a' && board[d1][d2] != 'A')
            {
                board[d1][d2] = '.';
            };
            printf("%c", board[d1][d2]);
        };
        printf("\n");
    }
}
//****** end Procedures ******//