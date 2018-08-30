#include "Layout.h"

Layout::Layout(Container* parent):Container(parent), m_changed(true) {
	
}

Layout::Layout(Container* parent, float width, float height) : Container(parent, width, height), m_changed(true) {
	
}

void Layout::setPadding(float top, float right, float bottom, float left) {
	m_padding.top = top;
	m_padding.right = right;
	m_padding.bottom = bottom;
	m_padding.left = left;
}

void Layout::setPadding(float top_bottom, float right, float left) {
	setPadding(top_bottom, right, top_bottom, left);
}

void Layout::setPadding(float top_bottom, float right_left) {
	setPadding(top_bottom, right_left, top_bottom, right_left);
}

void Layout::setPadding(float all) {
	setPadding(all, all, all, all);
}

sf::Vector2f Layout::getEffectivePos() const {
	return getPosition() + sf::Vector2f(m_padding.left, m_padding.top);
}

sf::Vector2f Layout::getEffectiveSize() const {
	return getSize() - sf::Vector2f(m_padding.left + m_padding.right, m_padding.top + m_padding.bottom);
}

void Layout::resizeElem(GuiElem* el, const sf::Vector2f& effectiveSize) {
	sf::Vector2f elemSize = el->getSize();

	if (elemSize.x > effectiveSize.x) {
		elemSize.x = effectiveSize.x;
	}
	if (elemSize.y > effectiveSize.y) {
		elemSize.y = effectiveSize.y;
	}

	el->setSize(elemSize.x, elemSize.y);
}

void Layout::setPosition(float x, float y) {
	Container::setPosition(x, y);
	m_changed = true;
}

void Layout::setSize(float x, float y) {
	Container::setSize(x, y);
	m_changed = true;
}

void Layout::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	auto* mut_this = const_cast<Layout*>(this);
	
	if (mut_this->m_changed) {
		mut_this->align();
		mut_this->m_changed = false;
	}

	Container::draw(target, states);
}

void Layout::onElemAdded(GuiElem * el) {
	Container::onElemAdded(el);
	m_layoutElements.push_back(el);
	m_changed = true;
}

void Layout::onElemRemoved(GuiElem* el) {
	m_layoutElements.erase(std::find(m_layoutElements.begin(), m_layoutElements.end(), el));
	m_changed = true;

	Container::onElemRemoved(el);
}
