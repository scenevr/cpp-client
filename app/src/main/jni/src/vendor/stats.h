#pragma once

#include <memory>

namespace scenevr {

class Stats {
  public:
    Stats(float reportInterval = 2.5f);
    void update(float deltaTime);
  private:
    int framesSinceReport, fps;
    float reportInterval, currentTime, nextReportTime;
  };
}
