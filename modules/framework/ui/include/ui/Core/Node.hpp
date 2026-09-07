#pragma once

#include <X11/Xlib.h>
#include <utility>

#include "ui/Layout.hpp"
#include "ui/Style.hpp"

namespace Nova::UI {
class Node {
public:
  virtual ~Node() = default;

  const Style &GetStyle() const { return m_style; }
  Rect GetBounds() const { return m_bounds; }

  virtual void Layout(const Rect &bounds) = 0;
  virtual void Render(Display *display, ::Window window) const = 0;

  virtual bool MouseButtonDown(int x, int y) { return false; }

protected:
  explicit Node(Style style) : m_style(std::move(style)) {}

protected:
  Style m_style;
  Rect m_bounds;
};
} // namespace Nova::UI
