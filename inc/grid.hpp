#pragma once

#include <vector>


class Grid {
    unsigned int screen_w;
    unsigned int screen_h;
    unsigned int cell_size;
    float x_offset, y_offset;
    std::vector<std::vector<unsigned int>> data;
    public:
    Grid(unsigned int screen_w, unsigned int screen_h, unsigned int cell_size);
};