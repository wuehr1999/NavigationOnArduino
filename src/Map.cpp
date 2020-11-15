#include "Map.h"

Map::Map() {}

void Map::begin(bool log) {
  this->log = log;

  String logMessage = "Setting up *.osm based map with up to " +
                      String(MAP_WAYPOINTS_MAX, DEC) + " points and up to " +
                      String(MAP_POINTSINWAY_MAX, DEC) +
                      " references in ways...";
  if (log) {
    Serial.println(
        "**********************************************************************"
        "************************************************************");
    Serial.println(logMessage);
  }
  parseLog = "";
  routeLog = "";
}

void Map::begin() { begin(true); }

void Map::parse(const char *osmString) {

  int len = strlen(osmString);

  int currentWayLength = 0;

  errors = 0;
  warnings = 0;

  for (int iter = 0; iter < 2; iter++) {

    if (iter == 1) {
      free(waypointIDs);
      free(waypoints);
      free(wayLengths);
      waypointIDs = (uint16_t *)malloc(numberOfWaypoints * sizeof(uint16_t));
      waypoints = (NavPoint *)malloc(numberOfWaypoints * sizeof(NavPoint));
      wayLengths = (uint16_t *)malloc(numberOfWays * sizeof(uint16_t));
      pointsInWay = currentWayLength;
      if (pointsInWay > MAP_POINTSINWAY_MAX) {
        pointsInWay = MAP_POINTSINWAY_MAX;
      }
      wayArray = (uint16_t *)malloc(pointsInWay * sizeof(uint16_t));
      flushWaypoints();
      flushWays();
    }

    errors = 0;
    String entry = "";
    int index = 0;

    numberOfWaypoints = 0;
    numberOfWays = 0;
    currentWayLength = 0;

    while (index < len) {
      while (osmString[index] != '<' && index < len) {
        index++;
      }
      while (osmString[index] != '>' && index < len) {
        entry += osmString[index];
        index++;
      }
      entry += ">";
      // Serial.println(entry);
      int fieldNo = 0;
      String fields[10];

      for (int i = 0; i < entry.length(); i++) {
        if (entry[i] == ' ' || entry[i] == '<' || entry[i] == '>') {
          // Serial.println(fields[fieldNo]);
          fieldNo++;
          fields[fieldNo] = "";
        } else {
          fields[fieldNo] += entry[i];
        }
      }
      entry = "";

      if (fields[1].compareTo("node") == 0) {
        int found = 0;
        int id;
        float latitude, longitude;
        for (int i = 2; i < 10; i++) {
          String currentField = fields[i];
          int fieldIndex = 0;
          String key = "";
          String value = "";
          while (currentField[fieldIndex] != '=' &&
                 fieldIndex < currentField.length()) {
            key += currentField[fieldIndex];
            fieldIndex++;
          }
          fieldIndex++;
          while (fieldIndex < currentField.length()) {
            value += currentField[fieldIndex];
            fieldIndex++;
          }
          value = value.substring(1, value.length() - 1);

          if (key.compareTo("id") == 0) {
            id = value.toInt();
            if (id < 0) {
              id = -id;
            }
            found++;
          } else if (key.compareTo("lat") == 0) {
            latitude = value.toFloat();
            found++;
          } else if (key.compareTo("lon") == 0) {
            longitude = value.toFloat();
            found++;
          }
          if (found == 3) {
            // Serial.println("found node");
            if (iter == 0) {
              numberOfWaypoints++;
            } else if (iter == 1) {
              addWaypoint((uint16_t)id, NavPoint(latitude, longitude));
            }
            break;
          }
        }
      } else if (fields[1].compareTo("way") == 0) {
        // Serial.println("way found");
        if (iter == 0) {
          numberOfWays++;
        } else if (iter == 1) {
          addWay();
        }
      } else if (fields[1].compareTo("nd") == 0) {
        bool found = false;
        int id = -1;

        for (int i = 2; i < 10; i++) {
          String currentField = fields[i];
          int fieldIndex = 0;
          String key = "";
          String value = "";
          while (currentField[fieldIndex] != '=' &&
                 fieldIndex < currentField.length()) {
            key += currentField[fieldIndex];
            fieldIndex++;
          }
          fieldIndex++;
          while (fieldIndex < currentField.length()) {
            value += currentField[fieldIndex];
            fieldIndex++;
          }
          value = value.substring(1, value.length() - 1);

          if (key.compareTo("ref") == 0) {
            id = value.toInt();
            if (id < 0) {
              id = -id;
            }
            // Serial.println(id);
            found = true;
          }
          if (found) {
            if (iter == 0) {
              currentWayLength++;
            } else if (iter == 1) {
              addPointToWay((uint16_t)id);
            }
            break;
          }
        }
      }
    }
  }

  parseLog = "Parsed osm file with " + String(errors, DEC) + " errors and " +
             String(warnings, DEC) + " warnings...\n" +
             String(numberOfWaypoints, DEC) + " of " +
             String(MAP_WAYPOINTS_MAX) + " available waypoints were used (" +
             String(numberOfWaypoints * (sizeof(NavPoint) + 2), DEC) +
             " Byte)...\n" + String(pointsInWay, DEC) + " of " +
             String(MAP_POINTSINWAY_MAX) +
             " available references to points in ways were used (" +
             String(pointsInWay * 2, DEC) + " Byte)...\n";
  if (log) {
    Serial.println("");
    Serial.println(parseLog);
    Serial.println("Distribution of waypoints in ways:");
    for (int i = 0; i < numberOfWays; i++) {
      Serial.println("Way " + String(i, DEC) + ": " +
                     String(wayLengths[i], DEC));
    }
    Serial.println(
        "**********************************************************************"
        "************************************************************");
  }
}

