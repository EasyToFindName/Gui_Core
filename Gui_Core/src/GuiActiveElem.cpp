#include "GuiActiveElem.h"

void GuiActiveElem::addListener(
    Event type, std::function<void(const sf::Event& e)> callback) {
  Subscriber s;
  s.event = type;
  s.callback = callback;

  m_subscribers.push_back(std::move(s));
}

void GuiActiveElem::triggerEvent(Event e, const sf::Event& sfE) {
  for (auto& i : m_subscribers) {
    if (e == i.event)
      i.callback(sfE);
  }
}
