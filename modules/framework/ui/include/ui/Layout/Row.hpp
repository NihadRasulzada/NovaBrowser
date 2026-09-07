#pragma once

#include "ui/Layout/Container.hpp"
#include <memory>
#include <utility>
#include <vector>

namespace Nova::UI {
inline View Row(std::vector<View> children, Style style = {}) {
  return View(std::make_shared<LinearContainer>(
      Axis::Horizontal, std::move(children), std::move(style)));
}
} // namespace Nova::UI
