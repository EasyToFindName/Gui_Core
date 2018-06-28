#pragma once

#include "Textbox.h"
#include "Image.h"
#include "DefaultButton.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <memory>
#include <unordered_map>
#include <vector>


class Gui {
public:
	Gui(sf::RenderWindow& window);
	void run(sf::Time dt);
	void captureEvent(sf::Event e);
	// -- load functions store resources until Gui destruction --

	//registers font in gui. label is a font-label used to create textbox with specified font
	//returns true if font file was successfully read
	//otherwise returns false
	bool loadFont(const std::string& label, const std::string& font_file_path);
	
	//registers cursor in gui. label is a cursor-label used in setCursor() function
	//returns true if cursor_file_path file was successfully read
	//otherwise returns false
	bool loadCursor(const std::string& label, const std::string& cursor_file_path);

	// -- set/reset allow to configure global parameters in gui

	//if cursor label was found replaces default windows cursor with specified and returns true
	//otherwise returns false
	//scales cursor to fit maxSizeX and maxSizeY
	bool setCursor(const std::string& cursor_label, int maxSizeX = 32, int maxSizeY = 32);

	//sets back default OS cursor
	void resetCursor();

	void setBackgroundColor(const sf::Color& color);
	
	//sets background color to black
	void resetBackgroundColor();

	//if image was successfully read returns true
	//otherwise returns false
	//scales image to fit fullscreen
	bool setBackgroundImage(const std::string& filePath);

	//removes image from background
	void resetBackgroundImage();

	// -- add/remove functions allow to free created resource --

	//if specified font label is registered
	//creates textbox and returns it's pointer
	//otherwise returns nullptr
	Textbox* addTextbox(const std::string& fontLabel, const std::string& contents="");

	//removes created earlier textbox
	//sets ptr to nullptr
	void removeTextbox(Textbox* ptr);
	
	//if image was successfully read returns ptr to new added image
	//otherwise returns nullptr
	Image* addImage(const std::string& filePath);

	//scales added image to sizeX, sizeY 
	Image* addImage(const std::string& filePath, unsigned sizeX, unsigned sizeY);

	//scales added image by scaleX, scaleY
	Image* addImage(const std::string& filePath, float scaleX, float scaleY);

	void removeImage(Image* ptr);

	//maybe should be implemented as template method
	//to return ptr of concrete button type.
	void addButton(std::unique_ptr<IButton>&& button);
private:
	sf::RenderWindow& m_window;
	
	std::unique_ptr<sf::Sprite> m_customCursor;
	std::unique_ptr<Image> m_backgroundImage;
	sf::Color m_backgroundColor;

	std::unordered_map<std::string, sf::Font> m_fonts;
	std::unordered_map<std::string, sf::Texture> m_cursors;

	//TODO:
	//Add a common base class and merge vectors in one
	std::vector<std::unique_ptr<Textbox>> m_textboxes;
	std::vector<std::unique_ptr<Image>> m_images;
	std::vector<std::unique_ptr<IButton>> m_buttons;
};