String Map::getParseLog() { return parseLog; }

bool Map::addWaypoint(uint16_t id, NavPoint point) {
  bool idExists = false;
  bool success = false;
  String logMessage =
      "Trying to add waypoint with id " + String(id, DEC) + "...\n";
  for (int i = 0; i < numberOfWaypoints; i++) {
    if (waypointIDs[i] == id) {
      idExists = true;
      break;
    }
  }
  if (!idExists) {
    if (numberOfWaypoints >= MAP_WAYPOINTS_MAX) {
      numberOfWaypoints = MAP_WAYPOINTS_MAX;
      logMessage += "ERROR: No more space for waypoints...\n";
      errors++;
    } else {
      numberOfWaypoints++;
      waypoints[numberOfWaypoints - 1] = point;
      waypointIDs[numberOfWaypoints - 1] = id;
      logMessage += "SUCCESS: Added waypoint number " +
                    String(numberOfWaypoints, DEC) + " with id " + id + "...\n";
      success = true;
    }
  } else {
    logMessage =
        "WARNING: Waypoint with id " + String(id, DEC) + " already exists...\n";
    warnings++;
  }

  if (log) {
    Serial.println("");
    Serial.print(logMessage);
  }
  return success;
}

bool Map::addWaypoint(NavPoint point) {
  int id = 0;
  for (int i = 0; i < numberOfWaypoints; i++) {
    if (id <= waypointIDs[i]) {
      id = waypointIDs[i] + 1;
    }
  }
  return addWaypoint((uint16_t)id, point);
}

void Map::flushWaypoints() {
  for (int i = 0; i < numberOfWaypoints; i++) {
    waypointIDs[i] = 0;
  }
  numberOfWaypoints = 0;
  if (log) {
    Serial.println("");
    Serial.println("Flushing waypoints...");
  }
}

bool Map::addWay() {
  String logMessage = "Trying to add way...\n";

  numberOfWays++;
  logMessage += "SUCCESS: Added way number " + String(numberOfWays) + "...\n";

  if (log) {
    Serial.println("");
    Serial.print(logMessage);
  }
  return true;
}

