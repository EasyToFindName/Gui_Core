#include "CenterLayout.h"

CenterLayout::CenterLayout(Container* parent) : Layout(parent) {}

CenterLayout::CenterLayout(Container* parent, float width, float height)
    : Layout(parent, width, height) {}

void CenterLayout::align() {
  sf::Vector2f effectiveSize = getEffectiveSize();
  sf::Vector2f effectivePos  = getEffectivePos();

  auto center = sf::Vector2f(effectiveSize.x / 2.0f, effectiveSize.y / 2.0f);

  for (auto& i : m_layoutElements) {
    resizeElem(i, effectiveSize);
    i->setPosition(effectivePos.x + (center.x - i->getSize().x / 2.0f),
                   effectivePos.y + (center.y - i->getSize().y / 2.0f));
  }
}