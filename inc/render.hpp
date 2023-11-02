#pragma once

#include "quad.hpp"

#include<vector>
#include <shaders.hpp>
#include <glm/glm.hpp>

class Render {
    uint32_t VBO, VAO;
    glm::mat4 MVP;
    public:
    Render();
    ~Render();
    Render(Render &) = delete;
    Render(Render &&) = delete;
    Render operator=(Render&) = delete;
    void renderQuad(const std::vector<Quad>&, const Shader&);
};