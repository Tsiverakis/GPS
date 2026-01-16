#ifndef STATIC_OBJECTS_H
#define STATIC_OBJECTS_H

#include "../temp.h"
#include <string>

// Stationary Vehicle
class StationaryVehicle : public WorldObject {
public:
    StationaryVehicle(int x, int y, std::string ID, std::string glyph);
    ~StationaryVehicle();
};

// Traffic Sign
class TrafficSign : public WorldObject {
private:
    std::string signtext;
public:
    TrafficSign(int x, int y, std::string text, std::string ID, std::string glyph);
    ~TrafficSign();
    std::string get_text() const;
};

// Traffic Light
class TrafficLight : public WorldObject {
private:
    std::string state; // "RED", "GREEN", "YELLOW"
    int timer;
public:
    TrafficLight(int x, int y, std::string initialState, std::string ID, std::string glyph);
    ~TrafficLight();
    std::string get_State() const;
    void update(int currentTick); 
};

#endif