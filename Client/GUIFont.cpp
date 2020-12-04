#include <iostream>

#define STB_TRUETYPE_IMPLEMENTATION
#include "GUIFont.hpp"

void GUIFont::initFont(){

     unsigned char* ttf_buffer = new unsigned char[1<<20];
     unsigned char* temp_bitmap = new unsigned char[512*512];
     m_cdata = new stbtt_bakedchar[96];



     fread(ttf_buffer, 1, 1<<20, fopen("res/fonts/arial.ttf", "rb"));
     stbtt_BakeFontBitmap(ttf_buffer,0, 32.0, temp_bitmap,512,512, 32,96, m_cdata);
     glGenTextures(1, &m_textureID);
     glBindTexture(GL_TEXTURE_2D, m_textureID);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
     glBindTexture(GL_TEXTURE_2D, 0);

     delete[] ttf_buffer;
     delete[] temp_bitmap;

}

void GUIFont::renderFont(GUIRenderer& renderer, float x, float y, const char* text) {

     while (*text) {
        if (*text >= 32 && *text < 128) {
           stbtt_aligned_quad q;
           stbtt_GetBakedQuad(m_cdata, 512,512, *text-32, &x,&y,&q,1);//1=opengl & d3d10+,0=d3d9
           renderer.draw(glm::vec4(q.x0, q.y0, q.x1 - q.x0, q.y1 - q.y0), glm::vec4(q.s0, 1.0f - q.t1, q.s1 - q.s0, q.t1 - q.t0), m_textureID, ColorRGBA8());
        }
        ++text;
     }

}
