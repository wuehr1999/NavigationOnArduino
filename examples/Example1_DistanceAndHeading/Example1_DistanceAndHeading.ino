/******************************************************************************
  Calculates distance and bearing between two cartesian points
  Libraries: NavigationOnArduino,
                               ArduinoQueue:
https://github.com/EinarArnason/ArduinoQueue

  Original Creation Date: 13.10.2020
******************************************************************************/

#include <NavPoint.h>

// Set up points
NavPoint p1(48.995796, 12.837936);
NavPoint p2(48.997873, 12.837614);

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
}

void loop() {
  // distance
  float distance = p1.calculateDistance(p2);

  // bearing
  float bearing = p1.calculateBearing(p2);

  Serial.println("Distance in m:");
  Serial.println(distance);
  Serial.println("Bearing in deg:");
  Serial.println(bearing);
  delay(3000);
}
