#pragma once

#include "ui/Components/Button.hpp"
#include "ui/Components/Icon.hpp"
#include "ui/Layout/Row.hpp"

namespace Browser {

inline Nova::UI::View NavigationBar() {
  using namespace Nova::UI;

  return Row({Button(Icon(IconType::Back),
                     ButtonProps{.style = {.width = 36, .height = 32}}),
              Button(Icon(IconType::Forward),
                     ButtonProps{.style = {.width = 36, .height = 32}}),
              Button(Icon(IconType::Reload),
                     ButtonProps{.style = {.width = 36, .height = 32}})},
             Style{.height = 52, .spacing = 8});
}

} // namespace Browser
