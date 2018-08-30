#include "Container.h"
#include <iostream>

#include <algorithm>

Container::Container(Container* parent) : GuiElem(parent) {
	m_region.setFillColor(sf::Color::Transparent);
}

Container::Container(Container* parent, float width, float height) : Container(parent) {
	this->setSize(width, height);
}

bool Container::setBackgroundImage(const std::string& filePath) {
	try {
		m_background = std::make_unique<Image>(this, filePath, getSize().x, getSize().y);
		m_background->setPosition(getPosition().x, getPosition().y);
		return true;
	}
	catch (...) {
		return false;
	}
}

void Container::setFillColor(const sf::Color& c) {
	m_region.setFillColor(c);
}

sf::Vector2f Container::getSize() const {
	return m_region.getSize();
}

sf::Vector2f Container::getPosition() const {
	return m_region.getPosition();
}


bool Container::removeElem(GuiElem* elem) {
	if (remove(m_elements, elem)
	||  remove(m_controls, elem)
	||  remove(m_containers, elem)) {
		return true;
	}

	for (auto& container : m_containers) {
		if (container->removeElem(elem)) {
			return true;
		}
	}

	return false;
}

void Container::onElemAdded(GuiElem* el) {
	auto pos = this->getPosition();
	el->setPosition(pos.x, pos.y);
}

void Container::onElemRemoved(GuiElem* el) {
	if (parent() != nullptr) {
		parent()->onElemRemoved(el);
	}
}

void Container::setSize(float width, float height) {
	m_region.setSize(sf::Vector2f(width, height));
}

void Container::setPosition(float x, float y) {
	m_region.setPosition(sf::Vector2f(x, y));
}

GuiActiveElem* Container::selectActiveElem(float x, float y) {
	for (auto& el : m_controls) {
		if (el->isPointInside(x, y)) {
			return el.get();
		}
	}

	GuiActiveElem* childActiveElem = nullptr;
	for (auto& container: m_containers) {
		childActiveElem = container->selectActiveElem(x, y);
		if (childActiveElem != nullptr) return childActiveElem;
	}

	return nullptr;
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_region);

	if (m_background) {
		target.draw(*m_background);
	}

	for (auto &i : m_elements) {
		i->draw(target, states);
	}

	for (auto &i : m_controls) {
		i->draw(target, states);
	}

	for (auto &i : m_containers) {
		i->draw(target, states);
	}
}