// The MIT License (MIT)
//
// Copyright (c) 2015 Benjamin Arnold
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

// Determines how we should sort the glyphs
enum class GlyphSortType {
     NONE,
     FRONT_TO_BACK,
     BACK_TO_FRONT,
     TEXTURE
};

struct Position {
     float x;
     float y;
};

struct ColorRGBA8 {
   ColorRGBA8() : r(255), g(255), b(255), a(255) { }
   ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
       r(R), g(G), b(B), a(A) { }
   GLubyte r;
   GLubyte g;
   GLubyte b;
   GLubyte a;
};

struct UV {
     float u;
     float v;
};

//The vertex definition
struct GUIVertex {
     //This is the position struct. When you store a struct or class
     //inside of another struct or class, it is called composition. This is
     //layed out exactly the same in memory as if we had a float position[2],
     //but doing it this way makes more sense.
     Position position;

     //4 bytes for r g b a color.
     ColorRGBA8 color;

     //UV texture coordinates.
     UV uv;

     void setPosition(float x, float y) {
          position.x = x;
          position.y = y;
     }

     void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
          color.r = r;
          color.g = g;
          color.b = b;
          color.a = a;
     }

     void setUV(float u, float v) {
          uv.u = u;
          uv.v = v;
     }
};

// A glyph is a single quad. These are added via SpriteBatch::draw
class Glyph {
public:
    Glyph() {};
    Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color);

    GLuint texture;
    float depth;

    GUIVertex topLeft;
    GUIVertex bottomLeft;
    GUIVertex topRight;
    GUIVertex bottomRight;
private:

};

// Each render batch is used for a single draw call
class RenderBatch {
public:
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
        numVertices(NumVertices), texture(Texture) {
    }
    GLuint offset = 0;
    GLuint numVertices = 0;
    GLuint texture = 0;
};

// The SpriteBatch class is a more efficient way of drawing sprites
class GUIRenderer
{
public:

    // Initializes the spritebatch
    void init();
    void dispose();

    // Begins the spritebatch
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

    // Ends the spritebatch
    void end();

    // Adds a glyph to the spritebatch
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);

    // Renders the entire SpriteBatch to the screen
    void renderBatch();

private:
    // Creates all the needed RenderBatches
    void createRenderBatches();

    // Generates our VAO and VBO
    void createVertexArray();

    // Sorts glyphs according to _sortType
    void sortGlyphs();

    // Comparators used by sortGlyphs()
    static bool compareFrontToBack(Glyph* a, Glyph* b);
    static bool compareBackToFront(Glyph* a, Glyph* b);
    static bool compareTexture(Glyph* a, Glyph* b);

    GLuint _vbo;
    GLuint _vao;

    GlyphSortType _sortType;

    std::vector<Glyph*> _glyphPointers; ///< This is for sorting
    std::vector<Glyph> _glyphs; ///< These are the actual glyphs
    std::vector<RenderBatch> _renderBatches;
};
