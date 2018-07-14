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
	gui.setCursor("./res/cursors/Cursor.png", 32, 32);

	auto main = gui.addElem<VerticalLayout>(gui.getSize().x, gui.getSize().y);
	main->setPadding(25.0f);
	main->setOffset(30.0f);
	
	auto button = main->addElem<DefaultButton>(200.0f, 70.0f);
	button->setText(FONT_ARIAL, "Add button");

	button->addListener(GuiActiveElem::PRESSED, [main]() {
		auto* useless = main->addElem<DefaultButton>(200.0f, 70.0f);
		useless->setText(FONT_ARIAL, "Click to remove");

		useless->addListener(GuiActiveElem::MOUSE_OVER, [useless]() {
			useless->setText(FONT_ARIAL, "Don't kill me pls!");
		});

		useless->addListener(GuiActiveElem::MOUSE_OUT, [useless]() {
			useless->setText(FONT_ARIAL, "Click to remove");
		});

		useless->addListener(GuiActiveElem::PRESSED, [main, useless]() {
			main->removeElem(useless);
		});
	});


	while (window.isOpen()) {
		gui.run(sf::Time::Zero);
	}

	return 0;
}