#ifndef BALL_H
#define BALL_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Ball : public sf::RectangleShape {
public:
    Ball(sf::RenderWindow &w, const sf::SoundBuffer &bounce_buf);

    void update(const sf::Time &dt);

    void draw(const sf::Time &dt);

    sf::Vector2f vel;

private:
    const std::pair<float, float> Y_BOUNDS;

    sf::RenderWindow &window;

    sf::Sound bounce;
};

#endif // BALL_H
