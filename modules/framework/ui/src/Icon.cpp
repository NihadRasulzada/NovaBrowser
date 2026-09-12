#include "ui/Icons/Icon.hpp"

#include <X11/Xlib.h>
#include <cstddef>
#include <vector>

namespace Nova::UI {

void IconNode::Render(Display *display, ::Window window, GC gc) const {
  Svg svg;
  if (m_type == IconType::RefreshCCW) {
    svg.viewBoxWidth = 24;
    svg.viewBoxHeight = 24;
    svg.strokeWidth = 2;
    svg.color = BlackPixel(display, DefaultScreen(display));

    svg.paths = {"M21 12a9 9 0 0 0-9-9 "
                 "9.75 9.75 0 0 0-6.74 2.74L3 8",

                 "M3 3v5h5",

                 "M3 12a9 9 0 0 0 9 9 "
                 "9.75 9.75 0 0 0 6.74-2.74L21 16",

                 "M16 16h5v5"};
    this->Draw(display, window, gc, m_bounds.x, m_bounds.y, m_size, svg);
  }
}

void IconNode::Draw(Display *display, Drawable drawable, GC gc, int x, int y,
                    int size, const Svg &svg) const {
  if (!display || !svg.paths.size() || size <= 0 || svg.viewBoxWidth <= 0.0 ||
      svg.viewBoxHeight <= 0.0 || svg.strokeWidth < 0.0) {
    return;
  }

  constexpr int SS = 8;

  const int width = size;
  const int height = size;

  const int highWidth = width * SS;
  const int highHeight = height * SS;

  std::vector<float> coverage(
      static_cast<size_t>(highWidth) * static_cast<size_t>(highHeight), 0.0f);
}

} // namespace Nova::UI
