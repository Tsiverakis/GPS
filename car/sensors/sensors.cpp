#include <iostream>
#include <vector>
#include "temp.h"
#include "sensors.h"
#include <cmath>
#include "MovingObjects.h"
#include "StaticObjects.h"
using namespace std;

// dummy values
int max_value = 15; // size of the world

// SENSOR
Sensor::Sensor(int range)
{
    this->range = range;
    p = Position(0, 0);
}

// LIDAR
Lidar::Lidar() : Sensor(9) {}

vector<ReadData> Lidar::sensorreading(Position p, string direction, vector<vector<WorldObject *>> &world)
{
    vector<ReadData> temp;
    int border1, border2, border3, border4;
    if ((max_value - 1 - p.getY() + 4) <= max_value)
    {
        border2 = (max_value - 1 - p.getY()) + 4;
    }
    else
    {
        border2 = max_value - 1;
    }

    if ((max_value - 1 - p.getY()) - 4 >= 0)
    {
        border1 = (max_value - 1 - p.getY()) - 4;
    }
    else
    {
        border1 = 0;
    }

    if (p.getX() - 4 >= 0)
    {
        border3 = p.getX() - 4;
    }
    else
    {
        border3 = 0;
    }

    if (p.getX() + 4 <= max_value)
    {
        border4 = p.getX() + 4;
    }
    else
    {
        border4 = max_value - 1;
    }

    for (int i = border1; i <= border2; i++)
    {
        for (int j = border3; j <= border4; j++)
        {
            if (world[j][i] != nullptr)
            {
                if (world[j][i]->getType() == "MovingObject" || world[j][i]->getType() == "StaticObject")
                {
                    ReadData temp1;
                    temp1.distance = abs(p.getX() - j) + abs(p.getY() - world[j][i]->getPosition().getY());
                    temp1.objectid = world[j][i]->getID();
                    double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                    temp1.confidence = 0.99 * (1.0 - ((double)temp1.distance / range)) + noise;
                    temp1.type = world[j][i]->getType();
                    temp1.p = world[j][i]->getPosition();
                    temp1.speed = -1;
                    temp1.direction = "N/A";
                    temp1.trafficlightp = "N/A";
                    temp1.signtext = "N/A";

                    temp.emplace_back(temp1);
                }
            }
        }
    }
    return temp;
}

// RADAR
Radar::Radar() : Sensor(12) {};

