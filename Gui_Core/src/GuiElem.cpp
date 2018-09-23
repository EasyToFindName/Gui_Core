#include "GuiElem.h"
#include "Container.h"

GuiElem::GuiElem(Container* parent) : m_parent(parent) {}

ResourceCacher* GuiElem::resources() {
  if (m_parent != nullptr)
    return m_parent->resources();
  else
    return nullptr;
}

Container* GuiElem::parent() { return m_parent; }