#pragma once

#include "Image.h"
#include <stdexcept>

#include "ResourceCacher.h"

Image::Image(GuiElem* parent, const std::string& filePath): GuiElem(parent) {
	m_texture = resources()->getTexture(filePath);

	if (m_texture == nullptr) {
		throw std::logic_error("Couldn't load Image");
	}

	m_sprite.setTexture(*m_texture);
}

Image::Image(GuiElem* parent, const std::string& filePath, float width, float height) : Image(parent, filePath) {
	setSize(width, height);
}

void Image::setScale(float x, float y) {
	if (x == 0.0f || y == 0.0f) return;
	m_sprite.setScale(x, y);
}

sf::Vector2f Image::getSize() const {
	auto textureSize = m_texture->getSize();
	auto scale = m_sprite.getScale();

	return sf::Vector2f(textureSize.x * scale.x,
						textureSize.y * scale.y);
}

sf::Vector2f Image::getPosition() const {
	return m_sprite.getPosition();
}

void Image::setSize(float width, float height) {	
	if (width == 0.0f || height == 0.0f) return;

	auto currentSize = this->getSize();
	if (currentSize.x == width && currentSize.y == height) return;

	auto currentScale = m_sprite.getScale();
	float scaleX = (width * currentScale.x) / currentSize.x;
	float scaleY = (height * currentScale.y) / currentSize.y;

	m_sprite.setScale(scaleX, scaleY);
}

void Image::setPosition(float x, float y) {
	m_sprite.setPosition(sf::Vector2f(x, y));
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite);
}

