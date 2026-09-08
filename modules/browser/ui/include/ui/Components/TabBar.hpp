#pragma once

#include "Tab.hpp"
#include "ui/Components/Button.hpp"
#include "ui/Components/Icon.hpp"
#include "ui/Components/Text.hpp"
#include "ui/Layout/Row.hpp"

namespace Browser {

inline Nova::UI::View TabBar() {
  using namespace Nova::UI;

  return Row({Tab("Github"), Tab("Linkedin")});
}

} // namespace Browser
