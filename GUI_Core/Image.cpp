#pragma once

#include "Image.h"

Image::Image(std::unique_ptr<sf::Texture>&& t) : m_texture(std::move(t)) {
	setTexture(*m_texture);
}

sf::Vector2u Image::getSize() const {
	auto textureSize = m_texture->getSize();
	auto scale = getScale();

	return sf::Vector2u(textureSize.x * scale.x,
						textureSize.y * scale.y);
}

