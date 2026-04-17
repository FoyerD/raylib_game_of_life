#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "raylib.h"

#define WIDTH 20
#define LENGTH 20

#define WIN_WIDTH 800
#define WIN_LENGTH 450

struct grid {
    short matrix[LENGTH][WIDTH];
};

struct grid grids[2];
int curr_grid_id = 0;

void init_grid();
void draw_grid();
void update_grid();

int main(int argc, char** argv) {
    InitWindow(WIN_LENGTH, WIN_LENGTH, "raylib example - basic window");
    init_grid();

    while (!WindowShouldClose())
    {
        system("clear");
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            draw_grid();
        EndDrawing();

        update_grid();
        sleep(1);

    }

    CloseWindow(); 
    return 0;
}



void init_grid() {
    int next_grid_id = (curr_grid_id + 1) % 2;
    struct grid* curr_grid = (grids + curr_grid_id);
    struct grid* next_grid =  (grids + next_grid_id);

    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < WIDTH; col++) {
            curr_grid->matrix[row][col] = 0;
            next_grid->matrix[row][col] = 0;
        }
    }


    curr_grid->matrix[10][12] = 1;
    curr_grid->matrix[11][10] = 1;
    curr_grid->matrix[12][12] = 1;
    curr_grid->matrix[12][11] = 1;
    curr_grid->matrix[12][12] = 1;
}


void draw_grid() {
    struct grid* curr_grid = (grids + curr_grid_id);

    printf("curr grid: %d\n", curr_grid_id);
    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < WIDTH; col++) {
            printf("%c", curr_grid->matrix[row][col] ? '*' : ' ');
        }
        printf("\n");
    }
}


void update_grid() {
    int n_neighbors = 0;
    int next_grid_id = (curr_grid_id + 1) % 2;
    struct grid* curr_grid = (grids+curr_grid_id);
    struct grid* next_grid = (grids+next_grid_id);

    for (int row = 1; row < LENGTH-1; row++) {
        for (int col = 1; col < WIDTH-1; col++) {
            n_neighbors = 0;

            // count neighbors
            n_neighbors += curr_grid->matrix[row-1][col-1];
            n_neighbors += curr_grid->matrix[row-1][col];
            n_neighbors += curr_grid->matrix[row-1][col+1];
            n_neighbors += curr_grid->matrix[row][col-1];
            n_neighbors += curr_grid->matrix[row][col+1];
            n_neighbors += curr_grid->matrix[row+1][col-1];
            n_neighbors += curr_grid->matrix[row+1][col];
            n_neighbors += curr_grid->matrix[row+1][col+1];

            // live cell
            if (curr_grid->matrix[row][col]) {
                if (n_neighbors < 2){
                    next_grid->matrix[row][col] = 0;
                }
                else if (n_neighbors == 2 || n_neighbors == 3) {
                    next_grid->matrix[row][col] = 1;
                }
                else {
                    next_grid->matrix[row][col] = 0;
                }
            }
            
            // dead cell(s)
            else {
                if (n_neighbors == 3) {
                    next_grid->matrix[row][col] = 1;
                }
            }
        }
    } 

    curr_grid_id = next_grid_id;
}
