#pragma once

namespace blessings {
  struct MonitorResolution {
    int width;
    int height;

    MonitorResolution(int w, int h) : width(w), height(h) {}
  };

  struct GridPos {
    int x;
    int y;

    GridPos(int X, int Y) : x(X), y(Y) {};
  };
}
