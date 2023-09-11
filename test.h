#ifndef TEST_H
#define TEST_H

#include <functional>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Test {
public:
    Test(sf::RenderWindow &w);

    void update(const sf::Time &dt);

    void draw(const sf::Time &dt);

private:
    sf::RenderWindow &window;

    sf::Texture box_texture;
    sf::Font source_code_pro;
    sf::SoundBuffer select;
    sf::Music music;

    sf::RectangleShape rect;
    sf::CircleShape triangle;
    sf::Sprite box;
    sf::Text text;

    const std::vector<std::reference_wrapper<sf::Drawable>> drawables;

    sf::Sound sound;
};

#endif // TEST_H
