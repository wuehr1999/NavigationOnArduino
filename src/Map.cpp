#include "Map.h"

Map::Map(){}

void Map::begin(bool log)
{
  this->log = log;
  flushWaypoints();
  flushWays();
  String logMessage = "Setting up *.osm based map with up to " + String(MAP_WAYPOINTS_MAX, DEC) + " points and up to " + String(MAP_WAYS_MAX, DEC) + " ways containg a maximum of " + String(MAP_WAYLENGTH_MAX, DEC) + "waypoints...";
  if(log)
  {
    Serial.println("**********************************************************************************************************************************");
    Serial.println(logMessage);
  }
}

void Map::begin()
{
  begin(true);
}

void Map::parse(const char *osmString)
{
  errors = 0;
  String entry = "";
  int index = 0;
  int len = strlen(osmString);

  flushWaypoints();
  flushWays();
  
  while(index < len)
  {
    while(osmString[index] != '<' && index < len)
    {
      index ++;
    }
    while(osmString[index] != '>' && index < len)
    {
      entry += osmString[index];
      index ++;
    }
    entry += ">";
    //Serial.println(entry);
    int fieldNo = 0;
    String fields[10];

    for(int i = 0; i < entry.length(); i++)
    {
      if(entry[i] == ' ' || entry[i] == '<' || entry[i] == '>')
      {
        //Serial.println(fields[fieldNo]);
        fieldNo ++;
        fields[fieldNo] = "";
      }
      else
      {
        fields[fieldNo] += entry[i];
      }
    }
    entry = "";
    
    if(fields[1].compareTo("node") == 0)
    {
      int found = 0;
      int id;
      float latitude, longitude;
      for(int i = 2; i < 10; i++)
      {
        String currentField = fields[i];
        int fieldIndex = 0;
        String key = "";
        String value = "";
        while(currentField[fieldIndex] != '=' && fieldIndex < currentField.length()) 
        {
          key += currentField[fieldIndex];
          fieldIndex++;
        }
        fieldIndex++;
        while(fieldIndex < currentField.length())
        {
          value += currentField[fieldIndex];
          fieldIndex++;
        }
        value = value.substring(1, value.length() - 1);
        
        if(key.compareTo("id") == 0)
        {
          id = value.toInt();
          if(id < 0)
          {
            id = -id;
          }
          found ++;
        }
        else if(key.compareTo("lat") == 0)
        {
          latitude = value.toFloat();
          found ++;
        }
        else if(key.compareTo("lon") == 0)
        {
          longitude = value.toFloat();
          found ++;
        }
        if(found == 3)
        {
          //Serial.println("found node");
          addWaypoint(id, NavPoint(latitude, longitude));
          break;
        }
      }
    }
    else if(fields[1].compareTo("way") == 0)
    {
      //Serial.println("way found");
      addWay();
    }
    else if(fields[1].compareTo("nd") == 0)
    {
      bool found = false;
      int id = -1;

      for(int i = 2; i < 10; i++)
      {
        String currentField = fields[i];
        int fieldIndex = 0;
        String key = "";
        String value = "";
        while(currentField[fieldIndex] != '=' && fieldIndex < currentField.length()) 
        {
          key += currentField[fieldIndex];
          fieldIndex++;
        }
        fieldIndex++;
        while(fieldIndex < currentField.length())
        {
          value += currentField[fieldIndex];
          fieldIndex++;
        }
        value = value.substring(1, value.length() - 1);
        
        if(key.compareTo("ref") == 0)
        {
          id = value.toInt();
          if(id < 0)
          {
            id = -id;
          }
	  //Serial.println(id);
          found = true;
        }      
        if(found)
        {
          addPointToWay(id);
          break;
        }
      }
    }
  }

  parseLog = "Parsed osm file with " + String(errors, DEC) + " errors....\n" + 
             String(numberOfWaypoints, DEC) + " of " + String(MAP_WAYPOINTS_MAX) + " available waypoints were used...\n" + 
	     String(numberOfWays, DEC) + " of " + String(MAP_WAYS_MAX) + " available ways were used...\n";
  if(log)
  {
    Serial.println("");
    Serial.println(parseLog);
    Serial.println("Distribution of waypoints in ways (Maximum of " + String(MAP_WAYLENGTH_MAX, DEC) + " points per way:");
    for(int i = 0; i < numberOfWays; i++)
    {
      Serial.println("Way " + String(i, DEC) + ": "+ String(wayLengths[i], DEC));
    }
    Serial.println("**********************************************************************************************************************************");
  }
}

String Map::getParseLog()
{
  return parseLog;
}

