#include "test.h"

Test::Test(sf::RenderWindow &w)
    : window(w),
      rect(sf::Vector2f(200, 200)),
      triangle(50, 3),
      text("", source_code_pro, 48),
      drawables({ rect, triangle, box, text }),
      sound(select) {
    window.setVerticalSyncEnabled(true);

    if (!box_texture.loadFromFile("assets/Tiles/Marble/tile_0000.png") ||
            !source_code_pro.loadFromFile("assets/SourceCodePro-Regular.otf") ||
            !select.loadFromFile("assets/Audio/select_001.ogg") ||
            !music.openFromFile("assets/can_can.wav")) {
        throw std::runtime_error("could not load assets");
    }

    rect.setOrigin(rect.getSize() / 2.f);
    rect.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.f);
    rect.setTexture(&box_texture);

    triangle.setPosition(100, 100);
    triangle.setOutlineThickness(10);
    triangle.setOutlineColor(sf::Color(0x0000ffff));

    box.setTexture(box_texture);
    box.setOrigin(box.getTextureRect().width / 2.,
                  box.getTextureRect().height / 2.);
    box.setScale(5, 5);

    text.setFillColor(sf::Color(0xff0000ff));
    text.setPosition(window.getSize().x / 2, 0);

    sound.setPitch(.5);
    sound.play();

    music.setVolume(50);
    music.play();

    sf::err() << "exiting Test constructor" << std::endl;
}

void Test::update(const sf::Time &dt) {
    for (sf::Event event; window.pollEvent(event);) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                text.setString(std::to_string(event.mouseButton.x) + ", "
                               + std::to_string(event.mouseButton.y));
                text.setOrigin(static_cast<int>(
                                   text.getLocalBounds().width / 2),
                               0);
            }
            break;

        default:
            break;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        rect.rotate(-.2);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        rect.rotate(.2);
    }
    triangle.rotate(.2);
    box.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}

void Test::draw(const sf::Time &dt) {
    window.clear(sf::Color(0x121212ff));
    for (const sf::Drawable &e : drawables) {
        window.draw(e);
    }
}
