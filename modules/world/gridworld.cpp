#include "gridworld.h"
#include <iostream>
#include <algorithm>
#include "../car/car.h"
#include "../objects/StaticObjects.h"

GridWorld::GridWorld(int size) : size(size)
{
    grid.resize(size, std::vector<WorldObject *>(size, nullptr));
}

GridWorld::~GridWorld()
{
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (grid[x][y] != nullptr)
            {
                delete grid[x][y];
                grid[x][y] = nullptr;
            }
        }
    }
}

void GridWorld::addObject(WorldObject *obj)
{
    Position p = obj->getPosition();
    if (p.getX() >= 0 && p.getX() < size && p.getY() >= 0 && p.getY() < size)
    {
        grid[p.getX()][p.getY()] = obj;
    }
}

void GridWorld::removeObject(int x, int y)
{
    if (x >= 0 && x < size && y >= 0 && y < size)
    {
        delete grid[x][y];
        grid[x][y] = nullptr;
    }
}

WorldObject *GridWorld::getObject(int x, int y) const
{
    if (x >= 0 && x < size && y >= 0 && y < size)
    {
        return grid[x][y];
    }
    return nullptr;
}

std::vector<std::vector<WorldObject *>> &GridWorld::getGrid()
{
    return grid;
}

void GridWorld::update(int *count)
{
    std::vector<MovingVehicle *> objectsToMove;
    std::vector<WorldObject *> lights;

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (grid[x][y] != nullptr)
            {
                if (grid[x][y]->getType() == "MovingObject" || grid[x][y]->getType() == "SelfDrivingCar")
                {
                    objectsToMove.emplace_back(dynamic_cast<MovingVehicle *>(grid[x][y]));
                }
                else if (grid[x][y]->getType() == "StaticObject")
                {
                    std::string id;
                    size_t index = grid[x][y]->getID().find(':');
                    if (index != std::string::npos)
                    {
                        id = grid[x][y]->getID().substr(0, index);
                    }
                    if (id == "TrafficLight")
                    {
                        lights.push_back(grid[x][y]);
                    }
                    {
                    }
                }
            }
        }
    }

    for (auto *obj : lights)
    {
        TrafficLight *light = dynamic_cast<TrafficLight *>(obj);
        if (light->get_State() == "GREEN" && *count == 8)
        {
            light->set_State("YELLOW");
            *count = 0;
        }
        else if (light->get_State() == "YELLOW" && *count == 2)
        {
            light->set_State("RED");
            *count = 0;
        }
        else if (light->get_State() == "RED" && *count == 4)
        {
            light->set_State("GREEN");
            *count = 0;
        }


        for (MovingVehicle *obj : objectsToMove)
        {
            if (obj->getDirection() == "UP")
            {
                obj->getPosition().setY(obj->getPosition().getY() + 1);
            }
            else if (obj->getDirection() == "DOWN")
            {
                obj->getPosition().setY(obj->getPosition().getY() - 1);
            }
            else if (obj->getDirection() == "RIGHT")
            {
                obj->getPosition().setX(obj->getPosition().getX() + 1);
            }
            else
            {
                obj->getPosition().setX(obj->getPosition().getX() - 1);
            }
        }
    }
}


void GridWorld::visualization_full() const
{
    std::cout << "\n--- FULL WORLD VISUALIZATION ---" << std::endl;
    for (int y = size - 1; y >= 0; y--)
    {
        for (int x = 0; x < size; x++)
        {
            if (grid[x][y] != nullptr)
                std::cout << grid[x][y]->getglyph() << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

void GridWorld::visualization_pov(SelfDrivingCar *ego, int radius, std::string mode) const
{
    Position pos = ego->getPosition();
    std::string dir = ego->getDirection();

    int x_min, x_max, y_min, y_max;

    if (mode == "centered")
    {
        x_min = std::max(0, pos.getX() - radius);
        x_max = std::min(size - 1, pos.getX() + radius);
        y_min = std::max(0, pos.getY() - radius);
        y_max = std::min(size - 1, pos.getY() + radius);
    }
    else
    { // mode == "front"
        if (dir == "UP")
        {
            x_min = std::max(0, pos.getX() - radius);
            x_max = std::min(size - 1, pos.getX() + radius);
            y_min = pos.getY();
            y_max = std::min(size - 1, pos.getY() + radius);
        }
        else if (dir == "DOWN")
        {
            x_min = std::max(0, pos.getX() - radius);
            x_max = std::min(size - 1, pos.getX() + radius);
            y_min = std::max(0, pos.getY() - radius);
            y_max = pos.getY();
        }
        else if (dir == "LEFT")
        {
            x_min = std::max(0, pos.getX() - radius);
            x_max = pos.getX();
            y_min = std::max(0, pos.getY() - radius);
            y_max = std::min(size - 1, pos.getY() + radius);
        }
        else
        { // RIGHT
            x_min = pos.getX();
            x_max = std::min(size - 1, pos.getX() + radius);
            y_min = std::max(0, pos.getY() - radius);
            y_max = std::min(size - 1, pos.getY() + radius);
        }
    }

    std::cout << "\n--- POV VISUALIZATION (" << mode << ") ---" << std::endl;
    for (int y = y_max; y >= y_min; y--)
    {
        for (int x = x_min; x <= x_max; x++)
        {
            if (x == pos.getX() && y == pos.getY())
                std::cout << "@ ";
            else if (grid[x][y] != nullptr)
                std::cout << grid[x][y]->getglyph() << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

void GridWorld::render() const
{
    visualization_full();
}