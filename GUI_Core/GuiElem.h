#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceCacher.h"

class GuiElem : public sf::Drawable {
public:
	explicit GuiElem(GuiElem* parent) : m_parent(parent) {}
	virtual ~GuiElem() = default;

	virtual sf::Vector2f getSize() const = 0;
	virtual sf::Vector2f getPosition() const = 0;

	virtual void setSize(float width, float height) = 0;
	virtual void setPosition(float x, float y) = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	virtual ResourceCacher* resources() { 
		if (m_parent != nullptr) return m_parent->resources(); 
		else return nullptr; 
	}

private:
	GuiElem* m_parent;

};