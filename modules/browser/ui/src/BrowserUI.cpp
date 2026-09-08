#include "ui/BrowserUI.hpp"
#include "ui/Components/NavigationBar.hpp"
#include "ui/Components/Text.hpp"
#include "ui/Layout/Column.hpp"

using namespace Nova::UI;

namespace Browser {

BrowserUI::BrowserUI() { m_root = Build(); }

View BrowserUI::Build() {
  return Column({
      NavigationBar(),
      Text("Salam"),
      // BrowserView()
  });
}
void BrowserUI::Resize(int width, int height) {
  m_width = width;
  m_height = height;
  m_root->Layout(Rect{0, 0, width, height});
}

void BrowserUI::Render(Display *display, ::Window window) {
  m_root->Render(display, window);
}

} // namespace Browser
