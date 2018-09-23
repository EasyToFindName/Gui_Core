#include "VerticalLayout.h"

VerticalLayout::VerticalLayout(Container* parent)
    : Layout(parent), m_offset(0.0f) {}

VerticalLayout::VerticalLayout(Container* parent, float width, float height)
    : Layout(parent, width, height), m_offset(0.0f) {}

void VerticalLayout::setOffset(float offset) {
  if (offset > 0.0f) {
    m_offset = offset;
  }
}

void VerticalLayout::align() {
  sf::Vector2f effectivePos = getEffectivePos();
  sf::Vector2f effectiveSize = getEffectiveSize();

  auto current = m_layoutElements.begin();
  resizeElem(*current, effectiveSize);

  auto size = (*current)->getSize();
  (*current)->setPosition(effectivePos.x +
                              (effectiveSize.x / 2.0f - size.x / 2.0f),
                          effectivePos.y);

  auto prevSize = (*current)->getSize();
  auto prevPos = (*current)->getPosition();

  for (++current; current != m_layoutElements.end(); ++current) {
    resizeElem(*current, effectiveSize);
    size = (*current)->getSize();

    (*current)->setPosition(effectivePos.x +
                                (effectiveSize.x / 2.0f - size.x / 2.0f),
                            prevPos.y + prevSize.y + m_offset);

    prevSize = (*current)->getSize();
    prevPos = (*current)->getPosition();
  }
}
