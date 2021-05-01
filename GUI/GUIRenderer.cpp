#include "GUIRenderer.hpp"

#include <algorithm>


Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tID) {

     textureID = tID;

     topLeft.setPosition(destRect.x, destRect.y + destRect.w);
     topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
     topLeft.setDepth(depth);

     bottomLeft.setPosition(destRect.x, destRect.y);
     bottomLeft.setUV(uvRect.x, uvRect.y);
     bottomLeft.setDepth(depth);

     bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
     bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
     bottomRight.setDepth(depth);

     topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
     topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
     topRight.setDepth(depth);

}


void GUIRenderer::init() {
     glGenVertexArrays(1, &m_vaoID);
     glBindVertexArray(m_vaoID);

     glGenBuffers(1, &m_vboID);
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

     glEnableVertexAttribArray(0);
     glEnableVertexAttribArray(1);
     glEnableVertexAttribArray(2);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)offsetof(GUIVertex, position));
     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)offsetof(GUIVertex, uv));

     glBindBuffer(GL_ARRAY_BUFFER, 0);

     glBindVertexArray(0);
}

void GUIRenderer::destroy() {

     if (m_vaoID != 0) {
          glDeleteVertexArrays(1, &m_vaoID);
          m_vaoID = 0;
     }

     if (m_vboID != 0) {
          glDeleteBuffers(1, &m_vboID);
          m_vboID = 0;
     }

}

void GUIRenderer::begin() {
     m_renderBatches.clear();

     m_glyphs.clear();
}

void GUIRenderer::end() {

     m_glyphPointers.resize(m_glyphs.size());
     for (unsigned int i = 0; i < m_glyphs.size(); i++) {
          m_glyphPointers[i] = &m_glyphs[i];
     }

     sortGlyphs();
     createRenderBatches();
}

void GUIRenderer::draw(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint textureID) {
    m_glyphs.emplace_back(destRect, uvRect, depth, textureID);
}

void GUIRenderer::render() {

    glBindVertexArray(m_vaoID);

    for (size_t i = 0; i < m_renderBatches.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].textureID);

        glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
    }

    glBindVertexArray(0);
}

void GUIRenderer::createRenderBatches() {

    std::vector <GUIVertex> vertices;
    vertices.resize(m_glyphPointers.size() * 6);

    if (m_glyphPointers.empty()) {
        return;
    }

    int offset = 0;
    int cv = 0;

    m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->textureID);
    vertices[cv++] = m_glyphPointers[0]->topLeft;
    vertices[cv++] = m_glyphPointers[0]->bottomLeft;
    vertices[cv++] = m_glyphPointers[0]->bottomRight;
    vertices[cv++] = m_glyphPointers[0]->bottomRight;
    vertices[cv++] = m_glyphPointers[0]->topRight;
    vertices[cv++] = m_glyphPointers[0]->topLeft;
    offset += 6;

    for (size_t cg = 1; cg < m_glyphPointers.size(); cg++) {

        if (m_glyphPointers[cg]->textureID != m_glyphPointers[cg - 1]->textureID) {
            m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->textureID);
        } else {
            m_renderBatches.back().numVertices += 6;
        }
        vertices[cv++] = m_glyphPointers[cg]->topLeft;
        vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
        vertices[cv++] = m_glyphPointers[cg]->bottomRight;
        vertices[cv++] = m_glyphPointers[cg]->bottomRight;
        vertices[cv++] = m_glyphPointers[cg]->topRight;
        vertices[cv++] = m_glyphPointers[cg]->topLeft;
        offset += 6;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GUIVertex), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GUIVertex), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void GUIRenderer::sortGlyphs() {
    std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
}

bool GUIRenderer::compareTexture(Glyph* a, Glyph* b) {
    return (a->textureID < b->textureID);
}
