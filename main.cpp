#include "pong.h"
#include "test.h"

int main() {
    sf::RenderWindow w(sf::VideoMode(1280, 720), "Pong");
    Pong scene(w); // replace with Test for testing
    sf::Time game_time(sf::Time::Zero);

    const sf::Clock clock;
    for (;;) {
        sf::Time time(clock.getElapsedTime());

        static const sf::Time UPDATE_ITVL(sf::seconds(.002));
        for (; time - game_time >= UPDATE_ITVL; game_time += UPDATE_ITVL) {
            scene.update(UPDATE_ITVL);
            if (!w.isOpen()) {
                return 0;
            }
        }

        scene.draw(time - game_time);
        w.display();
    }
}
