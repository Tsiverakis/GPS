#ifndef GRIDWORLD_H
#define GRIDWORLD_H

#include <vector>
#include <iostream>
#include "temp.h"

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

    void update();
    void render() const;
};

#endif
