#include "sfmx_mouse.h"

sfmx::vec2i  CastVector(sf::Vector2i vec) { return std::bit_cast<sfmx::vec2i >(vec); }
sf::Vector2i CastVector(sfmx::vec2i vec)  { return std::bit_cast<sf::Vector2i>(vec); }

bool sfmx::Mouse::IsButtonPressed(Button button) {
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
}

sfmx::vec2i sfmx::Mouse::GetPosition() {
    return CastVector(sf::Mouse::getPosition());
}

sfmx::vec2i sfmx::Mouse::GetPosition(const RenderWindow& relativeTo) {
    const sf::RenderWindow* render_window =
        static_cast<const sf::RenderWindow*>(relativeTo.____GetInternalImplementation____());

    return CastVector(sf::Mouse::getPosition(*render_window));
}

void sfmx::Mouse::SetPosition(const vec2i& position) {
    return sf::Mouse::setPosition(CastVector(position));
}

void sfmx::Mouse::SetPosition(const vec2i& position, const RenderWindow& relativeTo) {
    const sf::RenderWindow* render_window =
        static_cast<const sf::RenderWindow*>(relativeTo.____GetInternalImplementation____());

    return sf::Mouse::setPosition(CastVector(position), *render_window);
}