bool Map::addPointToWay(uint16_t id) {
  bool success = false;
  String logMessage = "Trying to add waypoint with id " + String(id, DEC) +
                      " to way number " + String(numberOfWays, DEC) + "...\n";
  if (numberOfWays <= 0) {
    logMessage += "ERROR: Currently no way added...\n";
    errors++;
  } else {
    int currentPoint = wayLengths[numberOfWays - 1];
    currentPoint++;
    {
      wayLengths[numberOfWays - 1] = currentPoint;
      for (int i = 0; i < numberOfWaypoints; i++) {
        if (waypointIDs[i] == id) {
          // ways[numberOfWays - 1][currentPoint - 1] = i;
          bool set = setWayArray(numberOfWays - 1, currentPoint - 1, i);
          if (set) {
            logMessage += "SUCCESS: Added waypoint with id " + String(id, DEC) +
                          " and index " + String(i, DEC) + " to way number " +
                          String(numberOfWays, DEC) + " at position " +
                          String(currentPoint, DEC) + "...\n";
            logMessage +=
                "Coordinates: " + String(waypoints[i].getLatitude(), 7) + ", " +
                String(waypoints[i].getLongitude(), 7) + "...\n";
          } else {
            logMessage += "Waypoint references overfilled...\n";
          }
          success = true;
          break;
        }
      }
      if (!success) {
        logMessage += "ERROR: Waypoint with id " + String(id, DEC) +
                      " could not be found...\n";
        errors++;
      }
    }
  }

  if (log) {
    Serial.println("");
    Serial.print(logMessage);
  }
  return success;
}

void Map::flushWays() {
  for (int i = 0; i < numberOfWays; i++) {
    wayLengths[i] = 0;
  }
  numberOfWays = 0;
  if (log) {
    Serial.println("");
    Serial.println("Flushing ways...");
  }
}

uint16_t Map::getNumberOfWaypoints() { return numberOfWaypoints; }

NavPoint Map::getWaypoint(uint16_t waypointIndex) {
  NavPoint waypoint;
  if (waypointIndex < numberOfWaypoints) {
    waypoint = waypoints[waypointIndex];
  }
  return waypoint;
}

uint16_t Map::getNumberOfWays() { return numberOfWays; }

uint16_t Map::getNumberOfPointsInWay(uint16_t index) {
  int points = 0;
  if (index < numberOfWays) {
    points = wayLengths[index];
  }
  return points;
}

NavPoint Map::getWaypointFromWay(uint16_t wayIndex, uint16_t waypointIndex) {
  NavPoint waypoint;
  if (wayIndex < numberOfWays && waypointIndex < wayLengths[wayIndex]) {
    waypoint = waypoints[getWayArray(
        wayIndex, waypointIndex)]; // waypoints[ways[wayIndex][waypointIndex]];
  }
  return waypoint;
}

uint16_t Map::getClosestWaypoint(NavPoint point) {
  float distanceMin = -1.0;
  uint16_t pointIndex = 0;

  for (int p = 0; p < numberOfWaypoints; p++) {
    float distance = point.calculateDistance(waypoints[p]);

    if (distanceMin < 0.0 || distance < distanceMin) {
      distanceMin = distance;
      pointIndex = p;
    }
  }

  return pointIndex;
}

ArduinoQueue<uint16_t> Map::getAdjacents(uint16_t pointIndex) {
  ArduinoQueue<uint16_t> adjacents(numberOfWaypoints);
  for (int w = 0; w < numberOfWays; w++) {
    for (int p = 0; p < wayLengths[w]; p++) {
      if (pointIndex == getWayArray(w, p) /*ways[w][p]*/) {
        if (p > 0) {
          adjacents.enqueue(getWayArray(w, p - 1) /*ways[w][p - 1]*/);
        }
        if (p < wayLengths[w]) {
          adjacents.enqueue(getWayArray(w, p + 1) /*ways[w][p + 1]*/);
        }
      }
    }
  }

  return adjacents;
}

