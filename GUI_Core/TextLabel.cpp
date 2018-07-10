#include "TextLabel.h"

TextLabel::TextLabel(GuiElem* parent, const std::string& fontPath, const std::string& text, unsigned int charSize) : GuiElem(parent) {
	m_font = resources()->getFont(fontPath);

	if (m_font == nullptr) {
		throw std::logic_error("Couldn't load font");
	}

	m_text.setFont(*m_font);
	m_text.setString(text);
	m_text.setCharacterSize(charSize);
}


void TextLabel::setText(const std::string& text) {
	m_text.setString(text);
}


void TextLabel::setCharacterSize(unsigned int charSize) {
	m_text.setCharacterSize(charSize);
}

void TextLabel::setPosition(float x, float y) {
	m_text.setPosition(x, y);
}

void TextLabel::setSize(float width, float height) {
	if (width == 0 || height == 0) return;
	auto curSize = getSize();
	auto curScale = m_text.getScale();

	float scaleX = (width * curScale.x) / curSize.x;
	float scaleY = (height * curScale.y) / curSize.y;

	m_text.setScale(scaleX, scaleY);
}

void TextLabel::setColor(const sf::Color& c) {
	m_text.setFillColor(c);
}

sf::Vector2f TextLabel::getSize() const {
	auto boundingBox = m_text.getGlobalBounds();
	return sf::Vector2f(boundingBox.width, boundingBox.height);
}

sf::Vector2f TextLabel::getPosition() const {
	return m_text.getPosition();
}

void TextLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_text);
}







