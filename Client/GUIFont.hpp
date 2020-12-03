#pragma once
#include "GUIRenderer.hpp"

#include "stb_truetype.h"

class GUIFont {
public:

     void initFont();
     void renderFont(GUIRenderer& renderer, float x, float y, const char* data);

     const stbtt_bakedchar* getBakedData() const;

private:

     stbtt_bakedchar m_cdata[96];
     GLuint m_textureID = 0;

};
