#include "inc/grid.hpp"

Grid::Grid(unsigned int screen_w, unsigned int screen_h, unsigned int cell_size)
    : screen_w(screen_w), screen_h(screen_h), cell_size(cell_size) {
        x_offset = 0;
        y_offset = 0;
}