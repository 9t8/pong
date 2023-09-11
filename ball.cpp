#include "ball.h"

Ball::Ball(sf::RenderWindow &w, const sf::SoundBuffer &bounce_buf)
    : RectangleShape(sf::Vector2f(w.getSize().y / 48, w.getSize().y / 48)),
      Y_BOUNDS(getSize().y / 2, w.getSize().y - getSize().y / 2),
      window(w),
      bounce(bounce_buf) {
    setOrigin(getSize() / 2.f);
}

void Ball::update(const sf::Time &dt) {
    move(vel * dt.asSeconds());

    float top_offset(Y_BOUNDS.first - getPosition().y);
    float bottom_offset(Y_BOUNDS.second - getPosition().y);
    if (top_offset >= 0) {
        bounce.play();

        move(0, 2 * top_offset);
        vel.y *= -1;
    } else if (bottom_offset <= 0) {
        bounce.play();

        move(0, 2 * bottom_offset);
        vel.y *= -1;
    }
}

void Ball::draw(const sf::Time &dt) {
    sf::Vector2f old_pos(getPosition());
    move(vel * dt.asSeconds());
    window.draw(*this);
    setPosition(old_pos);
}
