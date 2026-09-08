#pragma once

#include "ui/Core/Node.hpp"
#include "ui/Core/View.hpp"
#include "ui/Icons/IconType.hpp"

#include <memory>

namespace Nova::UI {

class IconNode : public Node {
public:
  explicit IconNode(IconType type, Style style = {})
      : Node(std::move(style)), m_type(type) {}

  void Layout(const Rect &bounds) override { m_bounds = bounds; }

  void Render(Display *display, ::Window window) const override;

private:
  void RenderBack(Display *display, ::Window window) const;
  void RenderForward(Display *display, ::Window window) const;
  void RenderReload(Display *display, ::Window window) const;

private:
  IconType m_type;
};

inline View Icon(IconType type, Style style = {}) {
  return View(std::make_shared<IconNode>(type, std::move(style)));
}

} // namespace Nova::UI
