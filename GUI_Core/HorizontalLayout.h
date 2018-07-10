#pragma once

#include "Layout.h"

class HorizontalLayout : public Layout  {
public:
	explicit HorizontalLayout(GuiElem* parent);
	HorizontalLayout(GuiElem* parent, float width, float height);

	void setOffset(float offset);
public:
	virtual void align() override;
private:
	float m_offset;
};

