#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "raylib.h"

#define WIDTH 192
#define HEIGHT 108

#define WIN_WIDTH GetScreenWidth()
#define WIN_HEIGHT GetScreenHeight()

#define CELL_SIZE 10
#define BASE_SLEEP 50000
#define SLEEP_STEP 5000

struct grid {
    short matrix[HEIGHT][WIDTH];
};

// grids
struct grid grids[2];
int curr_grid_id = 0;

// key settings
int sleep_time = BASE_SLEEP;
int quit = false;

void init_grid();
void draw_grid_cli();
void draw_grid();
void update_grid();
void check_keys();
int wrap_index(int i, bool col);

int main(int argc, char** argv) {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Jhon Conway's Game of Life");
    init_grid();

    while (!WindowShouldClose() && !quit)
    {
        BeginDrawing();
            ClearBackground(BLANK);
            draw_grid();
        EndDrawing();

        update_grid();
        check_keys();
        usleep(sleep_time);

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

    system("clear");
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
                DrawRectangle(col * cell_size, row * cell_size, cell_size, cell_size, RAYWHITE);
            }
        }
    }
    DrawRectangle(0, 0, cell_size, cell_size, RAYWHITE);
}


void update_grid() {
    int n_neighbors = 0;
    int next_grid_id = (curr_grid_id + 1) % 2;
    struct grid* curr_grid = (grids+curr_grid_id);
    struct grid* next_grid = (grids+next_grid_id);

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

                // amaze amaze amaze
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





void check_keys() {
    if (IsKeyPressed(KEY_Q)) {
        quit = true;
    }
    
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_J)) {
        sleep_time += SLEEP_STEP;
    }
    
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_K)) {
        sleep_time -= sleep_time-SLEEP_STEP > 0 ? SLEEP_STEP : 0;
    }
}
