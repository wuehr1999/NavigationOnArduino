#include "NavPoint.h"
#include <Arduino.h>
NavPoint::NavPoint()
{
    NavPoint(0, 0);
}

NavPoint::NavPoint(float latitude, float longitude)
{
    this->latitude=latitude;
    this->longitude=longitude;
}

NavPoint::~NavPoint(){}

float NavPoint::getLatitude() const
{
    return latitude;
}

void NavPoint::setLatitude(float latitude)
{
    this->latitude=latitude;
}

float NavPoint::getLongitude() const
{
    return longitude;
}

void NavPoint::setLongitude(float longitude)
{
    this->longitude=longitude;
}

float NavPoint::calculateDistance(NavPoint point)
{
    float la1=latitude; float lo1=longitude;
    float la2=point.getLatitude(); float lo2=point.getLongitude();
    float latitude1R = (la1*M_PI)/180.0;
    float longitude1R = (lo1*M_PI)/180.0;
    float latitude2R = (la2*M_PI)/180.0;
    float longitude2R = (lo2*M_PI)/180.0;
    float dlat = (latitude2R - latitude1R);
    float dlong = (longitude2R - longitude1R);
    float a = sin(dlat/2.0) * sin(dlat/2.0) +
            cos(latitude1R) * cos(latitude2R) *
            sin(dlong/2.0) * sin(dlong/2.0);

    return 6371000.0 * 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

}

float NavPoint::calculateBearing(NavPoint point)
{
    float la1=latitude; float lo1=longitude;
    float la2=point.getLatitude(); float lo2=point.getLongitude();
    float latitude1R = (la1*M_PI)/180.0;
    float longitude1R = (lo1*M_PI)/180.0;
    float latitude2R = (la2*M_PI)/180.0;
    float longitude2R = (lo2*M_PI)/180.0;
    float y = sin(longitude2R-longitude1R) * cos(latitude2R);
    float x = cos(latitude1R)*sin(latitude2R) -
            sin(latitude1R)*cos(latitude2R)*cos(longitude2R-longitude1R);
  
    float bearing = atan2(y, x)/ M_PI * 180.0;
    while(bearing < -180.0)
    {
	bearing += 360.0;
    }
    while(bearing > 180.0)
    {
  	bearing -= 360.0;
    }

    return bearing;
}

float NavPoint::calculateDistanceFromTrack(NavPoint trackpoint1, NavPoint trackpoint2)
{
	float dist = trackpoint1.calculateDistance(*this) / 6371000.0;

	float bearing1 = (trackpoint1.calculateBearing(*this) + 180) * M_PI / 180.0;

	float bearing2 = (trackpoint1.calculateBearing(trackpoint2) + 180) * M_PI / 180.0;

	float dxt = asin(sin(dist) * sin(bearing1 - bearing2));

	float dat = dxt;

	
	return dat * 6371000.0;
}

float NavPoint::calculateDeltaAngle(float courseHeading, NavPoint destinationPoint)
{
	if(courseHeading > 180)
    	{
        	courseHeading = 180;
    	}
    	else if(courseHeading < -180)
    	{
        	courseHeading = -180;
    	}

	float destinationBearing = calculateBearing(destinationPoint);

	float deltaAngle = destinationBearing - courseHeading;

	if(deltaAngle > 180)
   	{
        	deltaAngle -= 360;
    	}
    	else if(deltaAngle < -180)
    	{
        	deltaAngle += 360;
    	}
	
	return deltaAngle;
}

void NavPoint::xyPixelsFromStartPoint(NavPoint startPoint, int *x, int *y, float metersPerPixel)
{
    float distance = startPoint.calculateDistance(NavPoint(latitude, longitude));
    float bearing = startPoint.calculateBearing(NavPoint(latitude, longitude)) - 90.0;

    *x = (int)(cos(bearing * M_PI / 180.0) * distance / metersPerPixel);
    *y = (int)(sin(bearing * M_PI / 180.0) * distance / metersPerPixel);
}
