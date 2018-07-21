#include "Gui.h"
//#include <algorithm>



Gui::Gui(sf::RenderWindow& win)
	:Container(nullptr), m_window(win), m_selectedActiveItem(nullptr)
{
	setSize(win.getSize().x, win.getSize().y);
	setPosition(0.0f, 0.0f);
}

ResourceCacher* Gui::resources() {
	return &m_resourceCache;
}

void Gui::draw() {
	m_window.draw(*this);
}

bool Gui::setCursor(const std::string& filePath, int maxSizeX, int maxSizeY) {
	try {
		m_cursor = std::make_unique<Image>(this, filePath);
		
		auto cursorSize = m_cursor->getSize();

		float scaleX = 1.0f;
		float scaleY = 1.0f;

		if (cursorSize.x > maxSizeX) {
			scaleX = maxSizeX / cursorSize.x;
		}

		if (cursorSize.y > maxSizeY) {
			scaleY = maxSizeY / cursorSize.y;
		}

		m_cursor->setScale(scaleX, scaleY);
		m_window.setMouseCursorVisible(false);
		return true;
	}
	catch (...) {
		return false;
	}
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	Container::draw(target, states);
	
	if (m_cursor != nullptr) {
		auto pos = sf::Mouse::getPosition(m_window);
		m_cursor->setPosition(float(pos.x), float(pos.y));
		m_window.draw(*m_cursor);
	}
}

void Gui::onElemRemoved(GuiElem* el) {
	if (el == m_selectedActiveItem) {
		m_selectedActiveItem = nullptr;
	}
}

void Gui::run(sf::Time dt) {
	sf::Event e;
	while (m_window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			m_window.close();

		captureEvent(e);
	}

	this->draw();
	m_window.display();
}

void Gui::captureEvent(sf::Event e) {
	if (e.type == sf::Event::MouseMoved) {
		GuiActiveElem* temp = selectActiveElem(e.mouseMove.x, e.mouseMove.y);

		if (temp != m_selectedActiveItem) {
			if (m_selectedActiveItem != nullptr) {
				m_selectedActiveItem->onMouseOut();
				m_selectedActiveItem->triggerEvent(GuiActiveElem::MOUSE_OUT);
			}

			m_selectedActiveItem = temp;

			if (m_selectedActiveItem != nullptr) {
				m_selectedActiveItem->onMouseOver();
				m_selectedActiveItem->triggerEvent(GuiActiveElem::MOUSE_OVER);
			}
		}
		else if (temp != nullptr) {
			temp->onMouseMoved(e.mouseMove.x, e.mouseMove.y);
			temp->triggerEvent(GuiActiveElem::MOUSE_MOVED);
		}
	}

	else if (e.type == sf::Event::MouseButtonPressed) {
		if (m_selectedActiveItem != nullptr) {
			m_selectedActiveItem->onPressed(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
			m_selectedActiveItem->triggerEvent(GuiActiveElem::PRESSED);
		}

	}

	else if (e.type == sf::Event::MouseButtonReleased) {
		if (m_selectedActiveItem != nullptr) {
			m_selectedActiveItem->onReleased(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
			m_selectedActiveItem->triggerEvent(GuiActiveElem::RELEASED);
		}
	}
}