#pragma once
#include "GuiElem.h"

#include <SFML/Graphics.hpp>

class TextLabel : public GuiElem {
public:
	TextLabel(Container* parent, const std::string& fontPath, const std::string& text = "", unsigned int charSize = 30);

	void setText(const std::string& text);
	void setCharacterSize(unsigned int charSize);
	void setColor(const sf::Color& color);

public: //GuiElem
	virtual void setPosition(float x, float y) override;
	virtual void setSize(float x, float y) override;

	virtual sf::Vector2f getPosition() const override;
	virtual sf::Vector2f getSize() const override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Font* m_font;
	sf::Text m_text;
};

