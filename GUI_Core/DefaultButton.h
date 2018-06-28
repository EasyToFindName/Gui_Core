#pragma once

#include "Image.h"
#include "IButton.h"

#include <SFML/Graphics.hpp>

#include <memory>

class DefaultButton : public IButton {
public:
	DefaultButton(int posX, int posY, int sizeX, int sizeY);

	void setFillColor(const sf::Color& s);
public: //Drawable
	void draw(sf::RenderTarget& draw, sf::RenderStates states) const override;
public: //IButton
	bool isPointInside(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseOver() override;
	void onMouseOut() override;
	void onPressed(sf::Mouse::Button b, int x, int y) override;
	void onReleased(sf::Mouse::Button b, int x, int y) override;
private:
	sf::RectangleShape m_shape;
	sf::Color m_defaultColor;
	bool m_isPressed;

	int m_curPosX;
	int m_curPosY;
};