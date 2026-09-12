#pragma once

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
  explicit IconNode(IconType type, Style style = {})
      : Node(std::move(style)), m_type(type) {}

  void Layout(const Rect &bounds) override { m_bounds = bounds; }

  void Render(Display *display, ::Window window) const override;

private:
  IconType m_type;
};

inline View Icon(IconType type, Style style = {}) {
  return View(std::make_shared<IconNode>(type, std::move(style)));
}

} // namespace Nova::UI
