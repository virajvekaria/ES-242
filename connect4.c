#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

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
            (*board)[row][col] = '0';
        }
    }
}

player_t other_player(player_t player){
    switch (player)
    {
    case 'R': return 'B';
    case 'B': return 'R';
    default:
        assert(0);
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
            if (board[i][j] == '0')
            {
                return 0;
            }
        }
    }
    return 1;
}

int score(board_t board, player_t player){
    assert(has_won(board, player));
    int score = 10;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (board[i][j] == player)
            {
                score -= 1;
            }
        }
    }
    return score;
}

typedef struct
{
    int col;
    int score;
} move_t;

move_t best_move(board_t board, player_t player)
{
    move_t response;
    move_t candidate;
    int no_candidate = 0;

    assert(!is_full(board));
    assert(!has_won(board, 1));
    assert(!has_won(board, 2));

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            if(board[row][col] == '0'){
                board[row][col] = player;
                if(has_won(board, player)){
                    candidate = (move_t) {.col = col,
                    .score = score(board, player)};
                    return candidate;
                }
            board[row][col] = '0';
            }
        }
        
    }

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < col; col++)
        {
            if(board[row][col] == '0'){
                board[row][col] = player;
                if(is_full(board)){
                    candidate = (move_t){
                        .col = col,
                        .score = 0
                    };
                return candidate;
                }
            
            response = best_move(board, other_player(player));
            board[row][col] = '0';
            if(response.score < 0){
                candidate = (move_t){
                    .col = col,
                    .score = 10 + response.score
                };
                return candidate;
            }
            else if (response.score = 0){
                candidate = (move_t){
                    .col = col,
                    .score = 0
                };
                return candidate;
            }
            else{
                if(no_candidate){
                candidate = (move_t){
                    .col = col,
                    .score = -(response.score)
                };
                no_candidate = 0;
                }
            }
            }
        }
        
    }
    return candidate;
    
}

int drop_piece(board_t board, int col, player_t player)
{
    assert(board[3][col] == '0' || board[2][col] == '0' || board[1][col] == '0' || board[0][col] == '0');
    for (int row = 3; row >= 0; --row)
    {
        if (board[row][col] == '0')
        {
            board[row][col] = player;
            return row;
        }
    }
    return -1; // Invalid move
}

void print_board(board_t board)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    int move;
    board_t board;
    init_board(&board);

    move_t response;
    player_t current = 'R';

    while (true)
    {
        print_board(board);
        if (current == 'R')
        {
            printf("Enter your move: ");
            scanf("%d", &move);
            drop_piece(board, move, current);
        }
        else
        {
            response = best_move(board, current);
            drop_piece(board, response.col, current);
        }
        if (has_won(board, current))
        {
            print_board(board);
            printf("Player %c has won!\n", current);
            break;
        }
        else if (is_full(board))
        {
            print_board(board);
            printf("Draw.\n");
            break;
        }
        current = other_player(current);
    }

    return 0;
}