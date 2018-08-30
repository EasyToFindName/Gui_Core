#include "ResourceCacher.h"

sf::Font* ResourceCacher::loadFont(const std::string& filePath) {
	auto font = std::make_unique<sf::Font>();
	
	if (!font->loadFromFile(filePath)) {
		return nullptr;
	}

	auto ret = font.get();
	m_fonts[filePath] = std::move(font);
	return ret;
}

sf::Texture* ResourceCacher::loadTexture(const std::string& filePath) {
	auto texture = std::make_unique<sf::Texture>();

	if (!texture->loadFromFile(filePath)) {
		return nullptr;
	}

	auto ret = texture.get();
	m_textures[filePath] = std::move(texture);
	return ret;
}


sf::Font* ResourceCacher::getFont(const std::string& filePath) {
	auto iter = m_fonts.find(filePath);

	if (iter != m_fonts.end()) {
		return iter->second.get();
	}

	return loadFont(filePath);
}


sf::Texture* ResourceCacher::getTexture(const std::string& filePath) {
	auto iter = m_textures.find(filePath);

	if (iter != m_textures.end()) {
		return iter->second.get();
	}

	return loadTexture(filePath);
}

