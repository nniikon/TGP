#include "sfmx_keyboard.h"

#include "SFML/Window/Keyboard.hpp"

bool isKeyPressed(sfmx::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}

bool isKeyPressed(sfmx::Keyboard::Scancode scan) {
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scancode>(scan));
}
