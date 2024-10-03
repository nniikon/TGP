#include "tgp_button.h"

using namespace tgp;

ButtonBase::ButtonBase(std::unique_ptr<Action> action)
    : action_(std::move(action)) {}

void ButtonSpriteBase::Draw(sfmx::RenderWindow* window) {
    window->Draw(sprite_);
}

ButtonSpriteBase::ButtonSpriteBase(const sfmx::Sprite& sprite,
                                   std::unique_ptr<Action> action)
    : ButtonBase(std::move(action)),
      sprite_(sprite) {}
