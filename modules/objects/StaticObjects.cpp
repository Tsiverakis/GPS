#include "StaticObjects.h"
#include <iostream>

using namespace std;

// StationaryVehicle
StationaryVehicle::StationaryVehicle(int x, int y, string ID, string glyph)
    : WorldObject("StaticObject", ID, glyph, x, y) {
    cout << "[+PARKED: " << ID << "] Parked at (" << x << "," << y << ")" << endl;
}
StationaryVehicle::~StationaryVehicle() {
    cout << "[-PARKED: " << getID() << "] I'm being towed away!" << endl;
}

// TrafficSign 
TrafficSign::TrafficSign(int x, int y, string text, string ID, string glyph)
    : WorldObject("StaticObject", ID, glyph, x, y), signtext(text) {}

TrafficSign::~TrafficSign() {}

string TrafficSign::get_text() const { return signtext; }

// TrafficLight--
TrafficLight::TrafficLight(int x, int y, string initialState, string ID, string glyph)
    : WorldObject("StaticObject", ID, glyph, x, y), state(initialState) {
    cout << "[+LIGHT: " << ID << "] Initialized at (" << x << "," << y << ") to " << state << endl;
}

TrafficLight::~TrafficLight() {
    cout << "[-LIGHT: " << getID() << "] Turning off" << endl;
}

string TrafficLight::get_State() const { return state; }

void TrafficLight::update(int currentTick) {
    if (currentTick % 20 < 10) {
        state = "GREEN";
    }
    else if (currentTick % 20 < 15) {
        state = "YELLOW";
    }
    else {
        state = "RED";
    }
}