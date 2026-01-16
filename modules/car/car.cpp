#include "car.h"

using namespace std;

// constructor
SelfDrivingCar::SelfDrivingCar(Position p, Position target)
    : WorldObject("SelfDrivingCar", "EGO", "@", p.getX(), p.getY()) // Κλήση του constructor της βάσης
{
    this->p = p;
    this->target = target;
    this->Direction = "UP";
    this->speed = 0;
    this->lidar = Lidar();
    this->radar = Radar();
    this->camera = Camera();
    this->engine = SensorFusionEngine();

    cout << "[+CAR: EGO] Initialized at (" << p.getX() << "," << p.getY() << ") facing UP" << endl;
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

Position SelfDrivingCar::getTarget() const
{
    return target;
}

void SelfDrivingCar::makeDecision(vector<ReadData> data)
{
    bool up = false, down = false, left = false, right = false;
    bool traffic_light_detected = false;
    bool obstacle_detected = false;

    int distToTarget = abs(p.getX() - target.getX()) + abs(p.getY() - target.getY());

    if (p.getX() < target.getX()) right = true;
    else if (p.getX() > target.getX()) left = true;

    if (p.getY() < target.getY()) up = true;
    else if (p.getY() > target.getY()) down = true;

    for (const auto& obj : data)
    {
        if (obj.distance <= 2)
        {
            if (obj.type == "StaticObject")
            {
                if (obj.trafficlightp == "RED" || obj.trafficlightp == "YELLOW")
                {
                    traffic_light_detected = true;
                }
                
                if (up && obj.p.getY() > p.getY() && obj.p.getX() == p.getX()) { up = false; obstacle_detected = true; }
                if (down && obj.p.getY() < p.getY() && obj.p.getX() == p.getX()) { down = false; obstacle_detected = true; }
                if (right && obj.p.getX() > p.getX() && obj.p.getY() == p.getY()) { right = false; obstacle_detected = true; }
                if (left && obj.p.getX() < p.getX() && obj.p.getY() == p.getY()) { left = false; obstacle_detected = true; }
            }
            else if (obj.type == "MovingObject")
            {
                if (up && obj.p.getY() > p.getY() && obj.p.getX() == p.getX()) obstacle_detected = true;
                if (down && obj.p.getY() < p.getY() && obj.p.getX() == p.getX()) obstacle_detected = true;
                if (right && obj.p.getX() > p.getX() && obj.p.getY() == p.getY()) obstacle_detected = true;
                if (left && obj.p.getX() < p.getX() && obj.p.getY() == p.getY()) obstacle_detected = true;
            }
        }
    }

    if (distToTarget == 0)
    {
        speed = 0;
    }
    else if (traffic_light_detected || obstacle_detected)
    {
        speed = 0;
    }
    else
    {
        if (distToTarget < 2) speed = distToTarget;
        else speed = 2;
    }

    if (up) Direction = "UP";
    else if (down) Direction = "DOWN";
    else if (right) Direction = "RIGHT";
    else if (left) Direction = "LEFT";
}

bool SelfDrivingCar::executeMovement()
{
    if (speed <= 0) 
    {
        if (p.getX() == target.getX() && p.getY() == target.getY()) return true;
        return false;
    }

    if (Direction == "UP") p.setY(p.getY() + speed);
    else if (Direction == "DOWN") p.setY(p.getY() - speed);
    else if (Direction == "RIGHT") p.setX(p.getX() + speed);
    else if (Direction == "LEFT") p.setX(p.getX() - speed);

    if (p.getX() < 0) p.setX(0);
    if (p.getY() < 0) p.setY(0);
    if (p.getX() >= max_value) p.setX(max_value - 1);
    if (p.getY() >= max_value) p.setY(max_value - 1);

    cout << "DEBUG: Car is at (" << p.getX() << "," << p.getY() << ") with speed " << speed << " heading " << Direction << endl;

    if (p.getX() == target.getX() && p.getY() == target.getY())
    {
        cout << "[GOAL] Target reached!" << endl;
        return true;
    }

    return false;
}