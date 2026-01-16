#ifndef MOVING_OBJECTS_H
#define MOVING_OBJECTS_H

#include "../temp.h"
#include <string>

// Base class for moving objects
class MovingVehicle : public WorldObject {
protected:
    int speed;
    std::string direction;

public:
    MovingVehicle(Position pos, std::string type, std::string ID, std::string glyph, int speed, std::string direction);
    virtual ~MovingVehicle();

    int getSpeed() const;
    std::string getDirection() const;
    
    virtual void move(); // Virtual ώστε να μπορεί να γίνει override αν χρειαστεί
};

// MovingCar class derived from MovingVehicle
class MovingCar : public MovingVehicle {
public:
    MovingCar(Position pos, std::string ID, int speed, std::string direction);
    ~MovingCar();
};

// Bike class derived from MovingVehicle
class Bike : public MovingVehicle {
public:
    Bike(Position pos, std::string ID, int speed, std::string direction);
    ~Bike();
};

#endif