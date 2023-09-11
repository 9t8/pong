#include "paddle.h"

#include <cmath>

Paddle::Paddle(sf::RenderWindow &w)
    : RectangleShape(sf::Vector2f(w.getSize().y / 64, w.getSize().y / 8)),
      ACCEL(w.getSize().y * 8),
      vel(0),
      window(w),
      score(0),
      BOUNDS(getSize().y / 2, w.getSize().y - getSize().y / 2) {
    setOrigin(getSize() / 2.f);
}

void Paddle::update(const sf::Time &dt) {
    const float d_secs(dt.asSeconds());

    move(0, vel * d_secs);

    float top_offset(BOUNDS.first - getPosition().y);
    float bottom_offset(BOUNDS.second - getPosition().y);
    if (top_offset > 0) {
        move(0, top_offset);
        vel = 0;
    } else if (bottom_offset < 0) {
        move(0, bottom_offset);
        vel = 0;
    } else {
        vel /= std::pow(FRICTION, d_secs);
    }
}

void Paddle::draw(const sf::Time &dt) {
    const float d_secs(dt.asSeconds());

    sf::Vector2f old_pos(getPosition());
    move(0, vel * d_secs);
    window.draw(*this);
    setPosition(old_pos);
}

const float Paddle::FRICTION(64);
