#include "DefaultButton.h"
#include <iostream>

DefaultButton::DefaultButton(int posX, int posY, int sizeX, int sizeY)
	: m_shape(sf::Vector2f(sizeX, sizeY)), m_isPressed(false), m_curPosX(0), m_curPosY(0)
{
	m_shape.setPosition(posX, posY);
}

bool DefaultButton::isPointInside(int x, int y) {
	return m_shape.getGlobalBounds().contains(sf::Vector2f(x, y));
}

void DefaultButton::setFillColor(const sf::Color& s) {
	m_shape.setFillColor(s);
	m_defaultColor = s;
}

void DefaultButton::onMouseMoved(int x, int y) {
	std::cout << "onMouseMoved(" << x << ", " << y << ")\n";

	if (m_isPressed) {
		std::cout << x - m_curPosX << " " << y - m_curPosY << "\n";
		m_shape.move(x - m_curPosX, y - m_curPosY);
		m_curPosX = x;
		m_curPosY = y;
	}
}

void DefaultButton::onMouseOver() {
	std::cout << "onMouseOver()\n";
	m_shape.setFillColor(sf::Color(200, 168, 32, 255));
}

void DefaultButton::onMouseOut() {
	std::cout << "onMouseOut()\n";
	m_shape.setFillColor(m_defaultColor);
	m_isPressed = false;
}

void DefaultButton::onPressed(sf::Mouse::Button b, int x, int y) {
	std::cout << "onPressed()\n";
	
	if (b == sf::Mouse::Button::Left) {
		m_shape.setFillColor(sf::Color(200, 0, 0, 255));
	}
	else {
		m_shape.setFillColor(sf::Color(0, 200, 200, 255));
	}

	m_isPressed = true;
	m_curPosX = x;
	m_curPosY = y;

	std::cout << "Setting up curPos(" << m_curPosX
			  << ", " << m_curPosY << ")\n";
}

void DefaultButton::onReleased(sf::Mouse::Button b, int x, int y) {
	std::cout << "onReleased()\n";
	m_shape.setFillColor(m_defaultColor);

	m_isPressed = false;
}

void DefaultButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_shape);
}
