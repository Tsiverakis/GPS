#include <iostream>
#include <string>


using namespace std;

class Position {
    private:
        int x, y;
    public:
        Position()
        {
            this->x = -1;
            this->y = -1;
        }

        Position(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        void setX(int x)
        {
            this->x = x;
        }

        void setY(int y)
        {
            this->y = y;
        }

        int getX() const
        {
            return this->x;
        }

        int getY() const
        {
            return this->y;
        }
};

class MovingVehicle {
    private:
        Position pos;
        string type;
    protected:
        int speed;
        string direction;
    public:
        MovingVehicle(Position pos, string type, int speed, string direction)
        :pos(pos), type(type), speed(speed), direction(direction)
        {
            cout << "Moving Vehicle created at: " << getX() << ", " << getY() << endl; 
        }

        Position getPosition() const {
            return this->pos;
        }

        string getType() const {
            return this->type
        }

        int getSpeed() const {
            return this->speed;
        }

        strign getDirection() const {
            return this->direction;
        }

        ~MovingVehicle() {
            cout << "Moving Vehicle destroyed at: " << getX() << ", " << getY() << endl;
        }
};

class Car : public MovingVehicle {
    public:
        Car(Position pos, int speed, string direction)
        : MovingVehicle(pos, "Car", speed, direction) 
        {

        }
};

class Bike : public MovingVehicle {
    public:
        Bike(Position pos, int speed, string direction)
        : MovingVehicle(pos, "Bike", speed, direction) 
        {

        }
};


