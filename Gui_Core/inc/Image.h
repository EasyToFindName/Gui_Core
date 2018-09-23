#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GuiElem.h"

class Image : public GuiElem {
public:
  Image(Container* parent, const std::string& filePath);
  Image(Container* parent, const std::string& filePath, float width,
        float height);
  void setScale(float x, float y);

public: // GuiElem
  sf::Vector2f getSize() const override;
  sf::Vector2f getPosition() const override;

  void setSize(float width, float height) override;
  void setPosition(float x, float y) override;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  sf::Texture* m_texture;
  sf::Sprite m_sprite;
};