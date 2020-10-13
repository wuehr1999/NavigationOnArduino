#include "NavPoint.h"

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

    return 6371000* 2 * atan2(sqrt(a), sqrt(1-a));

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
  
  return (atan2(y, x)/(2*M_PI))*360.0;
}

