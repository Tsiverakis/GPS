#include "car.h"

extern int max_value;
using namespace std;
// constructor
SelfDrivingCar::SelfDrivingCar(Position p, Position target, string type, string id,string glyph) : WorldObject(type,id,glyph,p.getX() , p.getY())
{
    this->target = target;
    Direction = "UP";
    speed = 0;
    lidar = Lidar();
    radar = Radar();
    camera = Camera();
    engine = SensorFusionEngine();
}

// destructor
SelfDrivingCar::~SelfDrivingCar() {}

vector<ReadData> SelfDrivingCar::collectSensorData(std::vector<std::vector<WorldObject *>> &world)
{
    vector<ReadData> temp1, temp2, temp3, data;
    temp1 = lidar.sensorreading(p, Direction, world);
    temp2 = radar.sensorreading(p, Direction, world);
    temp3 = camera.sensorreading(p, Direction, world);
    data.insert(data.end(), temp1.begin(), temp1.end());
    data.insert(data.end(), temp2.begin(), temp2.end());
    data.insert(data.end(), temp3.begin(), temp3.end());
    engine.create_map(data);
    data = engine.fusion(engine.getMap());

    return data;
}

string SelfDrivingCar::getDirection() const
{
    return Direction;
}

Position SelfDrivingCar::getPosition() const
{
    return p;
}

void SelfDrivingCar::makeDecision(vector<ReadData> data)
{
    int count_up = 0, count_down = 0, count_left = 0, count_right = 0;
    bool up = false, down = false, left = false, right = false, change_direction = false, traffic_light_detected = false, bike_detected = false, decelerate = false, accelerate = false, decelerate1 = false;
    string decision;

    // calculates where the car needs to head to
    if (p.getX() < target.getX())
    {
        right = true;
    }
    else if (p.getX() > target.getX())
    {
        left = true;
    }

    if (p.getY() > target.getY())
    {
        down = true;
    }
    else if (p.getY() < target.getY())
    {
        up = true;
    }

    // we are arriving
    if (abs(p.getX() - target.getX()) + abs(p.getY() - target.getY()) <= 5 && (p.getX() != target.getX() || p.getY() != target.getY()))
    {
        decelerate1 = true;
    }

    for (ReadData obj : data)
    {
        string id;
        size_t index = obj.objectid.find(':');
        if (index != string::npos)
        {
            id = obj.objectid.substr(0, index);
        }
        if (obj.distance <= 3)
        { // checks for nearby objects
            if (obj.type == "StaticObject" && obj.trafficlightp != "N/A")
            { // check for red and yellow traffic lights
                if (obj.trafficlightp == "RED" || obj.trafficlightp == "YELLOW")
                {
                    traffic_light_detected = true;
                    decelerate = true;
                }
            }
        }

        if (obj.distance <= 2)
        {
            if (obj.type == "StaticObject" && id == "StationaryVehicle") // if it moves towards a StationaryVehicle it changes direction
            {                                                            // check for colliding with a static car
                if (down == true && obj.p.getY() < p.getY() && p.getX() == obj.p.getX())
                {
                    down = false;
                }

                if (up == true && obj.p.getY() > p.getY() && p.getX() == obj.p.getX())
                {
                    up = false;
                }

                if (right == true && obj.p.getX() > p.getX() && p.getY() == obj.p.getY())
                {
                    right = false;
                }

                if (left == true && obj.p.getX() < p.getX() && p.getY() == obj.p.getY())
                {
                    left = false;
                }
            }
            else if (obj.type == "MovingObject") // if it moves towards a moving object it decelerates
            {
                if (down == true && obj.p.getY() < p.getY() && p.getX() == obj.p.getX())
                {
                    decelerate = true;
                }
                else if (up == true && obj.p.getY() > p.getY() && p.getX() == obj.p.getX())
                {
                    decelerate = true;
                }
                else if (right == true && obj.p.getX() > p.getX() && p.getY() == obj.p.getY())
                {
                    decelerate = true;
                }
                else if (left == true && obj.p.getX() < p.getX() && p.getY() == obj.p.getY())
                {
                    decelerate = true;
                }
            }
        }
    }

    if (decelerate1 && speed > 1)
    {
        speed--; // decelerate but not stop
    }

    if (decelerate && speed > 0)
    {
        speed--; // decelarate and stop
    }

    if (up)
    {
        Direction = "UP";
    }
    else if (down)
    {
        Direction = "DOWN";
    }
    else if (right)
    {
        Direction = "RIGHT";
    }
    else if (left)
    {
        Direction = "LEFT";
    }

    if (!decelerate1 && !decelerate && speed < 2 && !traffic_light_detected)
    {
        speed++; // accelerate
    }
}

void SelfDrivingCar::executeMovement()
{
    if (Direction == "UP")
    {
        p.setY(p.getY() + speed);
    }
    else if (Direction == "DOWN")
    {
        p.setY(p.getY() - speed);
    }
    else if (Direction == "RIGHT")
    {
        p.setX(p.getX() + speed);
    }
    else
    {
        p.setX(p.getX() - speed);
    }

}
