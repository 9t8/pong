#include "pong.h"

#include <cmath>

Pong::Pong(sf::RenderWindow &w)
    : window(w),
      score("0 - 0", source_code_pro),
      hit(click),
      player(w),
      bot(w),
      ball(w, click),
      play_area((player.getSize().x * 3 + ball.getSize().x) / 2,
                0,
                w.getSize().x - player.getSize().x * 3 - ball.getSize().x,
                w.getSize().y),
      difficulty(.75) {
    if (!source_code_pro.loadFromFile("assets/SourceCodePro-Regular.otf")
            || !click.loadFromFile("assets/Audio/click_003.ogg")) {
        throw std::runtime_error("could not load assets");
    }

    score.setPosition((window.getSize().x- score.getLocalBounds().width) / 2, 0);

    player.setPosition(player.getSize().x, window.getSize().y / 2);

    bot.setPosition(window.getSize().x - bot.getSize().x, window.getSize().y / 2);

    enter_pregame();
}

void Pong::update(const sf::Time &dt) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        default:
            break;
        }
    }

    if (pregame) {
        pregame_logic(dt);
    } else {
        game_logic(dt);
    }
}

void Pong::draw(const sf::Time &dt) {
    window.clear(sf::Color(0x121212ff));

    window.draw(score);

    player.draw(dt);
    bot.draw(dt);
    ball.draw(dt);
}

void Pong::enter_pregame() {
    ball.vel.x = 0;

    score.setString(std::to_string(player.score) + " - "
                    + std::to_string(bot.score));

    pregame = true;
}

void Pong::pregame_logic(const sf::Time &dt) {
    ball.vel.y = player.vel;

    move_objects(dt);

    ball.setPosition(play_area.left + player.getSize().x, player.getPosition().y);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        ball.vel.x = window.getSize().x * -difficulty;
        ball.vel.y = 0;

        pregame = false;
    }
}

void Pong::game_logic(const sf::Time &dt) {
    const bool ball_was_inside(play_area.contains(ball.getPosition()));

    move_objects(dt);

    if (ball_was_inside) {
        float left_offset(play_area.left - ball.getPosition().x);
        float right_offset(play_area.left + play_area.width
                           - ball.getPosition().x);
        if (left_offset >= 0 &&
                player.getGlobalBounds().intersects(ball.getGlobalBounds())) {
            hit.play();

            ball.move(2 * left_offset, 0);
            ball.vel.x *= -1;
            ball.vel.y = (player.vel + ball.vel.y) / 2;
        } else if (right_offset <= 0 &&
                   bot.getGlobalBounds().intersects(ball.getGlobalBounds())) {
            hit.play();

            ball.move(2 * right_offset, 0);
            ball.vel.x *= -1;
            ball.vel.y = (bot.vel + ball.vel.y) / 2;
        }
    }

    if (ball.getPosition().x < -ball.getSize().x) {
        ++bot.score;
        enter_pregame();
    } else if (ball.getPosition().x >= window.getSize().x + ball.getSize().x) {
        ++player.score;
        enter_pregame();
    }
}

void Pong::move_objects(const sf::Time &dt) {
    const float d_secs(dt.asSeconds());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.vel -= player.ACCEL * d_secs;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.vel += player.ACCEL * d_secs;
    }

    bot.vel += std::copysign(bot.ACCEL * difficulty * d_secs,
                             ball.getPosition().y - bot.getPosition().y);

    player.update(dt);
    bot.update(dt);
    ball.update(dt);
}
