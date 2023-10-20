#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

enum {
    NO = 0,
    RED = 1,
    BLUE = 2
};

typedef char board_t[15];
typedef char player_t;

void initializeBoard(board_t board) {
    for (int i = 0; i < 15; i++) {
        board[i] = '.';
    }
}

void playMove(board_t board, int move, player_t player) {
    board[move] = player;
}

bool isValidMove(board_t board, int move) {
    return move >= 0 && move < 15 && board[move] == '.';
}

bool hasLost(board_t board, player_t player) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            for (int k = 0; k < 4 - i - j; k++) {
                int a1 = (i * (11 - i) / 2) + j + 1;
                int a2 = a1 + k + 1;
                int a3 = 6 + k + (i + j) * (9 - i - j) / 2;
                a1 = a1 - 1;
                a2 = a2 - 1;
                a3 = a3 - 1;
                
                if (board[a1] == board[a2] && board[a2] == board[a3] && board[a3] == player) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


bool isFull(board_t board) {
    for (int i = 0; i < 15; i++) {
        if (board[i] == '.') {
            return false;
        }
    }
    return true;
}

typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_score;

move_score best_move(board_t board, player_t player, int alpha, int beta, int depth, int max_min) {
    move_score best;
    best.score = (max_min == 1) ? -INT_MAX : INT_MAX;
    best.line = -1;

    if (hasLost(board, player)) {
        best.score = -1;
        return best;
    } 
    else if (hasLost(board, (player == 'R') ? 'B' : 'R')) {
        best.score = 1;
        return best;
    }


    if (max_min == 1) {
        for (int col = 14; col >= 0; col--) {
            if (isValidMove(board, col)) {
                
                playMove(board, col, player);

                move_score eval = best_move(board, player, alpha, beta, depth + 1, 0);

                board[col] = '.';

                if (eval.score > best.score) {
                    best.score = eval.score;
                    best.line = col;
                }
                alpha = (alpha > best.score) ? alpha : best.score;
                if (alpha >= beta) {
                    break;
                }
            }
        }
    } else { // max_min = 0
        for (int col = 14; col >= 0; col--) {
            if (isValidMove(board, col)) {
                playMove(board, col, (player == 'R') ? 'B' : 'R');

                move_score eval = best_move(board, player, alpha, beta, depth + 1, 1);

                board[col] = '.';

                if (eval.score < best.score) {
                    best.score = eval.score;
                    best.line = col;
                }
                beta = (beta < best.score) ? beta : best.score;
                if (alpha >= beta) {
                    break;
                }
            }
        }
    }
    return best;
}

void printBoard(board_t board) {
    for (int i = 0; i < 15; i++) {
        printf("%c ", board[i]);
    }
    printf("\n");
}

int generateRandomMove(board_t board, int lower, int upper) {
    while (1) {
        int num = (rand() % (upper - lower + 1)) + lower;
        if (isValidMove(board, num)) {
            return num;
        }
    }
}

int main() {
    board_t board;
    initializeBoard(board);
    printf("Initializing Board...\n");
    printBoard(board);
    printf("\n");

    player_t user;
    printf("Red plays First\n");
    printf("Which Color do you choose? (R or B): ");
    scanf(" %c", &user);

    while (user != 'R' && user != 'B') {
        printf("Invalid choice. Please select 'R' or 'B': ");
        scanf(" %c", &user);
    }
    printf("\n");

    player_t computer = (user == 'R') ? 'B' : 'R';
    player_t current = 'R';

    while (1) {
        if (current == user) {
            int move;
            printf("Enter your move (1, 15): ");
            scanf("%d", &move);
            while (!isValidMove(board, move - 1)) {
                printf("Not a valid move. Enter move again: ");
                scanf("%d", &move);
            }
            playMove(board, move - 1, current);
        } else {
            printf("Computer is thinking...\n");
            move_score computerMove = best_move(board, current, INT_MIN, INT_MAX, 0, 1);
            playMove(board, computerMove.line , current);
        }

        printBoard(board);
        printf("\n");

        if (hasLost(board, current)) {
            if (current == user) {
                printf("OOPS! Computer Won\n");
            } else {
                printf("HURRAY! You Won\n");
            }
            break;
        }

        current = (current == user) ? computer : user;
    }

    return 0;
}
