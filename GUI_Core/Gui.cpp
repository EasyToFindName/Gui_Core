#include "Gui.h"
//#include <algorithm>
//
//#include <iostream>

Gui::Gui(sf::RenderWindow& win)
	:Container(nullptr), m_window(win) 
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

//Gui::Gui(sf::RenderWindow& win)
//	:m_window(win),
//	 m_customCursor(nullptr),
//	 m_backgroundImage(nullptr),
//	 m_backgroundColor(sf::Color::Black)
//{
//
//}
//
//
//void Gui::run(sf::Time dt) {
//	m_window.clear(m_backgroundColor);
//
//	if (m_backgroundImage != nullptr) {
//		m_window.draw(*m_backgroundImage);
//	}
//
//	for (auto& i : m_textboxes) {
//		m_window.draw(*i);
//	}
//
//	for (auto& i : m_images) {
//		m_window.draw(*i);
//	}
//
//	for (auto& i : m_buttons) {
//		m_window.draw(*i);
//	}
//
//	if (m_customCursor != nullptr) {
//		m_customCursor->setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));
//		m_window.draw(*m_customCursor);
//	}
//}
//
//void Gui::captureEvent(sf::Event e) {
//	static IButton* selected = nullptr;
//	
//	if (e.type == sf::Event::MouseMoved) {
//		IButton* temp = nullptr;
//
//		for (auto& b : m_buttons) {
//			if (b->isPointInside(e.mouseMove.x, e.mouseMove.y)) {
//				temp = b.get();
//				temp->onMouseMoved(e.mouseMove.x, e.mouseMove.y);
//				break;
//			}
//		}
//
//		if (temp != selected) {
//			if (selected != nullptr) selected->onMouseOut();
//			selected = temp;
//			if (selected != nullptr) selected->onMouseOver();
//		}
//	}
//
//	else if (e.type == sf::Event::MouseButtonPressed) {
//		if (selected != nullptr) selected->onPressed(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
//	}
//
//	else if (e.type == sf::Event::MouseButtonReleased) {
//		if (selected != nullptr) selected->onReleased(e.mouseButton.button, e.mouseMove.x, e.mouseMove.y);
//	}
//
//}
//
//bool Gui::loadFont(const std::string& label, const std::string& font_file_path) {
//	sf::Font font;
//	
//	if (font.loadFromFile(font_file_path)) {
//		m_fonts[label] = font;
//		return true;
//	}
//
//	return false;
//}
//
//
//bool Gui::loadCursor(const std::string& label, const std::string& cursor_file_path) {
//	sf::Texture cursor;
//
//	if (cursor.loadFromFile(cursor_file_path)) {
//		m_cursors[label] = cursor;
//		return true;
//	}
//
//	return false;
//}
//
//
//Textbox* Gui::addTextbox(const std::string& fontLabel, const std::string& contents) {
//	auto fontIterator = m_fonts.find(fontLabel);
//	
//	if (fontIterator != m_fonts.end()) {
//		auto newTextbox = std::make_unique<Textbox>(fontIterator->second);
//		newTextbox->setString(contents);
//		m_textboxes.push_back(std::move(newTextbox));
//		return m_textboxes.back().get();
//	}
//
//	return nullptr;
//}
//
//
//void Gui::removeTextbox(Textbox* ptr) {
//	if (ptr != nullptr) {
//		m_textboxes.erase(
//			std::remove_if(m_textboxes.begin(), 
//						   m_textboxes.end(),
//						   [ptr](std::unique_ptr<Textbox>& current) {
//						       if (ptr == current.get()) return true;
//						       return false;
//						    }),
//			m_textboxes.end()
//		);
//		ptr = nullptr;
//	}
//}
//
//
//void Gui::setBackgroundColor(const sf::Color& color) {
//	m_backgroundColor = color;
//}
//
//void Gui::resetBackgroundColor() {
//	m_backgroundColor = sf::Color::Black;
//}
//
//bool Gui::setCursor(const std::string& cursor_label, int maxSizeX, int maxSizeY) {
//	auto cursorIterator = m_cursors.find(cursor_label);
//	
//	if (cursorIterator != m_cursors.end()) {
//		m_customCursor = std::make_unique<sf::Sprite>(cursorIterator->second);
//
//		//calc scale coef
//		auto spriteRect = m_customCursor->getLocalBounds();
//		float scaleX = 1.0f;
//		float scaleY = 1.0f;
//
//		if (spriteRect.width > maxSizeX) {
//			scaleX = maxSizeX / spriteRect.width;
//		}
//
//		if (spriteRect.height > maxSizeY) {
//			scaleY = maxSizeY / spriteRect.height;
//		}
//
//		m_customCursor->setScale(scaleX, scaleY);
//		m_window.setMouseCursorVisible(false);
//		return true;
//	}
//
//	return false;
//}
//
//void Gui::resetCursor() {
//	m_customCursor.reset();
//	m_window.setMouseCursorVisible(true);
//}
//
//bool Gui::setBackgroundImage(const std::string& filePath) {
//	auto bg = std::make_unique<sf::Texture>();
//	
//	if (!bg->loadFromFile(filePath)) {
//		return false;
//	}
//
//	auto winSize = m_window.getSize();
//	auto textSize = bg->getSize();
//
//	m_backgroundImage = std::make_unique<Image>(std::move(bg));
//
//	float scaleX = float(winSize.x) / float(textSize.x);
//	float scaleY = float(winSize.y) / float(textSize.y);
//
//	m_backgroundImage->setScale(scaleX, scaleY);
//
//	return true;
//}
//
//
//void Gui::resetBackgroundImage() {
//	m_backgroundImage.reset();
//}
//
//void Gui::removeImage(Image* ptr) {
//	if (ptr != nullptr) {
//		m_images.erase(
//			std::remove_if(m_images.begin(),
//				m_images.end(),
//				[ptr](std::unique_ptr<Image>& current) {
//			if (ptr == current.get()) return true;
//			return false;
//		}),
//			m_images.end()
//		);
//		ptr = nullptr;
//	}
//}
//
//void Gui::addButton(std::unique_ptr<IButton>&& button) {
//	m_buttons.push_back(std::move(button));
//}
//
