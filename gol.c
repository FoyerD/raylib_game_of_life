#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "raylib.h"

#define WIDTH 50
#define HEIGHT 50

#define WIN_WIDTH 500
#define WIN_HEIGHT 500 

#define CELL_SIZE 10

struct grid {
    short matrix[HEIGHT][WIDTH];
};

struct grid grids[2];
int curr_grid_id = 0;

void init_grid();
void draw_grid_cli();
void draw_grid();
void update_grid();
int wrap_index(int i, bool col);

int main(int argc, char** argv) {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Jhon Conway's Game of Life");
    init_grid();

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLANK);
            draw_grid();
        EndDrawing();

        update_grid();
        usleep(50000);

    }

    CloseWindow(); 
    return 0;
}



void init_grid() {
    int next_grid_id = (curr_grid_id + 1) % 2;
    struct grid* curr_grid = (grids + curr_grid_id);
    struct grid* next_grid =  (grids + next_grid_id);

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            curr_grid->matrix[row][col] = 0;
            next_grid->matrix[row][col] = 0;
        }
    }


    curr_grid->matrix[10][12] = 1;
    curr_grid->matrix[11][10] = 1;
    curr_grid->matrix[11][12] = 1;
    curr_grid->matrix[12][11] = 1;
    curr_grid->matrix[12][12] = 1;
}


void draw_grid_cli() {
    struct grid* curr_grid = (grids + curr_grid_id);

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            printf("%c", curr_grid->matrix[row][col] ? '*' : ' ');
        }
        printf("\n");
    }
}

void draw_grid() {
    struct grid* curr_grid = (grids + curr_grid_id);
    int cell_size = WIN_HEIGHT / HEIGHT;
    
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (curr_grid->matrix[row][col]) {
                DrawRectangle(row * cell_size, col * cell_size, cell_size, cell_size, RAYWHITE);
            }
        }
    }
}


void update_grid() {
    int n_neighbors = 0;
    int next_grid_id = (curr_grid_id + 1) % 2;
    struct grid* curr_grid = (grids+curr_grid_id);
    struct grid* next_grid = (grids+next_grid_id);

    system("clear");
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            n_neighbors = 0;

            // count neighbors
            n_neighbors += curr_grid->matrix[wrap_index(row-1, false)][wrap_index(col-1, true)];
            n_neighbors += curr_grid->matrix[wrap_index(row-1, false)][wrap_index(col, true)];
            n_neighbors += curr_grid->matrix[wrap_index(row-1, false)][wrap_index(col+1, true)];
            n_neighbors += curr_grid->matrix[wrap_index(row, false)][wrap_index(col-1, true)];
            n_neighbors += curr_grid->matrix[wrap_index(row, false)][wrap_index(col+1, true)];
            n_neighbors += curr_grid->matrix[wrap_index(row+1, false)][wrap_index(col-1, true)];
            n_neighbors += curr_grid->matrix[wrap_index(row+1, false)][wrap_index(col, true)];
            n_neighbors += curr_grid->matrix[wrap_index(row+1, false)][wrap_index(col+1, true)];

            // live cell
            if (curr_grid->matrix[row][col]) {
                // solitude
                if (n_neighbors < 2){
                    next_grid->matrix[row][col] = 0;
                }

                // yay yay yay!
                else if (n_neighbors == 2 || n_neighbors == 3) {
                    next_grid->matrix[row][col] = 1;
                }

                // overpopulation
                else {
                    next_grid->matrix[row][col] = 0;
                }
            }
            
            // dead cell(s)
            else {
                // its alive
                if (n_neighbors == 3) {
                    next_grid->matrix[row][col] = 1;
                }
                else {
                    next_grid->matrix[row][col] = curr_grid->matrix[row][col];
                }
            }
        }
    } 

    curr_grid_id = next_grid_id;
}


int wrap_index(int i, bool col) {
    int denumerator = col ? WIDTH : HEIGHT;
    if (i > 0) {
        i = i % denumerator;
    }
    else if (i < 0) {
        i = i % denumerator + denumerator;
    }

    return i;

}
