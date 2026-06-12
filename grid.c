#define WIDTH 160
#define HEIGHT 90

struct grid {
    short matrix[HEIGHT][WIDTH];
};

// grids
struct grid grids[2];
int curr_grid_id = 0;


void init_grid();
void update_grid();
int wrap_index(int i, int col);

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



 void update_grid() { 
    int n_neighbors = 0;
    int next_grid_id = (curr_grid_id + 1) % 2;
    struct grid* curr_grid = (grids+curr_grid_id);
    struct grid* next_grid = (grids+next_grid_id);

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            n_neighbors = 0;

            // count neighbors
            n_neighbors += curr_grid->matrix[wrap_index(row-1, 0)][wrap_index(col-1, 1)];
            n_neighbors += curr_grid->matrix[wrap_index(row-1, 0)][wrap_index(col, 1)];
            n_neighbors += curr_grid->matrix[wrap_index(row-1, 0)][wrap_index(col+1, 1)];
            n_neighbors += curr_grid->matrix[wrap_index(row, 0)][wrap_index(col-1, 1)];
            n_neighbors += curr_grid->matrix[wrap_index(row, 0)][wrap_index(col+1, 1)];
            n_neighbors += curr_grid->matrix[wrap_index(row+1, 0)][wrap_index(col-1, 1)];
            n_neighbors += curr_grid->matrix[wrap_index(row+1, 0)][wrap_index(col, 1)];
            n_neighbors += curr_grid->matrix[wrap_index(row+1, 0)][wrap_index(col+1, 1)];

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

int wrap_index(int i, int col) {
    int denumerator = col ? WIDTH : HEIGHT;
    if (i > 0) {
        i = i % denumerator;
    }
    else if (i < 0) {
        i = i % denumerator + denumerator;
    }
    return i;

}


