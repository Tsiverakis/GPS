#ifndef SENSORS
#define SENSORS
#include <iostream>
#include <vector>
#include "../../temp.h"

class Sensor
{
protected:
    int range;
    Position p;
public:
    // constructor
    Sensor(int range);

    virtual std::vector<ReadData> sensorreading(Position p, std::string direction, std::vector<std::vector<WorldObject *>>& world) = 0;
};

class Lidar : public Sensor
{
public:
    //constructor
    Lidar();

    std::vector<ReadData> sensorreading(Position p, std::string direction, std::vector<std::vector<WorldObject *>>& world);

};

class Radar : public Sensor{
    public:

    Radar();

    std::vector<ReadData> sensorreading(Position p, std::string direction, std::vector<std::vector<WorldObject *>>& world);

};

class Camera : public Sensor{
    public:

    Camera();

    std::vector<ReadData> sensorreading(Position p,std::string direction, std::vector<std::vector<WorldObject *>>& world);

};

#endif