#pragma once
#include "ui/Node.hpp"
#include "ui/View.hpp"
#include <vector>

namespace Nova::UI {

enum class Axis { Horizontal, Vertical };

class LinearContainer : public Node {
public:
  LinearContainer(Axis axis, std::vector<View> children, Style style)
      : Node(std::move(style)), m_axis(axis), m_children(std::move(children)) {}

  void Layout(const Rect &bounds) override;
  void Render(Display *display, ::Window window) const override;
  bool MouseButtonDown(int x, int y) override;

private:
  Axis m_axis;
  std::vector<View> m_children;
};

} // namespace Nova::UI
