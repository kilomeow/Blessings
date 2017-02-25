#pragma once

namespace blessings {
  struct MonitorResolution {
    int width;
    int height;

    MonitorResolution(int w=0, int h=0) : width(w), height(h) {}
  };

  struct GridPos {
    int x;
    int y;

    GridPos(int X=0, int Y=0) : x(X), y(Y) {};
  };
}
