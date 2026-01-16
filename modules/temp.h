#ifndef TEMP
#define TEMP

#include <string>
#include <vector>

extern int max_value;

// holds a 2d possition x,y
class Position
{
private:
    int x, y;

public:
    Position();

    Position(int x, int y);

    void setX(int x);

    void setY(int y);

    int getX() const;

    int getY() const;
};

class WorldObject
{
protected:
    Position p;
    std::string type;
    std::string ID;
    std::string glyph;

public:
    // constructor
    WorldObject(std:: string type, std::string ID, std::string glyph, int x, int y);

    // destructor
    virtual ~WorldObject() = 0;
    std::string getType();
    Position getPosition();
    std::string getID();
    std::string getglyph();
};

struct ReadData
{
    std::string type;
    int distance;
    Position p;
    std::string objectid; // category of object
    double confidence;
    int speed;
    std::string direction;
    std::string signtext;
    std::string trafficlightp;
};
#endif