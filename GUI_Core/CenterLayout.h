#pragma once

#include "Layout.h"

class CenterLayout : public Layout {
public:
	explicit CenterLayout(GuiElem* parent);
	CenterLayout(GuiElem* parent, float widht, float height);
public: 
	virtual void align() override;


};

