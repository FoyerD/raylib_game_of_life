#define WIDTH 160
#define HEIGHT 90

struct grid {
    short matrix[HEIGHT][WIDTH];
};

extern struct grid grids[2];
extern int curr_grid_id;


void init_grid();
void update_grid();
int wrap_index(int i, int col);
