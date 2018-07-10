#pragma once
#include "Layout.h"

#include <vector>
class VerticalLayout : public Layout {
public:
	explicit VerticalLayout(GuiElem* parent);
	VerticalLayout(GuiElem* parent, float width, float height);
	
	void setOffset(float offset);
public:
	virtual void align() override;
private:
	float m_offset;
};

