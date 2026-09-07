#pragma once
#include "ui/Layout/Container.hpp"

namespace Nova::UI {
inline View Column(std::vector<View> children, Style style = {}) {
  return View(std::make_shared<LinearContainer>(
      Axis::Vertical, std::move(children), std::move(style)));
}
} // namespace Nova::UI
