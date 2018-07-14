#pragma once

#include "GuiElem.h"
#include "Image.h"
#include "GuiActiveElem.h"

#include <vector>
#include <memory>
#include <type_traits>

class Container : public GuiElem {
public:
	explicit Container(GuiElem* parent);
	Container(GuiElem* parent, float width, float height);
	void setFillColor(const sf::Color& c);
	bool setBackgroundImage(const std::string& filePath);
public: //GuiElem
	virtual sf::Vector2f getSize() const override;
	virtual sf::Vector2f getPosition() const override;

	virtual void setSize(float width, float height) override;
	virtual void setPosition(float x, float y) override;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public: //factory
	//adds new gui elem to Container.
	//Constructor args mustn't contain parent ptr, because the method passes ptr to the current container as a first argument of the constructor.
	//Example: Creation of a class A with a constructor A(GuiElem* parent, int a, int b);
	//auto a = addElem<A>(1,2);
	template<typename GuiElemType, typename... ConstructorArgs>
	GuiElemType* addElem(ConstructorArgs... args);

protected: //container events
	//called after elem was added
	virtual void onElemAdded(GuiElem* el);
public: //gui events processing
	void captureEvent(sf::Event e);
protected:
	GuiActiveElem* selectActiveElem(float x, float y);
	static GuiActiveElem* selectedActiveElem;
private:
	sf::RectangleShape m_region;
	std::unique_ptr<Image> m_background;
	std::vector <std::unique_ptr<Container>> m_containers;
	std::vector<std::unique_ptr<GuiElem>> m_elements;
	std::vector<std::unique_ptr<GuiActiveElem>> m_controls;
};



template<typename GuiElemType, typename... ConstructorArgs>
GuiElemType* Container::addElem(ConstructorArgs... args) {
	try {
		auto newElem = new GuiElemType(this, args...); //can throw		
		GuiElemType* retValue = newElem;
		
		if (std::is_base_of<Container, GuiElemType>::value) {
			Container* ptr = reinterpret_cast<Container*>(newElem);
			m_containers.push_back(std::unique_ptr<Container>(ptr));
		}
		else if (std::is_base_of<GuiActiveElem, GuiElemType>::value) {
			GuiActiveElem* ptr = reinterpret_cast<GuiActiveElem*>(newElem);
			m_controls.push_back(std::unique_ptr<GuiActiveElem>(ptr));
		}
		else {
			m_elements.push_back(std::unique_ptr<GuiElem>(newElem));
		}
		
		onElemAdded(retValue);
		return retValue;
	}
	catch(...) {
		return nullptr;
	}
}
