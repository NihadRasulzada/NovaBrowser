#pragma once

#include "Svg.hpp"
#include "ui/Core/Node.hpp"
#include "ui/Core/View.hpp"
#include "ui/Icons/IconType.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <memory>
#include <vector>

namespace Nova::UI {

class IconNode : public Node {
public:
  explicit IconNode(IconType type, int size, Style style = {})
      : Node(std::move(style)), m_type(type), m_size(size) {}

  void Layout(const Rect &bounds) override { m_bounds = bounds; }

  void Render(Display *display, ::Window window, GC gc) const override;

private:
  void Draw(Display *display, Drawable drawable, GC gc, int x, int y, int size,
            const Svg &svg) const;

private:
  int m_size;
  IconType m_type;
};

inline View Icon(IconType type, int size = 24, Style style = {}) {
  return View(std::make_shared<IconNode>(type, size, std::move(style)));
}

} // namespace Nova::UI