bool Map::addWaypoint(int id, NavPoint point)
{
  bool idExists = false;
  bool success = false;
  String logMessage = "Trying to add waypoint with id " + String(id, DEC) + "...\n";
  for(int i = 0; i < numberOfWaypoints; i ++)
  {
    if(waypointIDs[i] == id)
    {
      idExists = true;
      break;
    }
  }
  if(!idExists)
  {
    if(numberOfWaypoints >= MAP_WAYPOINTS_MAX)
    {
      numberOfWaypoints = MAP_WAYPOINTS_MAX;
      logMessage += "ERROR: No more space for waypoints...\n";
    }
    else
    {
      numberOfWaypoints++;
      waypoints[numberOfWaypoints - 1] = point;
      waypointIDs[numberOfWaypoints - 1] = id;
      logMessage += "SUCCESS: Added waypoint number " + String(numberOfWaypoints, DEC) + " with id " + id + "...\n";
      success = true;
    }
  }
  else
  {
    logMessage = "WARNING: Waypoint with id "+ String(id, DEC) + " already exists...\n";
  }

  if(log)
  {
    Serial.println("");
    Serial.print(logMessage);
  }
  return success;
}

bool Map::addWaypoint(NavPoint point)
{
  int id = 0;
  for(int i = 0; i < numberOfWaypoints; i++)
  {
    if(id <= waypointIDs[i])
    {
      id = waypointIDs[i] + 1;
    }
  }
  return addWaypoint(id, point);
}

void Map::flushWaypoints()
{
  numberOfWaypoints = 0;
  for(int i = 0; i < MAP_WAYPOINTS_MAX; i++)
  {
    waypointIDs[i] = 0;
  }
  if(log)
  {
    Serial.println("");
    Serial.println("Flushing waypoints...");
  }
}

bool Map::addWay()
{
  String logMessage = "Trying to add way...\n";
  bool success = false;
  if(numberOfWays >= MAP_WAYS_MAX)
  {
    numberOfWays = MAP_WAYS_MAX;
    logMessage += "ERROR: No more space for ways...\n";
  }
  else
  {
    numberOfWays ++;
    logMessage += "SUCCESS: Added way number " + String(numberOfWays) + "...\n";
  }
  success = true;

  if(log)
  {
    Serial.println("");
    Serial.print(logMessage);
  }
  return success;
}

bool Map::addPointToWay(int id)
{
  bool success = false;
  String logMessage = "Trying to add waypoint with id " + String(id, DEC) + " to way number " + String(numberOfWays, DEC) + "...\n";
  if(numberOfWays <= 0)
  {
    logMessage += "ERROR: Currently no way added...\n";
  }
  else
  {
    int currentPoint = wayLengths[numberOfWays - 1];
    currentPoint ++;
    {
      if(currentPoint >= MAP_WAYLENGTH_MAX)
      {
        logMessage += "ERROR: No more space for waypoints in this way...\n";
      }
      else
      {
        wayLengths[numberOfWays -1] = currentPoint;
        for(int i = 0; i < numberOfWaypoints; i++)
        {
          if(waypointIDs[i] == id)
          {
            ways[numberOfWays - 1][currentPoint - 1] = i;
            logMessage += "SUCCESS: Added waypoint with id " + String(id, DEC) + " and index " + String(i, DEC) + " to way number " + String(numberOfWays, DEC) + " at position " + String(currentPoint, DEC) + "...\n";
            logMessage += "Coordinates: " + String(waypoints[i].getLatitude(), 7) + ", " + String(waypoints[i].getLongitude(), 7) + "...\n";
            success = true;
            break;
          }
        }
        if(!success)
        {
          logMessage += "ERROR: Waypoint with id " + String(id, DEC) + " could not be found...\n";
        }
      }
    }
  }

  if(log)
  {
    Serial.println("");
    Serial.print(logMessage);
  }
  return success;
}

void Map::flushWays()
{
  numberOfWays = 0;
  for(int i = 0; i < MAP_WAYS_MAX; i++)
  {
    wayLengths[i] = 0;
  }
  if(log)
  {
    Serial.println("");
    Serial.println("Flushing ways...");
  }
}

int Map::getNumberOfWaypoints()
{
  return numberOfWaypoints;  
}

NavPoint Map::getWaypoint(int waypointIndex)
{
  NavPoint waypoint;
  if(waypointIndex < numberOfWaypoints)
  {
    waypoint = waypoints[waypointIndex];
  }
  return waypoint;
}

int Map::getNumberOfWays()
{
  return numberOfWays;
}

int Map::getNumberOfPointsInWay(int index)
{
  int points = -1;
  if(index < numberOfWays)
  {
    points = wayLengths[index];
  }
  return points;
}

NavPoint Map::getWaypointFromWay(int wayIndex, int waypointIndex)
{
  NavPoint waypoint;
  if(wayIndex < numberOfWays && waypointIndex < wayLengths[wayIndex])
  {
    waypoint = waypoints[ways[wayIndex][waypointIndex]];
  }
  return waypoint;
}
