#include "Gui.h"

#include <SFML/System.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	Gui mainWindowGui(window);

	mainWindowGui.loadFont("Arial", "./res/fonts/arial.ttf");
	mainWindowGui.loadCursor("GothicCursor", "./res/cursors/Cursor_Goth_Cursor.png");
	
	mainWindowGui.setCursor("GothicCursor");
	mainWindowGui.setBackgroundColor(sf::Color::Green);
	mainWindowGui.setBackgroundImage("./res/textures/bg.png");

	Textbox* text = mainWindowGui.addTextbox("Arial", "Hello world!");
	if (text) {
		text->setFillColor(sf::Color(255, 0, 0));
		text->setPosition(50.0f, 50.0f);
		text->setCharacterSize(20);
	}

	Textbox* otherText = mainWindowGui.addTextbox("Arial", "Good bye");
	if (otherText) {
		text->setFillColor(sf::Color::Red);
	}

	Image* img = mainWindowGui.addImage("./res/textures/logo.png", 0.5f, 0.5f);
	if (img) {
		img->setPosition(window.getSize().x / 2 - img->getSize().x / 2, 50.0f);
	}

	auto button = std::make_unique<DefaultButton>(250, 250, 300, 50);
	
	button->setFillColor(sf::Color(128, 128, 128, 192));
	mainWindowGui.addButton(std::move(button));

	auto button2 = std::make_unique<DefaultButton>(250, 350, 300, 50);

	button2->setFillColor(sf::Color(128, 128, 128, 192));
	mainWindowGui.addButton(std::move(button2));


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			mainWindowGui.captureEvent(event);
		}


		mainWindowGui.run(sf::Time::Zero);
		window.display();
	}

	return 0;
}