#pragma once
#include <SFML/Graphics.hpp>

class Textbox : public sf::Text {
public:
	Textbox(const sf::Font& f);
	~Textbox();
};

