#include "tgp_image.h"

using namespace TGP;

ImageSprite::ImageSprite(const sf::Sprite& sprite)
    : sprite_(sprite) {}

void ImageSprite::Draw(sf::RenderWindow* window) {
    window->draw(sprite_);
}
