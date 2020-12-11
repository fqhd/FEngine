#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "GUIRenderer.hpp"
#include "InputManager.hpp"



class GUIButton{
public:

	GUIButton(const glm::vec4& destRect, GLuint textureID);
	void update(InputManager& manager);
	void render(GUIRenderer& renderer);
	bool isPressed();

private:

	glm::vec4 m_destRect;
	bool m_isPressed = false;
	GLuint m_textureID = 0;
	unsigned int m_textureIndex = 0;

};
#endif
