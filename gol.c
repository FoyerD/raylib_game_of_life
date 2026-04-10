#include <stdlib.h>

#define WIDTH 100
#define LENGTH 100

struct grid {
    short matrix[LENGTH][WIDTH];
};

void init_grid(struct grid grid);
void draw_grid(struct grid grid);
void update_grid(struct grid grid);

int main(int argc, char** argv) {
    struct grid grid;
    init_grid(grid);

    return 0;
}



void init_grid(struct grid grid) {
    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < WIDTH; col++) {
            grid.matrix[row][col] = (row + col) % 2 == 0;
        }
    }
}
