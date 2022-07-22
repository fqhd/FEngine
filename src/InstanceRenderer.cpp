#include "InstanceRenderer.hpp"

void InstanceRenderer::init(){
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

    float vertices[] = {
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f,

        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,

        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

        -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &instanceBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Object), (void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Object), (void*)(1 * 4 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Object), (void*)(2 * 4 * sizeof(float)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Object), (void*)(3 * 4 * sizeof(float)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Object), (void*)(4 * 4 * sizeof(float)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void InstanceRenderer::begin(){
    objects.clear();
}

void InstanceRenderer::add(const glm::mat4& matrix, const Color& color){
    objects.emplace_back(matrix, color);
}

void InstanceRenderer::end(){
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER, objects.size() * sizeof(objects[0]), objects.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstanceRenderer::draw(){
    glBindVertexArray(vaoID);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, objects.size());
    glBindVertexArray(0);
}

void InstanceRenderer::destroy(){
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
    glDeleteBuffers(1, &instanceBuffer);
}
