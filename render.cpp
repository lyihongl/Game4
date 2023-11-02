#include "inc/render.hpp"
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Render::Render() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}
Render::~Render(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Render::renderQuad(const std::vector<Quad> &quad, const Shader &sProgram) {
    // verticies
    std::vector<float> vertices;

    for (const Quad &q : quad) {
        vertices.push_back(q.topLeft().first);
        vertices.push_back(q.topLeft().second);
        vertices.push_back(q.topRight().first);
        vertices.push_back(q.topRight().second);
        vertices.push_back(q.bottomLeft().first);
        vertices.push_back(q.bottomLeft().second);

        vertices.push_back(q.bottomRight().first);
        vertices.push_back(q.bottomRight().second);
        vertices.push_back(q.topRight().first);
        vertices.push_back(q.topRight().second);
        vertices.push_back(q.bottomLeft().first);
        vertices.push_back(q.bottomLeft().second);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void *)0);

    glEnableVertexAttribArray(0);
    sProgram.Use();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}