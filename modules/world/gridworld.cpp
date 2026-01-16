#include "gridworld.h"
#include <iostream>
#include <algorithm>
#include "../car/car.h"

GridWorld::GridWorld(int size) : size(size) {
    grid.resize(size, std::vector<WorldObject*>(size, nullptr));
}

GridWorld::~GridWorld() {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (grid[x][y] != nullptr) {
                delete grid[x][y];
                grid[x][y] = nullptr;
            }
        }
    }
}

void GridWorld::addObject(WorldObject* obj) {
    Position p = obj->getPosition();
    if (p.getX() >= 0 && p.getX() < size && p.getY() >= 0 && p.getY() < size) {
        grid[p.getX()][p.getY()] = obj;
    }
}

void GridWorld::removeObject(int x, int y) {
    if (x >= 0 && x < size && y >= 0 && y < size) {
        delete grid[x][y];
        grid[x][y] = nullptr;
    }
}

WorldObject* GridWorld::getObject(int x, int y) const {
    if (x >= 0 && x < size && y >= 0 && y < size) {
        return grid[x][y];
    }
    return nullptr;
}

std::vector<std::vector<WorldObject*>>& GridWorld::getGrid() {
    return grid;
}

void GridWorld::update() {
    std::vector<WorldObject*> objectsToMove;

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (grid[x][y] != nullptr) {
                if (grid[x][y]->getType() == "MovingObject" || grid[x][y]->getType() == "SelfDrivingCar") {
                    objectsToMove.push_back(grid[x][y]);
                }
            }
        }
    }
    
    for (auto* obj : objectsToMove) {
        Position oldPos = obj->getPosition();
        
        if (obj->getType() == "MovingObject") {
            MovingVehicle* mv = dynamic_cast<MovingVehicle*>(obj);
            if (mv) {
                grid[oldPos.getX()][oldPos.getY()] = nullptr;
                mv->move();
                Position newPos = mv->getPosition();
                if (newPos.getX() >= 0 && newPos.getX() < size && newPos.getY() >= 0 && newPos.getY() < size) {
                    grid[newPos.getX()][newPos.getY()] = mv;
                } else {
                    delete mv;
                }
            }
        } else if (obj->getType() == "SelfDrivingCar") {
            grid[oldPos.getX()][oldPos.getY()] = nullptr;
            Position newPos = obj->getPosition();
            if (newPos.getX() >= 0 && newPos.getX() < size && newPos.getY() >= 0 && newPos.getY() < size) {
                grid[newPos.getX()][newPos.getY()] = obj;
            }
        }
    }
}

void GridWorld::visualization_full() const {
    std::cout << "\n--- FULL WORLD VISUALIZATION ---" << std::endl;
    for (int y = size - 1; y >= 0; y--) {
        for (int x = 0; x < size; x++) {
            if (grid[x][y] != nullptr)
                std::cout << grid[x][y]->getglyph() << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

void GridWorld::visualization_pov(SelfDrivingCar* ego, int radius, std::string mode) const {
    Position pos = ego->getPosition();
    std::string dir = ego->getDirection();
    
    int x_min, x_max, y_min, y_max;

    if (mode == "centered") {
        x_min = std::max(0, pos.getX() - radius);
        x_max = std::min(size - 1, pos.getX() + radius);
        y_min = std::max(0, pos.getY() - radius);
        y_max = std::min(size - 1, pos.getY() + radius);
    } else { // mode == "front"
        if (dir == "UP") {
            x_min = std::max(0, pos.getX() - radius); x_max = std::min(size - 1, pos.getX() + radius);
            y_min = pos.getY(); y_max = std::min(size - 1, pos.getY() + radius);
        } else if (dir == "DOWN") {
            x_min = std::max(0, pos.getX() - radius); x_max = std::min(size - 1, pos.getX() + radius);
            y_min = std::max(0, pos.getY() - radius); y_max = pos.getY();
        } else if (dir == "LEFT") {
            x_min = std::max(0, pos.getX() - radius); x_max = pos.getX();
            y_min = std::max(0, pos.getY() - radius); y_max = std::min(size - 1, pos.getY() + radius);
        } else { // RIGHT
            x_min = pos.getX(); x_max = std::min(size - 1, pos.getX() + radius);
            y_min = std::max(0, pos.getY() - radius); y_max = std::min(size - 1, pos.getY() + radius);
        }
    }

    std::cout << "\n--- POV VISUALIZATION (" << mode << ") ---" << std::endl;
    for (int y = y_max; y >= y_min; y--) {
        for (int x = x_min; x <= x_max; x++) {
            if (x == pos.getX() && y == pos.getY()) std::cout << "@ ";
            else if (grid[x][y] != nullptr) std::cout << grid[x][y]->getglyph() << " ";
            else std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

void GridWorld::render() const {
    visualization_full();
}