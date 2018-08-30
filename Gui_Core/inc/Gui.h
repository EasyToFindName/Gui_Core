#pragma once

#include "Container.h"
#include "ResourceCacher.h"

#include <memory>
#include <vector>

class Gui : public Container {
public:
	Gui(sf::RenderWindow& window);
	void run(sf::Time dt);
	bool setCursor(const std::string& filePath, int maxSizeX = 32, int maxSizeY = 32);
	void draw();

public: //gui events processing
	void captureEvent(sf::Event e);
protected:
	virtual ResourceCacher* resources() override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void onElemRemoved(GuiElem* el) override;
private:
	sf::RenderWindow& m_window;
	ResourceCacher m_resourceCache;

	std::unique_ptr<Image> m_cursor;
	GuiActiveElem* m_selectedActiveItem;
};

