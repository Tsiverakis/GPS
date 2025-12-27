#ifndef SENSORS
#define SENSORS
#include <iostream>
#include <vector>
#include "temp.h"

struct ReadData{
    std::string type;
    int distance;
    Position p;
    std::string objectid;
    double confidence;
    int speed;
    std::string direction;
    std:: string signtext;
    std::string trafficlightp;

};

class Sensor
{
protected:
    int range;
    Position p;
public:
    // constructor
    Sensor(int range);

    virtual std::vector<ReadData> sensorreading() = 0;
};

class Lidar : public Sensor
{
public:
    //constructor
    Lidar();

    std::vector<ReadData> sensorreading(Position p);

};

class Radar : public Sensor{
    public:

    Radar();

    std::vector<ReadData> sensorreading(Position p, std::string direction);

};

class Camera : public Sensor{
    public:

    Camera();

    std::vector<ReadData> sensorreading(Position p,std::string direction);

};

#endif