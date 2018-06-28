#pragma once

#include <SFML/Graphics.hpp>

struct IButton : public sf::Drawable {
	virtual bool isPointInside(int x, int y) = 0;

	virtual void onMouseMoved(int x, int y) {}

	virtual void onMouseOver() {}
	virtual void onMouseOut() {}
	
	virtual void onPressed(sf::Mouse::Button b, int x, int y) {}
	virtual void onReleased(sf::Mouse::Button b, int x, int y) {}
};