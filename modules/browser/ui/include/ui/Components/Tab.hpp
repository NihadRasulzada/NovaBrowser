#pragma once

#include "ui/Components/Button.hpp"
#include "ui/Components/Icon.hpp"
#include "ui/Components/Text.hpp"
#include "ui/Layout/Row.hpp"

#include <string>

namespace Browser {

inline Nova::UI::View Tab(std::string text) {
  using namespace Nova::UI;

  return Row({Text(text, TextProps{.style{.height = 16}}),
              Icon(IconType::Reload, Style{.height = 16})});
}

} // namespace Browser
