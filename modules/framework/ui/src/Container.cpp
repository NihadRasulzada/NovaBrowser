#include "ui/Layout/Container.hpp"

namespace Nova::UI {
void LinearContainer::Layout(const Rect &bounds) {
  m_bounds = bounds;
  const bool horizontal = m_axis == Axis::Horizontal;
  const int available = horizontal ? bounds.width : bounds.height;
  const int spacing = m_style.spacing.value_or(0);
  const int total_spacing =
      m_children.empty() ? 0
                         : spacing * (static_cast<int>(m_children.size()) - 1);

  int fixed_total = 0;
  int flex_total = 0;
  for (const auto &child : m_children) {
    const Style &s = child->GetStyle();
    const bool fixed = horizontal ? s.width.has_value() : s.height.has_value();
    if (fixed) {
      fixed_total += horizontal ? *s.width : *s.height;
    } else {
      flex_total += s.flex.value_or(1);
    }
  }

  const int flexible_space = available - fixed_total - total_spacing;
  int cursor = horizontal ? bounds.x : bounds.y;

  for (const auto &child : m_children) {
    const Style &s = child->GetStyle();
    const bool fixed = horizontal ? s.width.has_value() : s.height.has_value();

    int main_size = 0;
    if (fixed) {
      main_size = horizontal ? *s.width : *s.height;
    } else if (flex_total > 0) {
      main_size = flexible_space * s.flex.value_or(1) / flex_total;
    }

    const int cross_size = horizontal ? s.height.value_or(bounds.height)
                                      : s.width.value_or(bounds.width);

    Rect child_bounds = horizontal
                            ? Rect{cursor, bounds.y, main_size, cross_size}
                            : Rect{bounds.x, cursor, cross_size, main_size};

    child->Layout(child_bounds);
    cursor += main_size + spacing;
  }
}

void LinearContainer::Render(Display *display, ::Window window, GC gc) const {
  for (const auto &child : m_children) {
    child->Render(display, window, gc);
  }
}

bool LinearContainer::MouseButtonDown(int x, int y) {
  for (const auto &child : m_children) {
    if (child->GetBounds().Contains(x, y) && child->MouseButtonDown(x, y)) {
      return true;
    }
  }
  return false;
}

} // namespace Nova::UI
