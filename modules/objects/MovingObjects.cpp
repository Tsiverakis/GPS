#include "MovingObjects.h"
#include <iostream>

using namespace std;

// Εξωτερική μεταβλητή για έλεγχο ορίων
extern int max_value;

MovingVehicle::MovingVehicle(Position pos, string type, string ID, string glyph, int speed, string direction)
    : WorldObject(type, ID, glyph, pos.getX(), pos.getY()), speed(speed), direction(direction) 
{
    // Μήνυμα βάσει προδιαγραφών
    cout << "[+VEHICLE: " << ID << "] Created at (" << p.getX() << "," << p.getY() 
         << "), heading " << direction << " at " << speed << " units/tick" << endl;
}

MovingVehicle::~MovingVehicle() {
    cout << "[-SENSOR: " << ID << "] Sensor destroyed - No further data from me!" << endl;
}

int MovingVehicle::getSpeed() const { return speed; }
string MovingVehicle::getDirection() const { return direction; }

void MovingVehicle::move() {
    // Η κίνηση πρέπει να λαμβάνει υπόψη την ταχύτητα (speed)
    if (direction == "UP") p.setY(p.getY() + speed);
    else if (direction == "DOWN") p.setY(p.getY() - speed);
    else if (direction == "LEFT") p.setX(p.getX() - speed);
    else if (direction == "RIGHT") p.setX(p.getX() + speed);
}

// MovingCar Implementation
MovingCar::MovingCar(Position pos, string ID, int speed, string direction)
    : MovingVehicle(pos, "MovingObject", ID, "C", speed, direction) {}

MovingCar::~MovingCar() {
    cout << "[-CAR: " << ID << "] Being scrapped..." << endl; // Μήνυμα βάσει προδιαγραφών
}

// Bike Implementation
Bike::Bike(Position pos, string ID, int speed, string direction)
    : MovingVehicle(pos, "MovingObject", ID, "B", speed, direction) {}

Bike::~Bike() {
    cout << "[-BIKE: " << ID << "] Being locked away..." << endl; // Μήνυμα βάσει προδιαγραφών
}