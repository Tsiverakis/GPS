#include <iostream>
#include "temp.h"

using namespace std;

// It is a stationary vehicle at Position x,y
class StationaryVehicle : WorldObject
{
public:
    // constructor
    StationaryVehicle(int x, int y, string ID, string glyph)
        : WorldObject(type, ID, glyph, x, y)
    {
        cout << "Stationary vehicle created at: " << p.getX() << "," << p.getY() << endl;
    }

    // destructor
    ~StationaryVehicle()
    {
        cout << "Stationary vehicle destroyed at: " << p.getX() << "," << p.getY() << endl;
    }
};

// It is a traffic sign with an ID and a Position x,y
class TrafficSign : WorldObject
{
private:
    string signtext; // type of sign
public:
    // constructor
    TrafficSign(int x, int y, string signID, string ID, string glyph)
    : WorldObject(type, ID,glyph,x,y)
    {
        this->signtext = signID;
        cout << "Sign " << get_text() << " created at: " << p.getX() << "," << p.getY() << endl;
    }

    // destructor
    ~TrafficSign()
    {
        cout << "Sign " << get_text() << " destroyed at: " << p.getX() << "," << p.getY() << endl;
    }

    string get_text() { return signtext; } // returns the type of the sign
};

// It is a traffic light with a color(state) and a Position x,y
class TrafficLight :WorldObject
{
private:
    string state; // holds the color of the traffic light

public:
    // constructor
    TrafficLight(int x, int y, string state, string ID, string glyph)
    :WorldObject(type, ID,glyph,x,y)
    {
        this->state = state;
        cout << "Traffic light " << get_State() << " created at: " << p.getX() << "," << p.getY() << endl;
    }

    // destructor
    ~TrafficLight()
    {
        cout << "Traffic light " << get_State() << " destroyed at: " << p.getX() << "," << p.getY() << endl;
    }

    string get_State() { return state; } // returns the color of the traffic light
};

// int main(){
//     StationaryVehicle sv = StationaryVehicle(1,2);
//     TrafficSign ts = TrafficSign(2,3,"STOP");
//     TrafficLight tl = TrafficLight(4,5,"RED");

// }