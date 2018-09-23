#pragma once

#include "ResourceCacher.h"
#include <SFML/Graphics.hpp>

class Container;
class GuiElem : public sf::Drawable {
public:
  explicit GuiElem(Container* parent);
  virtual ~GuiElem() = default;

  virtual sf::Vector2f getSize() const     = 0;
  virtual sf::Vector2f getPosition() const = 0;

  virtual void setSize(float width, float height) = 0;
  virtual void setPosition(float x, float y)      = 0;

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override = 0;

  virtual ResourceCacher* resources();

  Container* parent();

private:
  Container* m_parent;
};