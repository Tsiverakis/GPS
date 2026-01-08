#include "gridworld.h"
#include <iostream>

// constructor
GridWorld::GridWorld(int size) : size(size) {
    grid.resize(size, std::vector<WorldObject*>(size, nullptr));
}

// destructor
GridWorld::~GridWorld() {
    for (auto& row : grid) {
        for (auto* obj : row) {
            delete obj;
        }
    }
}

// add object to world
void GridWorld::addObject(WorldObject* obj) {
    Position p = obj->getPosition();
    if (p.getX() >= 0 && p.getX() < size && p.getY() >= 0 && p.getY() < size) {
        grid[p.getX()][p.getY()] = obj;
    }
}

// remove object
void GridWorld::removeObject(int x, int y) {
    if (x >= 0 && x < size && y >= 0 && y < size) {
        delete grid[x][y];
        grid[x][y] = nullptr;
    }
}

// access single cell
WorldObject* GridWorld::getObject(int x, int y) const {
    if (x >= 0 && x < size && y >= 0 && y < size) {
        return grid[x][y];
    }
    return nullptr;
}

// access grid (used by sensors)
std::vector<std::vector<WorldObject*>>& GridWorld::getGrid() {
    return grid;
}

// update world 
void GridWorld::update() {
    
}

// visualization
void GridWorld::render() const {
    for (int y = size - 1; y >= 0; y--) {
        for (int x = 0; x < size; x++) {
            if (grid[x][y] != nullptr)
                std::cout << grid[x][y]->getglyph() << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}
