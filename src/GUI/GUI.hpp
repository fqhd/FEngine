#ifndef GUI_H
#define GUI_H

#include "GUIButton.hpp"
#include "GUIImage.hpp"

#include <vector>


class GUI {
public:


     std::vector<GUIButton> buttons;
     std::vector<GUIImage> images;

};

#endif
