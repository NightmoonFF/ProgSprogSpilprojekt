#pragma once

#include <vector>

struct Position {
    float latitude;
    float longitude;
};

class Snake {
public:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Snake();
    void move();
    void grow();
    void setDirection(Direction dir);

    const std::vector<Position>& getBody() const;

private:
    std::vector<Position> body;
    Direction direction;
};
