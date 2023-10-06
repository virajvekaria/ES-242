#include <stdio.h>
#include <assert.h>
#include <limits.h>

/*
 * The status of a line.
 */
enum {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

#define MAX_LINES (15)

/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

/* Global array to store the points associated with each line */
int points[15] = {12, 13, 14, 15, 16, 23, 24, 25, 26, 34, 35, 36, 45, 46, 56};

int is_line_occupied(board_t board, int line)
{
    return board[line] != NO;
}

int has_won(board_t board, player_t player) {
    // Define an array to store the points occupied by the player
    int playerPoints[6] = {0}; // Initialize to 0

    // Determine the points occupied by the player
    for (int line = 0; line < 15; ++line) {
        if (board[line] == player) {
            // Map lines to points (12 to 56)
            int point = (line + 12) / 2;
            playerPoints[point - 1] = 1; // Mark the point as occupied by the player
        }
    }

    // Define all possible combinations of triangles (3 points each)
    int triangles[20][3] = {
        {1, 2, 3}, {1, 2, 4}, {1, 2, 5}, {1, 2, 6},
        {1, 3, 4}, {1, 3, 5}, {1, 3, 6}, {1, 4, 5},
        {1, 4, 6}, {1, 5, 6}, {2, 3, 4}, {2, 3, 5},
        {2, 3, 6}, {2, 4, 5}, {2, 4, 6}, {2, 5, 6},
        {3, 4, 5}, {3, 4, 6}, {3, 5, 6}, {4, 5, 6}
    };

    // Check if any of the triangles is formed by the player
    for (int i = 0; i < 20; ++i) {
        int point1 = triangles[i][0];
        int point2 = triangles[i][1];
        int point3 = triangles[i][2];

        // Check if all three points are occupied by the player
        if (playerPoints[point1 - 1] && playerPoints[point2 - 1] && playerPoints[point3 - 1]) {
            return 1; // Player has formed a triangle, game ends, and the other player wins
        }
    }

    // If no triangles are formed, the game continues
    return 0;
}

int is_full(board_t board)
{
    // Checks if board is full
    // Return 1 if the board is full, 0 otherwise.
    for (int i = 0; i < 15; i++)
    {
        if (board[i] == NO)
        {
            return 0;
        }
    }
    return 1;
}

typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

move_t best_move(board_t board, char player, int depth, int alpha, int beta) {
    move_t response;
    move_t candidate = {.line = -1, .score = (player == 'B') ? INT_MIN : INT_MAX};

    if (has_won(board, 'R')) {
        candidate.score = -10;
        return candidate;
    }
    if (has_won(board, 'B')) {
        candidate.score = 10;
        return candidate;
    }

    if (is_full(board) || depth == 0) {
        candidate.score = 0;
        return candidate;
    }

    for (int line = 0; line < MAX_LINES; ++line) {
        if (board[line] == NO) {
            // Simulate drawing the line
            board[line] = player;

            if (has_won(board, other_player(player))) {
                // If forming a triangle, give it a high score
                response.score = (player == 'B') ? 1000 : -1000;
            } else {
                // If not forming a triangle, evaluate the position
                response = best_move(board, (player == 'B') ? 'R' : 'B', depth - 1, alpha, beta);
            }

            // Undo the move
            board[line] = NO;

            if (player == 'B') {
                if (response.score > candidate.score) {
                    candidate.line = line;
                    candidate.score = response.score;
                }
                alpha = (alpha > response.score) ? alpha : response.score;
            } else { // player == 'R'
                if (response.score < candidate.score) {
                    candidate.line = line;
                    candidate.score = response.score;
                }
                beta = (beta < response.score) ? beta : response.score;
            }

            if (beta <= alpha) {
                break; // Alpha-beta pruning
            }
        }
    }

    return candidate;
}


void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
        case RED: printf("R  "); break;
        case BLUE: printf("B  "); break;
        case NO: printf(". "); break;
        }
    }
    printf("\n");
}

void make_move(board_t board, int line, player_t player){
    assert(line >= 0 && line < 15);
    board[line] = player;
}

int main()
{
    player_t user_choice;
    printf("Select your player (R for RED, B for BLUE): ");
    scanf(" %c", &user_choice);

    player_t current_player = user_choice;
    board_t game_board;

    for (int i = 0; i < 15; i++)
    {
        game_board[i] = NO;
    }

    while (!has_won(game_board, current_player) && !is_full(game_board)){
        printf("Current board:\n");
        print_board(game_board);

        move_t move = best_move(game_board, current_player, 0, INT_MIN, INT_MAX);

        // Check if the chosen line is valid and not occupied
        if (move.line >= 0 && move.line < 15 && !is_line_occupied(game_board, move.line)) {
            make_move(game_board, move.line, current_player);
        } else {
            printf("Invalid move. Try again.\n");
            continue;
        }

        current_player = (current_player == RED) ? BLUE : RED;
    }
    return 0;
}
