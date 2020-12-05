#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "GUIRenderer.hpp"
#include "InputManager.hpp"



class GUIButton{
public:

	GUIButton(const glm::vec4& destRect, const ColorRGBA8& color);
	void update(InputManager& manager);
	void render(GUIRenderer& renderer, GLuint blankTextureID);
	bool isPressed();

private:
	
	bool m_isPressed = false;
	ColorRGBA8 m_baseColor;
	ColorRGBA8 m_currentColor;
	glm::vec4 m_destRect;
	std::string m_string;

};
#endif
