#include "../temp.h"
#include <string>
#include "StaticObjects.h"

using namespace std;

// constructor
StationaryVehicle::StationaryVehicle(int x, int y, string ID, string glyph)
    : WorldObject(type, ID, glyph, x, y)
{
    cout << "Stationary vehicle created at: " << p.getX() << "," << p.getY() << endl;
}

// destructor
StationaryVehicle::~StationaryVehicle()
{
    cout << "Stationary vehicle destroyed at: " << p.getX() << "," << p.getY() << endl;
}

// constructor
TrafficSign::TrafficSign(int x, int y, string signID, string ID, string glyph)
    : WorldObject(type, ID, glyph, x, y)
{
    this->signtext = signID;
    cout << "Sign " << get_text() << " created at: " << p.getX() << "," << p.getY() << endl;
}

// destructor
TrafficSign::~TrafficSign()
{
    cout << "Sign " << get_text() << " destroyed at: " << p.getX() << "," << p.getY() << endl;
}

string TrafficSign::get_text() { return signtext; } // returns the type of the sign

// It is a traffic light with a color(state) and a Position x,y

// constructor
TrafficLight::TrafficLight(int x, int y, string state, string ID, string glyph)
    : WorldObject(type, ID, glyph, x, y)
{
    this->state = state;
    cout << "Traffic light " << get_State() << " created at: " << p.getX() << "," << p.getY() << endl;
}

// destructor
TrafficLight::~TrafficLight()
{
    cout << "Traffic light " << get_State() << " destroyed at: " << p.getX() << "," << p.getY() << endl;
}

string TrafficLight::get_State() { return state; } // returns the color of the traffic light

void TrafficLight::set_State(string color) { state = color; };