vector<ReadData> Radar::sensorreading(Position p, string direction, vector<vector<WorldObject *>> &world)
{
    vector<ReadData> temp;
    int border2;
    if (direction == "UP")
    {
        if ((max_value - p.getY() - 2) >= 0)
        {
            if ((max_value - p.getY() - 1) - 12 >= 0)
            {
                border2 = (max_value - p.getY() - 1) - 12;
            }
            else
            {
                border2 = 0;
            }
            for (int i = (max_value - p.getY() - 1) - 1; i >= border2; i--)
            {
                if (world[p.getX()][i] != nullptr)
                {
                    if (world[p.getX()][i]->getType() == "MovingObject")
                    {
                        ReadData temp1;
                        temp1.distance = abs(p.getY() - world[p.getX()][i]->getPosition().getY());
                        MovingVehicle *car = dynamic_cast<MovingVehicle *>(world[p.getX()][i]);
                        if (car != nullptr)
                        {
                            temp1.speed = car->getSpeed();
                            temp1.direction = car->getDirection();
                        }
                        double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                        temp1.confidence = 0.95 * (1.0 - ((double)temp1.distance / range)) + noise;
                        temp1.objectid = world[p.getX()][i]->getID();
                        temp1.signtext = "N/A";
                        temp1.type = world[p.getX()][i]->getType();
                        temp1.trafficlightp = "N/A";
                        temp1.p = world[p.getX()][i]->getPosition();
                        temp.emplace_back(temp1);
                    }
                }
            }
        }
    }
    else if (direction == "DOWN")
    {
        if ((max_value - 1 - p.getY()) + 1 < max_value)
        {
            if ((max_value - 1 - p.getY()) + 12 < max_value)
            {
                border2 = (max_value + 1 - p.getY()) + 12;
            }
            else
            {
                border2 = max_value - 1;
            }

            for (int i = (max_value - p.getY() - 1); i <= border2; i++)
            {
                if (world[p.getX()][i] != nullptr)
                {
                    if (world[p.getX()][i]->getType() == "MovingObject")
                    {
                        ReadData temp1;
                        temp1.distance = abs(p.getY() - world[p.getX()][i]->getPosition().getY());
                        MovingVehicle *car = dynamic_cast<MovingVehicle *>(world[p.getX()][i]);
                        if (car != nullptr)
                        {
                            temp1.speed = car->getSpeed();
                            temp1.direction = car->getDirection();
                        }
                        double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                        temp1.confidence = 0.95 * (1.0 - ((double)temp1.distance / range)) + noise;
                        temp1.objectid = world[p.getX()][i]->getID();
                        temp1.signtext = "N/A";
                        temp1.type = world[p.getX()][i]->getType();
                        temp1.trafficlightp = "N/A";
                        temp1.p = world[p.getX()][i]->getPosition();
                        temp.emplace_back(temp1);
                    }
                }
            }
        }
    }
    else if (direction == "LEFT")
    {
        if (p.getX() - 1 >= 0)
        {
            if (p.getX() - 12 >= 0)
            {
                border2 = p.getX() - 12;
            }
            else
            {
                border2 = 0;
            }
            for (int i = p.getX() - 1; i >= border2; i--)
            {
                if (world[i][p.getY()] != nullptr)
                {
                    if (world[i][p.getY()]->getType() == "MovingObject")
                    {
                        ReadData temp1;
                        temp1.distance = abs(p.getX() - world[i][p.getY()]->getPosition().getX());
                        MovingVehicle *car = dynamic_cast<MovingVehicle *>(world[i][p.getY()]);
                        if (car != nullptr)
                        {
                            temp1.speed = car->getSpeed();
                            temp1.direction = car->getDirection();
                        }
                        double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                        temp1.confidence = 0.95 * (1.0 - ((double)temp1.distance / range)) + noise;
                        temp1.objectid = world[i][p.getY()]->getID();
                        temp1.signtext = "N/A";
                        temp1.type = world[i][p.getY()]->getType();
                        temp1.trafficlightp = "N/A";
                        temp1.p = world[i][p.getY()]->getPosition();
                        temp.emplace_back(temp1);
                    }
                }
            }
        }
    }
    else
    {
        if (p.getX() + 1 < max_value)
        {
            if (p.getX() + 12 < max_value)
            {
                border2 = p.getX() + 12;
            }
            else
            {
                border2 = max_value - 1;
            }
            for (int i = p.getX() + 1; i <= border2; i++)
            {
                if (world[i][p.getY()] != nullptr)
                {
                    if (world[i][p.getY()]->getType() == "MovingObject")
                    {
                        ReadData temp1;
                        temp1.distance = abs(p.getX() - world[i][p.getY()]->getPosition().getX());
                        MovingVehicle *car = dynamic_cast<MovingVehicle *>(world[i][p.getY()]);
                        if (car != nullptr)
                        {
                            temp1.speed = car->getSpeed();
                            temp1.direction = car->getDirection();
                        }
                        double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                        temp1.confidence = 0.95 * (1.0 - ((double)temp1.distance / range)) + noise;
                        temp1.objectid = world[i][p.getY()]->getID();
                        temp1.signtext = "N/A";
                        temp1.type = world[i][p.getY()]->getType();
                        temp1.trafficlightp = "N/A";
                        temp1.p = world[i][p.getY()]->getPosition();
                        temp.emplace_back(temp1);
                    }
                }
            }
        }
    }

    return temp;
}

Camera::Camera() : Sensor(7) {};

