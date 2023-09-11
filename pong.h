#ifndef PONG_H
#define PONG_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ball.h"
#include "paddle.h"

class Pong {
public:
    Pong(sf::RenderWindow &w);

    void update(const sf::Time &dt);

    void draw(const sf::Time &dt);

private:
    void enter_pregame();

    void pregame_logic(const sf::Time &dt);

    void game_logic(const sf::Time &dt);

    void move_objects(const sf::Time &dt);

    sf::RenderWindow &window;

    sf::Font source_code_pro;

    sf::Text score;

    sf::SoundBuffer click;

    sf::Sound hit;

    Paddle player, bot;

    Ball ball;

    sf::FloatRect play_area;

    float difficulty;

    bool pregame;
};

#endif // PONG_H
