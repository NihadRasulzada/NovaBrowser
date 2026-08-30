#include "../../modules/url/include/url/UrlLexer.hpp"
#include "linux/Application.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>

using namespace Browser::Url;

int main() {
  Browser::Platform::Linux::Application application;
  return application.Run();
}
