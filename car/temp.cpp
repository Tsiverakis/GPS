#include <iostream>
#include "temp.h"

using namespace std;

// POSITION

Position::Position()
{
    this->x = -1;
    this->y = -1;
}

Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Position::setX(int x)
{
    this->x = x;
}

void Position::setY(int y)
{
    this->y = y;
}

int Position::getX() const
{
    return this->x;
}

int Position::getY() const
{
    return this->y;
}

// WORLD OBJECT
//  constructor
WorldObject::WorldObject(string type, string ID, string glyph, int x, int y)
{
    this->glyph = glyph;
    this->ID = ID;
    this->type = type;
    p = Position(x, y);
}
WorldObject::~WorldObject()
{
}

string WorldObject::getType()
{
    return type;
}

Position WorldObject::getPosition()
{
    return p;
}

string WorldObject::getID()
{
    return ID;
}

string WorldObject::getglyph()
{
    return glyph;
}
