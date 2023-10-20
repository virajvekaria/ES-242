#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

enum LineStatus {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

#define MAX_LINES (15)
#define BOARD_SIZE (15)

int points[MAX_LINES] = {12, 13, 14, 15, 16, 23, 24, 25, 26, 34, 35, 36, 45, 46, 56};

typedef struct {
    int line;  /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

typedef char board_t[BOARD_SIZE];
typedef char player_t;

bool is_line_occupied(board_t board, int line) {
    return board[line] != NO;
}

player_t other_player(player_t player) {
    return (player == RED) ? BLUE : RED;
}

bool is_full(board_t board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == NO) {
            return false;
        }
    }
    return true;
}

void print_board(board_t board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        switch (board[i]) {
        case RED:
            printf("  R    ");
            break;
        case BLUE:
            printf("  B    ");
            break;
        case NO:
            printf("  .    ");
            break;
        }
    }
    printf("\n");

    // Print the lines associated with each position
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if(i<10){
         printf("%d:0%d  ", points[i], i);   
         continue;
        }
        printf("%d:%d  ", points[i], i);
    }
    printf("\n");
}

void make_move(board_t board, int line, player_t player) {
    board[line] = player;
}


int has_lost(board_t board, player_t player)
{
    int lines[] = {
        12, 13, 14, 15, 16, 23, 24, 25, 26, 34, 35, 36, 45, 46, 56
    };

    // Check if the AI player has formed a triangle
    for (int i = 0; i < 15; i++) {
        for (int j = i + 1; j < 15; j++) {
            for (int k = j + 1; k < 15; k++) {
                if (board[lines[i]] == player && board[lines[j]] == player && board[lines[k]] == player) {
                    return 1; // AI has lost
                }
            }
        }
    }

    return 0;
}



move_t best_move(board_t board, player_t player, int depth) {
    move_t response;
    response.line = -1;
    response.score = (player == BLUE) ? INT_MIN : INT_MAX;

    if (has_lost(board, player)) {
        response.score = -1;
        return response;
    }

    if (has_lost(board, other_player(player))) {
        response.score = 1;
        return response;
    }

    if (is_full(board) || depth == 0) {
        response.score = 0;
        return response;
    }

    for (int line = 0; line < MAX_LINES; line++) {
        if (!is_line_occupied(board, line)) {
            make_move(board, line, player);

            move_t next_move = best_move(board, other_player(player), depth - 1);

            if (player == BLUE) {
                if (next_move.score > response.score) {
                    response.score = next_move.score;
                    response.line = line;
                }
            } else {
                if (next_move.score < response.score) {
                    response.score = next_move.score;
                    response.line = line;
                }
            }

            make_move(board, line, NO);
        }
    }

    return response;
}

int main() {
    board_t game_board = {NO};
    player_t current_player;
    int depth = 6;

    char user_choice;
    printf("Do you want to start as Red (R) or Blue (B)? ");
    scanf(" %c", &user_choice);

    if (user_choice == 'R') {
        current_player = RED;
    } else if (user_choice == 'B') {
        current_player = BLUE;
    } else {
        printf("Invalid choice. Please select 'R' or 'B'.\n");
        return 1;
    }

    while (true) {
        printf("Current board:\n");
        print_board(game_board);

        if (has_lost(game_board, current_player)) {
            printf("%s player wins!\n", (current_player == RED) ? "Red" : "Blue");
            break;
        }

        if (is_full(game_board)) {
            printf("It's a draw!\n");
            break;
        }

        if (current_player == RED) {
            int chosen_line_index;
            printf("Enter the line to draw (0-14): ");
            scanf("%d", &chosen_line_index);

            if (chosen_line_index >= 0 && chosen_line_index < MAX_LINES && !is_line_occupied(game_board, chosen_line_index)) {
                make_move(game_board, chosen_line_index, current_player);
            } else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            move_t ai_move = best_move(game_board, current_player, depth);
            int chosen_line = ai_move.line;
            printf("AI (Blue) chose line %d\n", points[chosen_line]);
            make_move(game_board, chosen_line, current_player);
        }

        current_player = other_player(current_player);
    }

    return 0;
}
