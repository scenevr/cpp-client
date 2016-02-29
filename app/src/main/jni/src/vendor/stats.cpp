#include "stats.h"
#include "three/console.h"
#include <sstream>

using namespace three;

namespace scenevr {

Stats::Stats(float reportInterval) :
    framesSinceReport( 0 ),
    fps( 60 ),
    reportInterval( reportInterval ),
    currentTime( 0 ),
    nextReportTime( currentTime + reportInterval ) {
}

void Stats::update(float deltaTime) {
  currentTime += deltaTime;

  ++framesSinceReport;

  if ( currentTime > nextReportTime ) {
    nextReportTime = currentTime + reportInterval;
    fps = framesSinceReport;
    framesSinceReport = 0;
  }

  std::stringstream ss;
  ss << "FPS: " << fps;

  if ( framesSinceReport == 0 ) {
    console().log(ss.str().c_str());
  }
}

}
