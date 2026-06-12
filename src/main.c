#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "raylib.h"
#include "gol_grid.h"

#define WIN_WIDTH WIDTH* 10
#define WIN_HEIGHT HEIGHT * 10

#define CELL_SIZE (WIN_HEIGHT/HEIGHT)
#define BASE_SLEEP 50000
#define SLEEP_STEP 5000

//mouse pos
int mouse_x = 0;
int mouse_y = 0;
int cursor_cell_col = 0;
int cursor_cell_row = 0;

// key settings
int sleep_time = BASE_SLEEP;
int quit = 0;
int stop = 1;

void draw_grid_cli();
void draw_grid();
void check_keys();
void check_mouse();
void update_mouse();

int main(int argc, char** argv) {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Jhon Conway's Game of Life");
    SetTargetFPS(60);
    init_grid();

    while (!WindowShouldClose() && !quit)
    {
        if(quit) {
            break;
        }

        BeginDrawing();
            ClearBackground(BLANK);
            draw_grid();
        EndDrawing();

        if (!stop) {
            update_grid();
        }

        // updates
        update_mouse();
        check_keys();
        check_mouse();

        usleep(sleep_time);

    }

    CloseWindow(); 
    return 0;
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
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (curr_grid->matrix[row][col] && 
                !(cursor_cell_row == row && cursor_cell_col == col)) {
                DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, RAYWHITE);
            }
        }
    }
}

void check_keys() {
    if (IsKeyPressed(KEY_Q)) {
        quit = 1;
    }
    
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_J)) {
        sleep_time += SLEEP_STEP;
    }
    
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_K)) {
        sleep_time -= sleep_time-SLEEP_STEP > 0 ? SLEEP_STEP : 0;
    }

    if (IsKeyReleased(KEY_SPACE)) {
        stop = !stop;
    }
}

void check_mouse() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        grids[curr_grid_id].matrix[cursor_cell_row][cursor_cell_col] = 1;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        grids[curr_grid_id].matrix[cursor_cell_row][cursor_cell_col] = 0;
    }
    
    DrawRectangle(cursor_cell_col * CELL_SIZE, cursor_cell_row * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
}

void update_mouse() {
    mouse_x = GetMouseX();
    mouse_y = GetMouseY();
    cursor_cell_col = (mouse_x - (mouse_x % CELL_SIZE)) / CELL_SIZE;
    cursor_cell_row = (mouse_y - (mouse_y % CELL_SIZE)) / CELL_SIZE;
}
