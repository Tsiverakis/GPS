#include <iostream>

using namespace std;

//holds a 2d possition x,y
class Position
{
private:
    int x, y;

public:
    Position()
    {
        this -> x = -1;
        this -> y = -1;
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


//It is a stationary vehicle at Position x,y
class StationaryVehicle: public Position{
    public:
        //constructor
        StationaryVehicle(int x, int y)
        :Position(x,y)
        {
            cout << "Stationary vehicle created at: " << getX() << "," << getY() << endl;
            
        }

        //destructor
        ~StationaryVehicle(){
            cout << "Stationary vehicle destroyed at: " << getX() << "," << getY() << endl;
        }
};

//It is a traffic sign with an ID and a Position x,y
class TrafficSign: public Position{
    public:
        string signID;//type of sign

        //constructor
        TrafficSign(int x , int y , string signID)
        :Position(x,y)
        {
            this -> signID = signID;

            cout << "Sign " << get_ID() << " created at: " << getX() << "," << getY() << endl;
        }

        //destructor
        ~TrafficSign(){
            cout << "Sign " << get_ID() << " destroyed at: " << getX() << "," << getY() << endl;
        }

        string get_ID(){ return signID; }//returns the type of the sign
};

//It is a traffic light with a color(state) and a Position x,y
class TrafficLight: public Position{
    public:
        string state;//holds the color of the traffic light

        //constructor
        TrafficLight(int x , int y, string state)
        :Position(x,y)
        {
            this -> state = state;

            cout << "Traffic light " << get_State() << " created at: " << getX() << "," << getY() << endl;
        }

        //destructor
        ~TrafficLight(){
            cout << "Traffic light " << get_State() << " destroyed at: " << getX() << "," << getY() << endl;
        }

        string get_State(){ return state; }//returns the color of the traffic light
};

// int main(){
//     StationaryVehicle sv = StationaryVehicle(1,2);
//     TrafficSign ts = TrafficSign(2,3,"STOP");
//     TrafficLight tl = TrafficLight(4,5,"RED");

// }