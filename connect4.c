#include <stdio.h>
#include <stdbool.h>

/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
enum
{
    EMPTY = 0,
    RED,
    BLUE,
};

typedef char board_t[4][5];
typedef char player_t;

void init_board(board_t *board)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            (*board)[row][col] = 0;
        }
    }
}

int has_won(board_t board, player_t player)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 2; ++col)
        {
            if (board[row][col] == player && board[row][col + 1] == player &&
                board[row][col + 2] == player && board[row][col + 3] == player)
            {
                return true;
            }
        }
    }

    for (int row = 0; row < 2; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            if (board[row][col] == player && board[row + 1][col] == player &&
                board[row + 2][col] == player && board[row + 3][col] == player)
            {
                return true;
            }
        }
    }

    for (int row = 0; row < 2; ++row)
    {
        for (int col = 0; col < 2; ++col)
        {
            if (board[row][col] == player && board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player && board[row + 3][col + 3] == player)
            {
                return true;
            }
        }
    }

    for (int row = 0; row < 2; ++row)
    {
        for (int col = 3; col < 5; ++col)
        {
            if (board[row][col] == player && board[row + 1][col - 1] == player &&
                board[row + 2][col - 2] == player && board[row + 3][col - 3] == player)
            {
                return true;
            }
        }
    }

    return false;
}

int is_full(board_t board)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (board[i][j] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

typedef struct
{
    int col;
    int score;
} move_t;

move_t best_move(board_t board, player_t player)
{
}

void print_board(board_t board)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            printf("%2d ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    board_t trial;
    init_board(&trial);
    return 0;
}
