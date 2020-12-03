#include <iostream>

#define STB_TRUETYPE_IMPLEMENTATION
#include "GUIFont.hpp"

void GUIFont::initFont(){
     unsigned char ttf_buffer[1<<20];
     unsigned char temp_bitmap[512*512];

     FILE* f = fopen("res/fonts/arial.ttf", "rb");
     if(!f){
          printf("failed to load in ttf\n");
     }

     fread(ttf_buffer, 1, 1<<20, f);

     if(!ttf_buffer){
          printf("failed to load in map\n");
     }

     stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, m_cdata); // no guarantee this fits!
     glGenTextures(1, &m_textureID);
     glBindTexture(GL_TEXTURE_2D, m_textureID);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glBindTexture(GL_TEXTURE_2D, 0);
}

void GUIFont::renderFont(GUIRenderer& renderer, float x, float y, const char* text) {


     while (*text) {
          if (*text >= 32 && *text < 128) {
               stbtt_aligned_quad q;
               stbtt_GetBakedQuad(m_cdata, 512,512, *text-32, &x,&y,&q,1);

               renderer.draw(glm::vec4(q.x0, q.y0, q.x1, q.y1), glm::vec4(q.s0, q.t0, q.s1, q.t1), m_textureID, ColorRGBA8());

          }
          ++text;
     }


}

const stbtt_bakedchar* GUIFont::getBakedData() const {
     return m_cdata;
}
