#pragma once

namespace Nova::UI {
struct Point {
  double x = 0.0;
  double y = 0.0;
};

struct Segment {
  Point a;
  Point b;
};
} // namespace Nova::UI
