#ifndef CAR
#define CAR
#include "temp.h"
#include "sensorfusionengine/engine.h"
#include "sensors/sensors.h"

class SelfDrivingCar
{
private:
    Position p;
    std::string Direction;
    int speed;
    Lidar lidar;
    Radar radar;
    Camera camera;
    SensorFusionEngine engine;
    Position target;

public:
    // constructor
    SelfDrivingCar(Position p, Position target);
    // destructor
    ~SelfDrivingCar();

    std::vector<ReadData> collectSensorData( std::vector<std::vector<WorldObject *>> &world);

    void makeDecision(std::vector<ReadData> data);

    void executeMovement();

    //returns the position of the car
    Position getPosition() const;

    //returns the direction of the car
    std::string getDirection() const;
};

#endif