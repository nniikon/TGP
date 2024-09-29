#include "tgp_button.h"

using namespace tgp;

void ButtonSpriteBase::Draw(sfmx::RenderWindow* window) {
    window->Draw(sprite_);
}

ButtonSpriteBase::ButtonSpriteBase(const sfmx::Sprite& sprite)
    : sprite_(sprite) {}