ArduinoQueue<uint16_t> Map::planRoute(NavPoint start, NavPoint destination) {
  int startIndex = getClosestWaypoint(destination);
  int destIndex = getClosestWaypoint(start);

  // float distances[numberOfWaypoints];
  // int previousVertexes[numberOfWaypoints];
  // bool visitedVertexes[numberOfWaypoints];
  float *distances = new float[numberOfWaypoints];
  int *previousVertexes = new int[numberOfWaypoints];
  bool *visitedVertexes = new bool[numberOfWaypoints];

  float endless = -1.0;
  int unknown = -1;
  routeLog = "Routeplanner...\n";
  routeLog += "Start: " + start.toString() +
              ", Destination: " + destination.toString() + "\n";
  routeLog += "Snapping to: (" + waypoints[startIndex].toString() + "), (" +
              waypoints[destIndex].toString() + ")\n";
  routeLog += "startIndex: " + String(startIndex, DEC) +
              ", destIndex: " + String(destIndex, DEC) + "\n";
  if (log) {
    Serial.println(
        "**********************************************************************"
        "************************************************************");
    Serial.println("Initializing routeplanner...");
    Serial.print(routeLog);
  }

  for (int i = 0; i < numberOfWaypoints; i++) {
    distances[i] = endless;
    previousVertexes[i] = unknown;
    visitedVertexes[i] = false;
  }

  distances[startIndex] = 0.0;
  previousVertexes[startIndex] = startIndex;

  int nextIndex = unknown;
  bool allVisited = false;

  while (!allVisited) {
    float minDist = endless;

    for (int i = 0; i < numberOfWaypoints; i++) {
      if ((minDist == endless ||
           (distances[i] < minDist && distances[i] != endless)) &&
          !visitedVertexes[i]) {
        minDist = distances[i];
        nextIndex = i;
      }
    }
    visitedVertexes[nextIndex] = true;

    ArduinoQueue<uint16_t> adjacents = getAdjacents(nextIndex);

    while (!adjacents.isEmpty()) {
      int adj = adjacents.dequeue();
      float distance = distances[nextIndex] +
                       waypoints[nextIndex].calculateDistance(waypoints[adj]);

      if (distance < distances[adj] || distances[adj] == endless) {
        distances[adj] = distance;
        previousVertexes[adj] = nextIndex;
      }
    }

    allVisited = true;

    for (int i = 0; i < numberOfWaypoints; i++) {
      if (!visitedVertexes[i]) {
        allVisited = false;
        break;
      }
    }
  }

  int point = destIndex;

  ArduinoQueue<uint16_t> route(numberOfWaypoints);
  int iteration = 0;
  String wayLog = "";
  while (1) {
    iteration++;
    wayLog = "index: " + String(point, DEC) + ", (" +
             String(waypoints[point].getLatitude(), 7) + "," +
             String(waypoints[point].getLongitude(), 7) + ")\n";
    routeLog += wayLog;
    if (log) {
      Serial.print(wayLog);
    }
    if (previousVertexes[point] == unknown || iteration > numberOfWaypoints) {
      wayLog = "ERROR: faulty way...\n";
      errors++;
      routeLog += wayLog;
      if (log) {
        Serial.print(wayLog);
      }
      break;
    } else if (previousVertexes[point] == startIndex) {
      wayLog = "SUCCESS: way complete...\n";
      routeLog += wayLog;
      if (log) {
        Serial.print(wayLog);
      }
      route.enqueue(startIndex);
      break;
    } else {
      point = previousVertexes[point];
      route.enqueue(point);
    }
  }

  delete[] distances;
  delete[] previousVertexes;
  delete[] visitedVertexes;

  Serial.println(
      "************************************************************************"
      "**********************************************************");

  return route;
}

String Map::getRouteLog() { return routeLog; }

bool Map::setWayArray(uint16_t wayNr, uint16_t index, uint16_t pointId) {
  uint16_t offset = index;
  for (uint16_t i = 0; i < wayNr; i++) {
    offset += wayLengths[i];
  }
  if (offset < pointsInWay) {
    wayArray[offset] = pointId;
    return true;
  } else {
    return false;
  }
}

uint16_t Map::getWayArray(uint16_t wayNr, uint16_t index) {
  uint16_t offset = index;
  for (uint16_t i = 0; i < wayNr; i++) {
    offset += wayLengths[i];
  }

  return wayArray[offset];
}

NavPoint Map::getUpperLeftCorner() {
  float latMax = 0.0;
  float lonMin = 181.0;

  for (int i = 0; i < numberOfWaypoints; i++) {
    NavPoint current = waypoints[i];
    if (current.getLatitude() > latMax) {
      latMax = current.getLatitude();
    }
    if (current.getLongitude() < lonMin) {
      lonMin = current.getLongitude();
    }
  }

  return NavPoint(latMax, lonMin);
}

NavPoint Map::getLowerRightCorner() {
  float latMin = 91.0;
  float lonMax = 0.0;

  for (int i = 0; i < numberOfWaypoints; i++) {
    NavPoint current = waypoints[i];
    if (current.getLatitude() < latMin) {
      latMin = current.getLatitude();
    }
    if (current.getLongitude() > lonMax) {
      lonMax = current.getLongitude();
    }
  }

  return NavPoint(latMin, lonMax);
}
