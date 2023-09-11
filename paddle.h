#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle : public sf::RectangleShape {
public:
    Paddle(sf::RenderWindow &w);

    void update(const sf::Time &dt);

    void draw(const sf::Time &dt);

    const int ACCEL;

    float vel;

    int score;

private:
    static const float FRICTION;

    sf::RenderWindow &window;

    const std::pair<float, float> BOUNDS;
};

#endif // PADDLE_H
