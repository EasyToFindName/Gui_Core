#include "Gui.h"
#include "Image.h"
#include "TextLabel.h"
#include "VerticalLayout.h"
#include "HorizontalLayout.h"
#include "CenterLayout.h"
#include "DefaultButton.h"
#include "Container.h"


#include <SFML/System.hpp>
#include <iostream>

#define FONT_ARIAL "./res/fonts/arial.ttf"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	
	Gui gui(window);
	gui.setBackgroundImage("./res/textures/bg.png");
	gui.setCursor("./res/cursors/Cursor_Goth_Cursor.png");

	auto main = gui.addElem<CenterLayout>(gui.getSize().x, gui.getSize().y);
	main->setPadding(25.0f);

	auto button = main->addElem<DefaultButton>(200.0f, 100.0f);
	button->setText(FONT_ARIAL, "Hello?");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			gui.captureEvent(event);
		}

		gui.draw();

		window.display();
	}

	return 0;
}