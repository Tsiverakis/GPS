#ifndef GRIDWORLD_H
#define GRIDWORLD_H

#include <vector>
#include <iostream>
#include "../temp.h"
#include "../objects/MovingObjects.h" 

class SelfDrivingCar;

class GridWorld {
private:
    int size;
    
    std::vector<std::vector<WorldObject*>> grid;

public:
    GridWorld(int size);
    ~GridWorld();

    void addObject(WorldObject* obj);
    void removeObject(int x, int y);

    WorldObject* getObject(int x, int y) const;
    std::vector<std::vector<WorldObject*>>& getGrid();

    void update(int *count);
    void render() const;

    void visualization_full() const;
    void visualization_pov(SelfDrivingCar* ego, int radius, std::string mode) const;
    
    bool isWithinBounds(int x, int y) const {
        return (x >= 0 && x < size && y >= 0 && y < size);
    }
};

#endif