#include <CenterLayout.h>
#include <Container.h>
#include <DefaultButton.h>
#include <DragAndDrop.h>
#include <Gui.h>
#include <HorizontalLayout.h>
#include <Image.h>
#include <TextLabel.h>
#include <VerticalLayout.h>

#include <SFML/System.hpp>
#include <iostream>
#include <stack>

#define FONT_ARIAL "./res/fonts/arial.ttf"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

  Gui gui(window);
  gui.setBackgroundImage("./res/textures/bg.png");
  gui.setCursor("./res/cursors/Cursor.png", 32, 32);

  // header
  auto controlsWrapper =
      gui.addElem<CenterLayout>(gui.getSize().x, gui.getSize().y / 6);
  controlsWrapper->setFillColor(sf::Color(192, 192, 192, 192));

  auto controls = controlsWrapper->addElem<HorizontalLayout>(
      controlsWrapper->getSize().x / 2, controlsWrapper->getSize().y);
  controls->setOffset(24.0f);

  auto createButton = controls->addElem<DefaultButton>(200.0f, 70.0f);
  createButton->setText(FONT_ARIAL, "Create button");

  auto deleteButton = controls->addElem<DefaultButton>(200.0f, 70.0f);
  deleteButton->setText(FONT_ARIAL, "Delete button");

  // main
  std::stack<DefaultButton*> mainButtons;

  auto main = gui.addElem<Container>();
  main->setPosition(gui.getSize().x / 3, gui.getSize().y / 4);

  createButton->addListener(
      GuiActiveElem::PRESSED, [&mainButtons, main](const sf::Event& e) mutable {
        auto draggableButton = main->addElem<DefaultButton>(200.0f, 70.0f);
        DragAndDrop::apply(draggableButton);
        draggableButton->setText(FONT_ARIAL, "Drag me");
        mainButtons.push(draggableButton);
      });

  deleteButton->addListener(GuiActiveElem::PRESSED,
                            [&mainButtons, main](const sf::Event& e) mutable {
                              if (mainButtons.size()) {
                                auto toDelete = mainButtons.top();
                                mainButtons.pop();
                                main->removeElem(toDelete);
                              }
                            });

  while (window.isOpen()) {
    gui.run(sf::Time::Zero);
  }

  return 0;
}