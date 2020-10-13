#ifndef NAVPOINT_H
#define NAVPOINT_H

#include <math.h>

class NavPoint
{
public:
    /*!
    * @brief Initializes navigation point without coordinates
    */
    NavPoint();

    /*!
    * @brief Initializes navigation point with coordinates
    * @param latitude, Latitude as float
    * @param longitude, Longitude as float
    */
    NavPoint(float latitude, float longitude);

    /*!
    * @brief Destructor
    */
    ~NavPoint();

    /*!
    * @brief Getter for Latitude
    * @return Latitude as float
    */
    float getLatitude() const;

    /*!
    * @brief Setter for Latitude
    * @param laittude, Latitude as float
    */
    void setLatitude(float value);

    /*!
    * @brief Getter for Longitude
    * @return Longitude as float
    */
    float getLongitude() const;

    /*!
    * @brief Setter for Longitude
    * @param laittude, Longitude as float
    */
    void setLongitude(float value);

    /*!
    * @brief Calculates distance to second point
    * @param p2, second NavPoint 
    * @retval distance in m
    */
    float calculateDistance(NavPoint point);

    /*!
    * @brief Calculates bearing to second point
    * @param p2, second NavPoint 
    * @retval bearing from -180 deg to 180 deg
    */
    float calculateBearing(NavPoint point);

private:
    float latitude, longitude;

};

#endif

