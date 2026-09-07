#pragma once

#include <optional>

namespace Nova::UI {
struct Style {
  std::optional<int> width;
  std::optional<int> height;
  std::optional<int> flex;
  std::optional<int> spacing;
};
} // namespace Nova::UI
