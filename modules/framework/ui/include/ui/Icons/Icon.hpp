#pragma once

#include "ui/Core/Node.hpp"
#include "ui/Core/View.hpp"
#include "ui/Icons/IconType.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <memory>
#include <vector>

namespace Nova::UI {

struct Point {
  double x;
  double y;
};

struct Segment {
  Point a;
  Point b;
};

class IconNode : public Node {
public:
  explicit IconNode(IconType type, Style style = {})
      : Node(std::move(style)), m_type(type) {}

  void Layout(const Rect &bounds) override { m_bounds = bounds; }

  void Render(Display *display, ::Window window) const override;

private:
  void AddLine(std::vector<Segment> &segments, Point a, Point b);
  Point Transform(Point p, double x, double y, double size);
  void Draw(Display *display, Drawable drawable, GC gc, int x, int y, int size,
            unsigned long color);
  IconType m_type;
};

inline View Icon(IconType type, Style style = {}) {
  return View(std::make_shared<IconNode>(type, std::move(style)));
}

} // namespace Nova::UI
