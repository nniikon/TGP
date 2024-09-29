#include "sfmx_sprite.h"

sfmx::Sprite::Sprite(const sfmx::Texture& texture, const sfmx::IntRect& rectangle) 
    // FIXME:    bit_cast doesn't work
    : sprite_(*(sf::Texture*)(&texture), std::bit_cast<sf::IntRect>(rectangle)) {}

void sfmx::Sprite::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    sprite_.setColor(sf::Color(r, g, b, a));
}

void sfmx::Sprite::SetPosition(float x, float y) {
    sprite_.setPosition(x, y);
}

void sfmx::Sprite::SetScale(float x, float y) {
    sprite_.setScale(x, y);
}

bool sfmx::FloatRect::Contains(float x, float y) const {
    sf::FloatRect bounds = {pos_x, pos_y, size_x, size_y};
    return bounds.contains(x, y);
}

sfmx::FloatRect sfmx::Sprite::GetGlobalBounds() const {
    sf::FloatRect bounds = sprite_.getGlobalBounds();
    return *(sfmx::FloatRect*)(&bounds);
}
