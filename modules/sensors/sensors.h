#ifndef SENSORS_H
#define SENSORS_H

#include <iostream>
#include <vector>
#include <string>
#include "../temp.h"

// Base Sensor class
class Sensor
{
protected:
    int range;
    Position p;
public:
    // constructor
    Sensor(int range);

    virtual std::vector<ReadData> sensorreading(Position p, std::string direction, std::vector<std::vector<WorldObject *>>& world) = 0;
    
    virtual ~Sensor() {} 
};

// Derived Sensor classes
//Lidar class
class Lidar : public Sensor
{
public:
    Lidar();
    std::vector<ReadData> sensorreading(Position p, std::string direction, std::vector<std::vector<WorldObject *>>& world) override;
};

// Radar class
class Radar : public Sensor
{
public:
    Radar();
    std::vector<ReadData> sensorreading(Position p, std::string direction, std::vector<std::vector<WorldObject *>>& world) override;
};

// Camera class
class Camera : public Sensor
{
public:
    Camera();
    std::vector<ReadData> sensorreading(Position p, std::string direction, std::vector<std::vector<WorldObject *>>& world) override;
};

#endif