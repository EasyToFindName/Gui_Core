#pragma once

#include "GuiElem.h"
#include <SFML/Graphics.hpp>

class GuiActiveElem : public GuiElem {
public:
	GuiActiveElem(GuiElem* parent):GuiElem(parent) {}

	virtual bool isPointInside(float x, float y) = 0;

	virtual void onMouseMoved(int x, int y) {}

	virtual void onMouseOver() {}
	virtual void onMouseOut() {}
	
	virtual void onPressed(sf::Mouse::Button b, int x, int y) {}
	virtual void onReleased(sf::Mouse::Button b, int x, int y) {}
};