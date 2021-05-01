#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

#include "GUIVertex.hpp"

#include <vector>
#include <GL/glew.h>


class Glyph {
public:
    Glyph() {};
    Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tID);

    GLuint textureID = 0;

    GUIVertex topLeft;
    GUIVertex bottomLeft;
    GUIVertex topRight;
    GUIVertex bottomRight;


};

class Batch {
public:
    Batch(GLuint o, GLuint n, GLuint t) {
        offset = o;
        numVertices = n;
        textureID = t;
    }

    GLuint offset = 0;
    GLuint numVertices = 0;
    GLuint textureID = 0;
};

class GUIRenderer {
public:

    void init();
    void begin();
    void end();
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint texture);
    void destroy();

    void render();

private:

    void createRenderBatches();

    void sortGlyphs();

    static bool compareTexture(Glyph* a, Glyph* b);

    GLuint m_vboID;
    GLuint m_vaoID;

    std::vector<Glyph*> m_glyphPointers;
    std::vector<Glyph> m_glyphs;
    std::vector<Batch> m_renderBatches;
};

#endif
