#pragma once

#include <string>
#include <GLAD/glad.h>

namespace FEngine
{
	class Pixel
	{
	public:
		Pixel() {}
		GLubyte r = 0;
		GLubyte g = 0;
		GLubyte b = 0;
		GLubyte a = 0;
	};

	class Image
	{
	public:
		int loadFromFile(const std::string &path, int desiredChannels = 4);
		unsigned char *getData();
		Pixel getPixel(unsigned int x, unsigned int y);
		int getWidth();
		int getHeight();
		int getNumChannels();
		void free();

	private:
		int m_width = 0;
		int m_height = 0;
		int m_numChannels;
		unsigned char *m_imageData = nullptr;
	};
}
