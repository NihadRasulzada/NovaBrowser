#pragma once

#include "ui/Core/Node.hpp"
#include "ui/Core/View.hpp"

namespace Nova::UI {
class TabBarNode : public Node {
public:
  explicit TabBarNode(Style style = {}) : Node(std::move(style)) {}
  void Layout(const Rect &bounds) override { m_bounds = bounds; }
  void Render(Display *display, ::Window window) const override;
};

inline View TabBar(Style style = {}) {
  return View(std::make_shared<TabBarNode>(std::move(style)));
}
} // namespace Nova::UI
