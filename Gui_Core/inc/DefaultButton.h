#pragma once

#include "CenterLayout.h"
#include "GuiActiveElem.h"
#include "TextLabel.h"

#include <SFML/Graphics.hpp>

#include <memory>

class DefaultButton : public GuiActiveElem {
public:
  explicit DefaultButton(Container* parent);
  DefaultButton(Container* parent, float width, float height);

  void setFillColor(const sf::Color& s);
  void setText(const std::string& fontPath, const std::string& text,
               const sf::Color& c = sf::Color::White, int fontSize = 16);

public: // GuiElem
  virtual sf::Vector2f getSize() const override;
  virtual sf::Vector2f getPosition() const override;

  virtual void setSize(float width, float height) override;
  virtual void setPosition(float x, float y) override;

  void draw(sf::RenderTarget& draw, sf::RenderStates states) const override;

public: // GuiActiveElem
  bool isPointInside(float x, float y) override;
  void onMouseMoved(int x, int y) override;
  void onMouseOver() override;
  void onMouseOut() override;
  void onPressed(sf::Mouse::Button b, int x, int y) override;
  void onReleased(sf::Mouse::Button b, int x, int y) override;

private:
  CenterLayout m_region;
  TextLabel* m_text;
};