#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOARD_SIZE (3)
#define MAX_MOVES (20)

typedef struct {
    short board[BOARD_SIZE][BOARD_SIZE];
    char moves[MAX_MOVES];
} node;

typedef struct QueueNode {
    node data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, node data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    
    q->rear->next = newNode;
    q->rear = newNode;
}

node dequeue(Queue* q) {
    if (isEmpty(q)) {
        perror("Queue is empty");
        exit(1);
    }

    QueueNode* temp = q->front;
    node data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return data;
}

int is_solved(node state) {
    short solved[3][3] = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    return memcmp(state.board, solved, sizeof(solved)) == 0;
}

node L(node current_node, short x, short y) {
    node new_node = current_node;
    // Implement the left move logic here to update the new_node state.
    switch (new_node.board[x][y])
    {
    case 1:
        new_node.board[x][y-1] = 5;
        break;
    case 2:
        new_node.board[x][y-1] = 2;
        break;
    case 3:
        new_node.board[x][y-1] = 1;
        break;
    case 4:
        new_node.board[x][y-1] = 4;
        break;
    case 5:
        new_node.board[x][y-1] = 6;
        break;
    case 6:
        new_node.board[x][y-1] = 3;
        break;
    default:
        break;
    }

    new_node.board[x][y] = 0;

    // Append the move to the end of the moves array
    char move[4];
    move[0] = 'L';
    move[1] = (char)(x+48);
    move[2] = (char)(y+48);
    move[3] = '\0';

    strcat(new_node.moves, move);
    return new_node;
}

node R(node current_node, short x, short y) {
    node new_node = current_node;
    // Implement the left move logic here to update the new_node state.
    switch (new_node.board[x][y])
    {
    case 1:
        new_node.board[x][y-1] = 3;
        break;
    case 2:
        new_node.board[x][y-1] = 2;
        break;
    case 3:
        new_node.board[x][y-1] = 6;
        break;
    case 4:
        new_node.board[x][y-1] = 4;
        break;
    case 5:
        new_node.board[x][y-1] = 1;
        break;
    case 6:
        new_node.board[x][y-1] = 5;
        break;
    default:
        break;
    }

    new_node.board[x][y] = 0;

    // Append the move to the end of the moves array
    char move[4];
    move[0] = 'L';
    move[1] = (char)(x+48);
    move[2] = (char)(y+48);
    move[3] = '\0';

    strcat(new_node.moves, move);
    return new_node;
}

node U(node current_node, short x, short y) {
    node new_node = current_node;
    // Implement the left move logic here to update the new_node state.
    switch (new_node.board[x][y])
    {
    case 1:
        new_node.board[x][y-1] = 4;
        break;
    case 2:
        new_node.board[x][y-1] = 1;
        break;
    case 3:
        new_node.board[x][y-1] = 3;
        break;
    case 4:
        new_node.board[x][y-1] = 6;
        break;
    case 5:
        new_node.board[x][y-1] = 5;
        break;
    case 6:
        new_node.board[x][y-1] = 2;
        break;
    default:
        break;
    }

    new_node.board[x][y] = 0;

    // Append the move to the end of the moves array
    char move[4];
    move[0] = 'L';
    move[1] = (char)(x+48);
    move[2] = (char)(y+48);
    move[3] = '\0';

    strcat(new_node.moves, move);
    return new_node;
}

node D(node current_node, short x, short y) {
    node new_node = current_node;
    // Implement the left move logic here to update the new_node state.
    switch (new_node.board[x][y])
    {
    case 1:
        new_node.board[x][y-1] = 2;
        break;
    case 2:
        new_node.board[x][y-1] = 6;
        break;
    case 3:
        new_node.board[x][y-1] = 3;
        break;
    case 4:
        new_node.board[x][y-1] = 1;
        break;
    case 5:
        new_node.board[x][y-1] = 5;
        break;
    case 6:
        new_node.board[x][y-1] = 4;
        break;
    default:
        break;
    }

    new_node.board[x][y] = 0;

    // Append the move to the end of the moves array
    char move[4];
    move[0] = 'L';
    move[1] = (char)(x+48);
    move[2] = (char)(y+48);
    move[3] = '\0';

    strcat(new_node.moves, move);
    return new_node;
}

void printBoard(node n) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%2d ", n.board[i][j]);
        }
        printf("\n");
    }
}

void bfs(node initial_state) {
    Queue queue;
    initQueue(&queue);
    
    enqueue(&queue, initial_state);
    
    while (!isEmpty(&queue)) {
        node current_node = dequeue(&queue);
        
        if (is_solved(current_node)) {
            printf("Found a solution!\n");
            // You can now output the moves to reach this solution if needed.
            break;
        }
        
        // Generate child nodes by making valid moves and enqueue them
        
        // You will need to implement the logic to generate child nodes here based on valid moves.
        // Update the state and moves in the child nodes and enqueue them.
    }
}

int main() {
    node initial_state;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            scanf("%hd", &initial_state.board[i][j]);
        }
    }

    short x = 1;
    short y = 2;

    node new = L(initial_state, x, y);

    // Assign individual characters, not string literals
    char moves[4];
    moves[0] = 'L';
    moves[1] = '2';
    moves[2] = '1';
    moves[3] = '\0';

    strcat(new.moves, moves);

    node new_new = L(new, x, y);

    printf("Moves: %s\n", new_new.moves);

    // bfs(initial_state);

    return 0;
}
