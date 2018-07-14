#include "Container.h"
#include <iostream>

GuiActiveElem* Container::selectedActiveElem = nullptr;

Container::Container(GuiElem* parent) : GuiElem(parent) {
	m_region.setFillColor(sf::Color::Transparent);
}

Container::Container(GuiElem* parent, float width, float height) : Container(parent) {
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

void Container::onElemAdded(GuiElem* el) {
	auto pos = this->getPosition();
	el->setPosition(pos.x, pos.y);
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
	for (auto& container : m_containers) {
		childActiveElem = container->selectActiveElem(x, y);
		if (childActiveElem != nullptr) return childActiveElem;
	}

	return nullptr;
}

void Container::captureEvent(sf::Event e) {
	if (e.type == sf::Event::MouseMoved) {
		GuiActiveElem* temp = selectActiveElem(e.mouseMove.x, e.mouseMove.y);

		if (temp != selectedActiveElem) {
			if (selectedActiveElem != nullptr) {
				selectedActiveElem->onMouseOut();
				selectedActiveElem->triggerEvent(GuiActiveElem::MOUSE_OUT);
			}

			selectedActiveElem = temp;
			
			if (selectedActiveElem != nullptr) {
				selectedActiveElem->onMouseOver();
				selectedActiveElem->triggerEvent(GuiActiveElem::MOUSE_OVER);
			}
		}
		else if (temp != nullptr) {
			temp->onMouseMoved(e.mouseMove.x, e.mouseMove.y);
			temp->triggerEvent(GuiActiveElem::MOUSE_MOVED);
		}
	}

	else if (e.type == sf::Event::MouseButtonPressed) {
		if (selectedActiveElem != nullptr) {
			selectedActiveElem->onPressed(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
			selectedActiveElem->triggerEvent(GuiActiveElem::PRESSED);
		}

	}

	else if (e.type == sf::Event::MouseButtonReleased) {
		if (selectedActiveElem != nullptr) {
			selectedActiveElem->onReleased(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
			selectedActiveElem->triggerEvent(GuiActiveElem::RELEASED);
		}
	}
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