#include "Snake.h"

Snake::Snake() {
    body.push_back({ 0.0f, 0.0f });  // Start at equator and prime meridian
    direction = RIGHT;
}

void Snake::move() {
    Position newHead = body.front();
    switch (direction) {
    case UP:    newHead.latitude += 0.1f; break;
    case DOWN:  newHead.latitude -= 0.1f; break;
    case LEFT:  newHead.longitude -= 0.1f; break;
    case RIGHT: newHead.longitude += 0.1f; break;
    }
    body.insert(body.begin(), newHead);
    body.pop_back();
}

void Snake::grow() {
    body.push_back(body.back());  // Temporary grow
}

void Snake::setDirection(Direction dir) {
    direction = dir;
}

const std::vector<Position>& Snake::getBody() const {
    return body;
}
