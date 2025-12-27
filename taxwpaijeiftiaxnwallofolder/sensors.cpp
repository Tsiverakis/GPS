#include <iostream>
#include <vector>
#include "temp.h"
#include "sensors.h"

using namespace std;

// SENSOR
Sensor::Sensor(int range)
{
    this->range = range;
    p = Position(0, 0);
}

// LIDAR
Lidar::Lidar() : Sensor(9) {}

vector<ReadData> Lidar::sensorreading(Position p)
{
    vector<ReadData> temp;
    for (int i = p.getY() + 4; i < p.getY() + 4; i++)
    {
        for (int j = p.getX() - 4; j < p.getX() + 4; j++)
        {
            // if(world(i,j) == worldobject){ ReadData temp1; temp.type = world(i,j).type; temp.distance = |p.getx() - j| + | p.gety()-i|; temp.p = Position(p.getx(),p.gety()); ...genika bazw ta panta}... xreiazomai to world
        }
    }
}

// RADAR
Radar::Radar() : Sensor(12) {};

vector<ReadData> Radar::sensorreading(Position p, string direction)
{
    vector<ReadData> temp;
    if(direction == "UP"){
        for (int i = p.getY(); i <= p.getY() + 12; i++)
        {
            // if(world(p.getx,i) == moving object){ ReadData temp1; bazw ayta poy leei}
        }
    }else if(direction == "DOWN"){

    }
}

Camera:: Camera() : Sensor(7){};

vector<ReadData> Camera::sensorreading(Position p,string direction){

}
