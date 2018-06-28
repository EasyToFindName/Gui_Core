#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Image : public sf::Sprite {
public:
	Image(std::unique_ptr<sf::Texture>&& t);

	sf::Vector2u getSize() const;
private:
	std::unique_ptr<sf::Texture> m_texture;
};