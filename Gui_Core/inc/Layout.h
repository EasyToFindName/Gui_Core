#pragma once

#include "Container.h"

#include <vector>
class Layout : public Container {
public:
  explicit Layout(Container* parent);
  Layout(Container* parent, float width, float height);

  void setPadding(float all);
  void setPadding(float top_bottom, float right_left);
  void setPadding(float top_bottom, float right, float left);
  void setPadding(float top, float right, float bottom, float left);

public:
  virtual void setPosition(float x, float y) override;
  virtual void setSize(float width, float height) override;

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
  virtual void onElemAdded(GuiElem* el) override;
  virtual void onElemRemoved(GuiElem* el) override;

protected:
  virtual void align() = 0;

protected:
  sf::Vector2f getEffectivePos() const;
  sf::Vector2f getEffectiveSize() const;
  static void resizeElem(GuiElem* el, const sf::Vector2f& effectiveSize);

protected:
  std::vector<GuiElem*> m_layoutElements;

private:
  struct Padding {
    Padding() : top(0.0f), right(0.0f), bottom(0.0f), left(0.0f) {}

    float top;
    float right;
    float bottom;
    float left;
  } m_padding;

  bool m_changed;
};
