#pragma once

#include "GuiElem.h"
#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>

class GuiActiveElem : public GuiElem {
public:
  using Event = enum {
    PRESSED,
    RELEASED,

    MOUSE_OVER,
    MOUSE_OUT,
    MOUSE_MOVED
  };

public:
  GuiActiveElem(Container* parent) : GuiElem(parent) {}

  virtual bool isPointInside(float x, float y) = 0;

  virtual void onMouseMoved(int x, int y) {}
  virtual void onMouseOver() {}
  virtual void onMouseOut() {}

  virtual void onPressed(sf::Mouse::Button b, int x, int y) {}
  virtual void onReleased(sf::Mouse::Button b, int x, int y) {}

public:
  void addListener(Event type, std::function<void(const sf::Event&)> callback);
  void triggerEvent(Event e, const sf::Event& sfEvent);

private:
  struct Subscriber {
    Event event;
    std::function<void(const sf::Event&)> callback;
  };

  std::vector<Subscriber> m_subscribers;
};