vector<ReadData> Camera::sensorreading(Position p, string direction, vector<vector<WorldObject *>> &world)
{
    vector<ReadData> temp;
    int border1, border2, border3, border4;
    if (direction == "UP")
    {
        if ((max_value - 2 - p.getY()) >= 0)
        {
            border2 = (max_value - 1 - p.getY());
            if ((max_value - 1 - p.getY()) - 7 >= 0)
            {
                border1 = (max_value - 1 - p.getY()) - 7;
            }
            else
            {
                border1 = 0;
            }

            if (p.getX() - 3 >= 0)
            {
                border3 = p.getX() - 3;
            }
            else
            {
                border3 = 0;
            }

            if (p.getX() + 3 < max_value)
            {
                border4 = p.getX() + 3;
            }
            else
            {
                border4 = max_value - 1;
            }

            for (int i = border1; i < border2; i++)
            {
                for (int j = border3; j <= border4; j++)
                {
                    ReadData temp1;
                    if (world[j][i] != nullptr)
                    {
                        if (world[j][i]->getType() == "StaticObject")
                        {
                            temp1.type = world[j][i]->getType();
                            temp1.objectid = world[j][i]->getID();
                            temp1.distance = abs(world[j][i]->getPosition().getX() - p.getX()) + abs(world[j][i]->getPosition().getY() - p.getY());
                            temp1.p = world[j][i]->getPosition();
                            double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                            temp1.confidence = 0.87 * (1.0 - ((double)temp1.distance / range)) + noise;
                            if (world[j][i]->getType() == "TrafficSign")
                            {
                                TrafficSign *sign = dynamic_cast<TrafficSign *>(world[j][i]);
                                if (sign != nullptr)
                                {
                                    temp1.signtext = sign->get_text();
                                    temp1.trafficlightp = "N/A";
                                    temp1.speed = -1;
                                    temp1.direction = "N/A";
                                }
                            }
                            else if (world[j][i]->getType() == "TrafficLight")
                            {
                                TrafficLight *light = dynamic_cast<TrafficLight *>(world[j][i]);
                                if (light != nullptr)
                                {
                                    temp1.trafficlightp = light->get_State();
                                    temp1.signtext = "N/A";
                                    temp1.speed = -1;
                                    temp1.direction = "N/A";
                                }
                            }
                            temp.emplace_back(temp1);
                        }
                        else if (world[j][i]->getType() == "MovingObject")
                        {
                            temp1.type = world[j][i]->getType();
                            temp1.objectid = world[j][i]->getID();
                            temp1.distance = abs(world[j][i]->getPosition().getX() - p.getX()) + abs(world[j][i]->getPosition().getY() - p.getY());
                            temp1.p = world[j][i]->getPosition();
                            double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                            temp1.confidence = 0.87 * (1.0 - ((double)temp1.distance / range)) + noise;
                            MovingVehicle *vehicle = dynamic_cast<MovingVehicle *>(world[j][i]);
                            if (vehicle != nullptr)
                            {
                                temp1.speed = vehicle->getSpeed();
                                temp1.direction = vehicle->getDirection();
                                temp1.signtext = "N/A";
                                temp1.trafficlightp = "N/A";
                            }
                            temp.emplace_back(temp1);
                        }
                    }
                }
            }
        }
    }
    else if (direction == "DOWN")
    {
        if ((max_value - p.getY() - 1) < max_value)
        {
            border1 = (max_value - p.getY() - 1);
            if ((max_value - p.getY() - 1) + 7 < max_value)
            {
                border2 = (max_value - p.getY() - 1) + 7;
            }
            else
            {
                border2 = max_value - 1;
            }
            if (p.getX() - 3 >= 0)
            {
                border3 = p.getX() - 3;
            }
            else
            {
                border3 = 0;
            }

            if (p.getX() + 3 < max_value)
            {
                border4 = p.getX() + 3;
            }
            else
            {
                border4 = max_value - 1;
            }
            for (int i = border1; i < border2; i++)
            {
                for (int j = border3; j <= border4; j++)
                {
                    ReadData temp1;
                    if (world[j][i] != nullptr)
                    {
                        if (world[j][i]->getType() == "StaticObject")
                        {
                            temp1.type = world[j][i]->getType();
                            temp1.objectid = world[j][i]->getID();
                            temp1.distance = abs(world[j][i]->getPosition().getX() - p.getX()) + abs(world[j][i]->getPosition().getY() - p.getY());
                            temp1.p = world[j][i]->getPosition();
                            double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                            temp1.confidence = 0.87 * (1.0 - ((double)temp1.distance / range)) + noise;
                            if (world[j][i]->getType() == "TrafficSign")
                            {
                                TrafficSign *sign = dynamic_cast<TrafficSign *>(world[j][i]);
                                if (sign != nullptr)
                                {
                                    temp1.signtext = sign->get_text();
                                    temp1.trafficlightp = "N/A";
                                    temp1.speed = -1;
                                    temp1.direction = "N/A";
                                }
                            }
                            else if (world[j][i]->getType() == "TrafficLight")
                            {
                                TrafficLight *light = dynamic_cast<TrafficLight *>(world[j][i]);
                                if (light != nullptr)
                                {
                                    temp1.trafficlightp = light->get_State();
                                    temp1.signtext = "N/A";
                                    temp1.speed = -1;
                                    temp1.direction = "N/A";
                                }
                            }
                            temp.emplace_back(temp1);
                        }
                        else if (world[j][i]->getType() == "MovingObject")
                        {
                            temp1.type = world[j][i]->getType();
                            temp1.objectid = world[j][i]->getID();
                            temp1.distance = abs(world[j][i]->getPosition().getX() - p.getX()) + abs(world[j][i]->getPosition().getY() - p.getY());
                            temp1.p = world[j][i]->getPosition();
                            double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                            temp1.confidence = 0.87 * (1.0 - ((double)temp1.distance / range)) + noise;
                            MovingVehicle *vehicle = dynamic_cast<MovingVehicle *>(world[j][i]);
                            if (vehicle != nullptr)
                            {
                                temp1.speed = vehicle->getSpeed();
                                temp1.direction = vehicle->getDirection();
                                temp1.signtext = "N/A";
                                temp1.trafficlightp = "N/A";
                            }
                            temp.emplace_back(temp1);
                        }
                    }
                }
            }
        }
    }
    else if (direction == "RIGHT")
    {
        if (p.getX() + 1 < max_value)
        {
            border3 = p.getX() + 1;
            if ((max_value - p.getY() - 1) - 3 >= 0)
            {
                border1 = (max_value - p.getY() - 1) - 3;
            }
            else
            {
                border1 = 0;
            }

            if ((max_value - p.getY() - 1) + 3 < max_value)
            {
                border2 = (max_value - p.getY() - 1) + 3;
            }
            else
            {
                border2 = max_value - 1;
            }

            if (p.getX() + 7 < max_value)
            {
                border4 = p.getX() + 7;
            }
            else
            {
                border4 = max_value - 1;
            }
            for (int i = border1; i <= border2; i++)
            {
                for (int j = border3; j <= border4; j++)
                {
                    ReadData temp1;
                    if (world[j][i] != nullptr)
                    {
                        if (world[j][i]->getType() == "StaticObject")
                        {
                            temp1.type = world[j][i]->getType();
                            temp1.objectid = world[j][i]->getID();
                            temp1.distance = abs(world[j][i]->getPosition().getX() - p.getX()) + abs(world[j][i]->getPosition().getY() - p.getY());
                            temp1.p = world[j][i]->getPosition();
                            double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                            temp1.confidence = 0.87 * (1.0 - ((double)temp1.distance / range)) + noise;
                            if (world[j][i]->getType() == "TrafficSign")
                            {
                                TrafficSign *sign = dynamic_cast<TrafficSign *>(world[j][i]);
                                if (sign != nullptr)
                                {
                                    temp1.signtext = sign->get_text();
                                    temp1.trafficlightp = "N/A";
                                    temp1.speed = -1;
                                    temp1.direction = "N/A";
                                }
                            }
                            else if (world[j][i]->getType() == "TrafficLight")
                            {
                                TrafficLight *light = dynamic_cast<TrafficLight *>(world[j][i]);
                                if (light != nullptr)
                                {
                                    temp1.trafficlightp = light->get_State();
                                    temp1.signtext = "N/A";
                                    temp1.speed = -1;
                                    temp1.direction = "N/A";
                                }
                            }
                            temp.emplace_back(temp1);
                        }
                        else if (world[j][i]->getType() == "MovingObject")
                        {
                            temp1.type = world[j][i]->getType();
                            temp1.objectid = world[j][i]->getID();
                            temp1.distance = abs(world[j][i]->getPosition().getX() - p.getX()) + abs(world[j][i]->getPosition().getY() - p.getY());
                            temp1.p = world[j][i]->getPosition();
                            double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                            temp1.confidence = 0.87 * (1.0 - ((double)temp1.distance / range)) + noise;
                            MovingVehicle *vehicle = dynamic_cast<MovingVehicle *>(world[j][i]);
                            if (vehicle != nullptr)
                            {
                                temp1.speed = vehicle->getSpeed();
                                temp1.direction = vehicle->getDirection();
                                temp1.signtext = "N/A";
                                temp1.trafficlightp = "N/A";
                            }
                            temp.emplace_back(temp1);
                        }
                    }
                }
            }
        }
    }
    else
    {

        if (p.getX() - 1 >= 0)
        {
            border4 = p.getX();
            if ((max_value - p.getY()) - 2 >= 0)
            {
                border1 = (max_value - p.getY()) - 2;
            }
            else
            {
                border1 = 0;
            }
            if ((max_value - p.getY()) + 4 < max_value)
            {
                border2 = (max_value - p.getY()) + 4;
            }
            else
            {
                border2 = max_value - 1;
            }
            if (p.getX() - 7 >= 0)
            {
                border3 = p.getX() - 7;
            }
            else
            {
                border3 = 0;
            }
            for (int i = border1; i <= border2; i++)
            {
                for (int j = border3; j < border4; j++)
                {
                    ReadData temp1;
                    if (world[j][i] != nullptr)
                    {
                        if (world[j][i]->getType() == "StaticObject")
                        {
                            temp1.type = world[j][i]->getType();
                            temp1.objectid = world[j][i]->getID();
                            temp1.distance = abs(world[j][i]->getPosition().getX() - p.getX()) + abs(world[j][i]->getPosition().getY() - p.getY());
                            temp1.p = world[j][i]->getPosition();
                            double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                            temp1.confidence = 0.87 * (1.0 - ((double)temp1.distance / range)) + noise;
                            if (world[j][i]->getType() == "TrafficSign")
                            {
                                TrafficSign *sign = dynamic_cast<TrafficSign *>(world[j][i]);
                                if (sign != nullptr)
                                {
                                    temp1.signtext = sign->get_text();
                                    temp1.trafficlightp = "N/A";
                                    temp1.speed = -1;
                                    temp1.direction = "N/A";
                                }
                            }
                            else if (world[j][i]->getType() == "TrafficLight")
                            {
                                TrafficLight *light = dynamic_cast<TrafficLight *>(world[j][i]);
                                if (light != nullptr)
                                {
                                    temp1.trafficlightp = light->get_State();
                                    temp1.signtext = "N/A";
                                    temp1.speed = -1;
                                    temp1.direction = "N/A";
                                }
                            }
                            temp.emplace_back(temp1);
                        }
                        else if (world[j][i]->getType() == "MovingObject")
                        {
                            temp1.type = world[j][i]->getType();
                            temp1.objectid = world[j][i]->getID();
                            temp1.distance = abs(world[j][i]->getPosition().getX() - p.getX()) + abs(world[j][i]->getPosition().getY() - p.getY());
                            temp1.p = world[j][i]->getPosition();
                            double noise = (rand() % 2 == 0) ? -0.05 : 0.05;
                            temp1.confidence = 0.87 * (1.0 - ((double)temp1.distance / range)) + noise;
                            MovingVehicle *vehicle = dynamic_cast<MovingVehicle *>(world[j][i]);
                            if (vehicle != nullptr)
                            {
                                temp1.speed = vehicle->getSpeed();
                                temp1.direction = vehicle->getDirection();
                                temp1.signtext = "N/A";
                                temp1.trafficlightp = "N/A";
                            }
                            temp.emplace_back(temp1);
                        }
                    }
                }
            }
        }
    }
    return temp;
}
