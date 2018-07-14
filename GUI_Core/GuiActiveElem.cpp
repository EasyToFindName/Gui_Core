#include "GuiActiveElem.h"

void GuiActiveElem::addListener(Event type, std::function<void()> callback) {
	Subscriber s;
	s.event = type;
	s.callback = callback;

	m_subscribers.push_back(std::move(s));
}

void GuiActiveElem::triggerEvent(Event e) {
	for (auto& i : m_subscribers) {
		if (e == i.event) i.callback();
	}
}
