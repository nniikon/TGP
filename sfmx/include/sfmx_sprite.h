#ifndef SFMX_SPRITE_H_
#define SFMX_SPRITE_H_

#include <SFML/Graphics/Sprite.hpp>
#include <cstdint>
#include "sfmx_texture.h"

namespace sfmx {

class FloatRect {
public:
    float pos_x;
    float pos_y;
    float size_x;
    float size_y;

    bool Contains(float x, float y) const;
};

class Sprite {
public:
    Sprite();
    Sprite(const Texture& texture, const IntRect& rectangle);

    void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    void SetPosition(float x, float y);
    void SetScale(float x, float y);
    void SetTexture(const Texture& texture);
    void SetTextureRect(const IntRect& rectangle);
    FloatRect GetGlobalBounds() const;

private:
    sf::Sprite sprite_;
};

}; // namespace

#endif // SFMX_SPRITE_H_
