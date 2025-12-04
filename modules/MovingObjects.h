#include <iostream>

class Position {
    private:
        int x, y;
    public:
        Position() {
            x = -1;
            y = - 1;
        }

        Position(int x, int y) {
            this->x = x;
            this->y = y;
        }

        void setX(int x) {
            this->x = x;
        }

        void setY(int y) {
            this->y  = y;
        }

        int getX() const {
            return this->x;
        }

        int getY() const {
            return this->y;
        }
};