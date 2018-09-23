#pragma once

#include "Layout.h"

class CenterLayout : public Layout {
public:
  explicit CenterLayout(Container* parent);
  CenterLayout(Container* parent, float widht, float height);

public:
  virtual void align() override;
};
