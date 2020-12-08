#pragma once
#include "GUIRenderer.hpp"

#include "stb_truetype.h"

class GUIFont {
public:

     void initFont();
     void renderFont(GUIRenderer& renderer, float x, float y, const char* data);

private:

     GLuint m_textureID;
     stbtt_bakedchar* m_cdata = nullptr; // ASCII 32..126 is 95 glyphs
     stbtt_fontinfo font;
     int i,j,ascent,baseline,ch=0;
     float scale, xpos=2; // leave a little padding in case the character extends left


};