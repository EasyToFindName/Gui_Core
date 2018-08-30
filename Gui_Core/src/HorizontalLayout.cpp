#include "HorizontalLayout.h"

#include "HorizontalLayout.h"



HorizontalLayout::HorizontalLayout(Container* parent)
	:Layout(parent), m_offset(0.0f) {

}

HorizontalLayout::HorizontalLayout(Container* parent, float width, float height)
	: Layout(parent, width, height), m_offset(0.0f) {

}

void HorizontalLayout::setOffset(float offset) {
	if (offset > 0.0f) {
		m_offset = offset;
	}
}

void HorizontalLayout::align() {
	sf::Vector2f effectivePos = getEffectivePos();
	sf::Vector2f effectiveSize = getEffectiveSize();

	auto current = m_layoutElements.begin();
	//resizeElem(*current, effectiveSize);

	auto size = (*current)->getSize();

	(*current)->setPosition(effectivePos.x,
							effectivePos.y + (effectiveSize.y / 2.0f - size.y / 2.0f));

	auto prevSize = (*current)->getSize();
	auto prevPos = (*current)->getPosition();

	for (++current; current != m_layoutElements.end(); ++current) {
		resizeElem(*current, effectiveSize);
		size = (*current)->getSize();

		(*current)->setPosition(prevPos.x + prevSize.x + m_offset,
								effectivePos.y + (effectiveSize.y / 2.0f - size.y / 2.0f));

		prevSize = (*current)->getSize();
		prevPos = (*current)->getPosition();
	}

}
