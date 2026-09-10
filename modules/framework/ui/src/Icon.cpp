#include "ui/Icons/Icon.hpp"

#include <X11/Xlib.h>
#include <vector>

namespace Nova::UI {

Point Transform(Point p, double x, double y, double size) {
  const double scale = size / 24.0;

  return {x + p.x * scale, y + p.y * scale};
}

void IconNode::Render(Display *display, ::Window window) const {
  int screen = DefaultScreen(display);
  GC gc = XCreateGC(display, window, 0, nullptr);

  switch (m_type) {
  case IconType::ArrowLeft:
    this->Draw(display, window, gc, 50, 50, 24, BlackPixel(display, screen));
    break;

  case IconType::ArrowRight:

  case IconType::RefreshCCW:
  }
}

void IconNode::Draw(Display *display, Drawable drawable, GC gc, int x, int y,
                    int size, unsigned long color) {

  if (!display || size <= 0)
    return;

  constexpr int SS = 8;

  const int width = size;
  const int height = size;

  const int highWidth = width * SS;
  const int highHeight = height * SS;

  std::vector<float> coverage(highWidth * highHeight, 0.0f);

  auto transform = [&](Point p) {
    const double scale = static_cast<double>(size) / 24.0;

    return Point{p.x * scale * SS, p.y * scale * SS};
  };
}

} // namespace Nova::UI
