#include <iostream>
#include "../temp.h"
#include <string>



// It is a stationary vehicle at Position x,y
class StationaryVehicle : public WorldObject
{
public:
    // constructor
    StationaryVehicle(int x, int y, std::string ID, std::string glyph);

    // destructor
    ~StationaryVehicle();
};

// It is a traffic sign with an ID and a Position x,y
class TrafficSign : public WorldObject
{
private:
    std::string signtext; // type of sign
public:
    // constructor
    TrafficSign(int x, int y, std::string signID, std::string ID, std::string glyph);


    // destructor
    ~TrafficSign();

    std::string get_text(); // returns the type of the sign
};

// It is a traffic light with a color(state) and a Position x,y
class TrafficLight : public WorldObject
{
private:
    std::string state; // holds the color of the traffic light

public:
    // constructor
    TrafficLight(int x, int y, std::string state, std::string ID, std::string glyph);


    // destructor
    ~TrafficLight();


    std::string get_State(); // returns the color of the traffic light

    void set_State(std::string color);
};
