#include "inc/quad.hpp"

Quad::Quad(float w, float h, float x, float y) : x(x), y(y), w(w), h(h) {
}

std::pair<float, float> Quad::topLeft() const {
    return {x-w/2, y-h/2};
}
std::pair<float, float> Quad::topRight() const {
    return {x+w/2, y-h/2};
}
std::pair<float, float> Quad::bottomRight() const {
    return {x+w/2, y+h/2};
}
std::pair<float, float> Quad::bottomLeft() const {
    return {x-w/2, y+h/2};
}