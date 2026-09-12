#pragma once

#include <string>
#include <vector>

namespace Nova::UI {
struct Svg {
  double viewBoxWidth = 24.0;
  double viewBoxHeight = 24.0;

  double strokeWidth = 2.0;

  unsigned long color = 0x000000;

  std::vector<std::string> paths;
};
} // namespace Nova::UI
