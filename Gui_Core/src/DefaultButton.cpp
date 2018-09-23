#include "DefaultButton.h"
#include <iostream>

DefaultButton::DefaultButton(Container* parent)
    : GuiActiveElem(parent), m_region(parent), m_text(nullptr) {
  m_region.setFillColor(sf::Color(60, 60, 60, 192));
}

DefaultButton::DefaultButton(Container* parent, float width, float height)
    : GuiActiveElem(parent), m_region(parent, width, height), m_text(nullptr) {
  m_region.setFillColor(sf::Color(60, 60, 60, 192));
}

bool DefaultButton::isPointInside(float x, float y) {
  sf::FloatRect bounds(m_region.getPosition(), m_region.getSize());
  return bounds.contains(x, y);
}

void DefaultButton::setFillColor(const sf::Color& s) {
  m_region.setFillColor(s);
}

void DefaultButton::setText(const std::string& fontPath,
                            const std::string& text, const sf::Color& c,
                            int fontSize) {
  if (m_text == nullptr) {
    m_text = m_region.addElem<TextLabel>(fontPath);

    if (m_text == nullptr)
      return; // Creating text label failed
  }

  m_text->setText(text);
  m_text->setColor(c);
  m_text->setCharacterSize(fontSize);
}

sf::Vector2f DefaultButton::getSize() const { return m_region.getSize(); }

sf::Vector2f DefaultButton::getPosition() const {
  return m_region.getPosition();
}

void DefaultButton::setSize(float width, float height) {
  m_region.setSize(width, height);
}

void DefaultButton::setPosition(float x, float y) {
  m_region.setPosition(x, y);
}

void DefaultButton::onMouseMoved(int x, int y) {
  std::cout << "onMouseMoved(" << x << ", " << y << ")\n";
}

void DefaultButton::onMouseOver() {
  std::cout << "onMouseOver()\n";
  m_region.setFillColor(sf::Color(30, 30, 30, 228));
}

void DefaultButton::onMouseOut() {
  std::cout << "onMouseOut()\n";
  m_region.setFillColor(sf::Color(60, 60, 60, 192));
}

void DefaultButton::onPressed(sf::Mouse::Button b, int x, int y) {
  std::cout << "onPressed()\n";
  m_region.setFillColor(sf::Color(192, 192, 192, 255));
  if (m_text != nullptr)
    m_text->setColor(sf::Color::Black);
}

void DefaultButton::onReleased(sf::Mouse::Button b, int x, int y) {
  std::cout << "onReleased()\n";
  m_region.setFillColor(sf::Color(30, 30, 30, 228));
  if (m_text != nullptr)
    m_text->setColor(sf::Color::White);
}

void DefaultButton::draw(sf::RenderTarget& target,
                         sf::RenderStates states) const {
  target.draw(m_region);
}
