# NavigationOnArduino
[![General Formatting Checks](https://github.com/wuehr1999/NavigationOnArduino/workflows/General%20Formatting%20Checks/badge.svg)](https://github.com/wuehr1999/NavigationOnArduino/actions?workflow=General+Formatting+Checks)
[![Spell Check](https://github.com/wuehr1999/NavigationOnArduino/workflows/Spell%20Check/badge.svg)](https://github.com/wuehr1999/NavigationOnArduino/actions?workflow=Spell+Check)

**Manage navigaiton tasks with geodata (latitude and  longitude) and openstreetmap data on an Arduino.**

**See the ![wiki](https://github.com/wuehr1999/NavigationOnArduino/wiki) for complete documentation**

## Features

* distance and bearing calculation between waypoints
* course heading calculation
* offtrack check
* simple and lightweight openstreetmap file parser (.osm)
* management of waypoints in map
* route planning with Dijkstra's algorithm
* helpers for visualisation on graphic displays

![Map on DOGM display](extras/images/display.png)

## Used Libraries

* ArduinoQueue: https://github.com/EinarArnason/ArduinoQueue
* DogGraphicDisplay (only in visualisation examples): https://github.com/generationmake/DogGraphicDisplay
