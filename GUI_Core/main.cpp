#include "Gui.h"
#include "Image.h"
#include "TextLabel.h"
#include "VerticalLayout.h"
#include "HorizontalLayout.h"
#include "CenterLayout.h"
#include "Container.h"


#include <SFML/System.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	
	Gui gui(window);
	gui.setBackgroundImage("./res/textures/bg.png");
	gui.setCursor("./res/cursors/Cursor_Goth_Cursor.png");


	auto main = gui.addElem<CenterLayout>(gui.getSize().x, gui.getSize().y);
	main->setPadding(25.0f);

	auto label3 = main->addElem<Image>("./res/textures/bg.png", 300, 300);

	auto label2 = main->addElem<Image>("./res/textures/bg.png", 200, 200);

	auto label1 = main->addElem<Image>("./res/textures/bg.png", 100, 100);

	auto label4 = main->addElem<TextLabel>("./res/fonts/arial.ttf", "Test3", 30);
	label4->setColor(sf::Color::Black);

	main->align();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		gui.draw();

		window.display();
	}

	return 0;
}