#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

typedef int cube_state[24];

void init_cube(cube_state *state)
{
    for (int i = 0; i < 24; i++)
    {
        (*state)[i] = floor(i/6);
    }
}

void swap_elements(cube_state *state, int index1, int index2)
{
    // Check if the indices are within bounds
    if (index1 < 0 || index1 >= 24 || index2 < 0 || index2 >= 24)
    {
        printf("Error: Indices out of bounds\n");
        return;
    }

    // Swap the elements at index1 and index2
    int temp = (*state)[index1];
    (*state)[index1] = (*state)[index2];
    (*state)[index2] = temp;
}

void R(cube_state *state){
    // 1 10 17 21
    // 3 8 19 23
    swap_elements(&state, 1, 21);
    swap_elements(&state, 21, 10);
    swap_elements(&state, 10, 17);
    swap_elements(&state, 3, 23);
    swap_elements(&state, 23, 8);
    swap_elements(&state, 8, 19);
    swap_elements(&state, 4, 5);
    swap_elements(&state, 4, 7);
    swap_elements(&state, 4, 6);
}

void R_prime(cube_state *state){
    // 1 10 17 21
    // 3 8 19 23
    swap_elements(&state, 1, 17);
    swap_elements(&state, 17, 10);
    swap_elements(&state, 10, 21);
    swap_elements(&state, 3, 19);
    swap_elements(&state, 19, 8);
    swap_elements(&state, 8, 23);
    swap_elements(&state, 4, 6);
    swap_elements(&state, 4, 7);
    swap_elements(&state, 4, 5);
}

void U(cube_state *state){
    swap_elements(&state, 0, 4);
    swap_elements(&state, 4, 8);
    swap_elements(&state, 12, 8);
    swap_elements(&state, 1, 5);
    swap_elements(&state, 5, 9);
    swap_elements(&state, 13, 9);
    swap_elements(&state, 16, 17);
    swap_elements(&state, 16, 19);
    swap_elements(&state, 16, 18);
}

void U_prime(cube_state *state){
    swap_elements(&state, 0, 4);
    swap_elements(&state, 12, 0);
    swap_elements(&state, 12, 8);
    swap_elements(&state, 1, 5);
    swap_elements(&state, 13, 1);
    swap_elements(&state, 13, 9);
    swap_elements(&state, 16, 18);
    swap_elements(&state, 16, 19);
    swap_elements(&state, 16, 17);
}

void F(cube_state *state){
    // 4 15 18 21
    // 6 13 19 20
    swap_elements(&state, 4, 21);
    swap_elements(&state, 4, 18);
    swap_elements(&state, 18, 15);
    swap_elements(&state, 6, 20);
    swap_elements(&state, 6, 19);
    swap_elements(&state, 19, 13);
    swap_elements(&state, 0, 1);
    swap_elements(&state, 0, 3);
    swap_elements(&state, 0, 2);
}

void F_prime(cube_state *state){
    // 4 15 18 21
    // 6 13 19 20
    swap_elements(&state, 4, 21);
    swap_elements(&state, 21, 15);
    swap_elements(&state, 15, 18);
    swap_elements(&state, 6, 20);
    swap_elements(&state, 20, 13);
    swap_elements(&state, 13, 19);
    swap_elements(&state, 0, 2);
    swap_elements(&state, 0, 3);
    swap_elements(&state, 0, 1);
}

void R2(cube_state *state){
    // 4 15 18 21
    // 6 13 19 20
    swap_elements(&state, 1, 10);
    swap_elements(&state, 3, 8);
    swap_elements(&state, 19, 23);
    swap_elements(&state, 17, 21);
    swap_elements(&state, 5, 6);
    swap_elements(&state, 4, 7);
}

void U2(cube_state *state){
    // 4 15 18 21
    // 6 13 19 20
    swap_elements(&state, 0, 8);
    swap_elements(&state, 1, 9);
    swap_elements(&state, 4, 12);
    swap_elements(&state, 5, 13);
    swap_elements(&state, 16, 19);
    swap_elements(&state, 17, 18);
}

void F2(cube_state *state){
    // 4 15 18 21
    // 6 13 19 20
    swap_elements(&state, 4, 15);
    swap_elements(&state, 6, 13);
    swap_elements(&state, 19, 20);
    swap_elements(&state, 18, 21);
    swap_elements(&state, 0, 3);
    swap_elements(&state, 1, 2);
}

