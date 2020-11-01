/******************************************************************************
  Calculates distance of point to a track defined by two waypoints to check
  if the vehicle is still on track.
  Libraries: NavigationOnArduino,
			       ArduinoQueue: https://github.com/EinarArnason/ArduinoQueue

  Original Creation Date: 13.10.2020
******************************************************************************/

#include <NavPoint.h>

// Set up points
NavPoint currentPoint1(51.150187, 5.191011);
NavPoint currentPoint2(51.082342, 17.324204);

NavPoint trackpoint1(47.787554, 10.706037);
NavPoint trackpoint2(54.123990, 10.100044);

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
}

void loop() {

  float distance1 =
      currentPoint1.calculateDistanceFromTrack(trackpoint1, trackpoint2);
  float distance2 =
      currentPoint2.calculateDistanceFromTrack(trackpoint1, trackpoint2);

  Serial.println("Distance 1:");
  Serial.println(distance1);

  Serial.println("Distance 2:");
  Serial.println(distance2);

  delay(3000);
}
