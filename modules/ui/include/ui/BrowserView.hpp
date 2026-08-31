#pragma once
#include "ui/Node.hpp"
#include "ui/View.hpp"

namespace Nova::UI {
class BrowserViewNode : public Node {
public:
  explicit BrowserViewNode(Style style = {}) : Node(std::move(style)) {}
  void Layout(const Rect &bounds) override { m_bounds = bounds; }
  void Render(Display *display, ::Window window) const override;
};

inline View BrowserView(Style style = {}) {
  return View(std::make_shared<BrowserViewNode>(std::move(style)));
}
} // namespace Nova::UI
