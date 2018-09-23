#include "DragAndDrop.h"

#include <SFML/Graphics.hpp>
#include <memory>

struct Data {
  Data(GuiActiveElem* elem) : elem(elem), captured(false) {}

  GuiActiveElem* elem;
  sf::Vector2i mousePos;
  bool captured;
};

struct OnPressed {
  OnPressed(std::shared_ptr<Data> m_state) : m_state(m_state) {}
  void operator()(const sf::Event& e) {
    m_state->captured = true;
    m_state->mousePos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);
  }

private:
  std::shared_ptr<Data> m_state;
};

struct OnMove {
  OnMove(std::shared_ptr<Data> m_state) : m_state(m_state) {}
  void operator()(const sf::Event& e) {
    if (m_state->captured) {
      auto delta =
          sf::Vector2i(e.mouseMove.x, e.mouseMove.y) - m_state->mousePos;
      auto ElPos = m_state->elem->getPosition();

      m_state->elem->setPosition(ElPos.x + delta.x, ElPos.y + delta.y);

      m_state->mousePos = sf::Vector2i(e.mouseMove.x, e.mouseMove.y);
    }
  }

private:
  std::shared_ptr<Data> m_state;
};

struct OnReleased {
  OnReleased(std::shared_ptr<Data> m_state) : m_state(m_state) {}
  void operator()(const sf::Event& e) { m_state->captured = false; }

private:
  std::shared_ptr<Data> m_state;
};

void DragAndDrop::apply(GuiActiveElem* el) {
  auto state = std::make_shared<Data>(el);

  el->addListener(GuiActiveElem::PRESSED, OnPressed(state));
  el->addListener(GuiActiveElem::MOUSE_MOVED, OnMove(state));
  el->addListener(GuiActiveElem::RELEASED, OnReleased(state));
  el->addListener(GuiActiveElem::MOUSE_OUT, OnReleased(state));
}