#ifndef TGP_BUTTON_H_
#define TGP_BUTTON_H_

#include "tgp_action.h"
#include "tgp_window.h"

namespace tgp {

class ButtonBase : public WindowBase {
public:
    virtual void OnHover  () = 0;
    virtual void OnIdle   () = 0;
    virtual void OnPress  () = 0;
    virtual void OnRelease() = 0;

    ButtonBase(std::unique_ptr<Action> action);
    virtual ~ButtonBase() = default;

protected:
    std::unique_ptr<Action> action_;
};

class ButtonSpriteBase : public ButtonBase {
public:
    void Draw(sfmx::RenderWindow* window) override;

    ButtonSpriteBase(const sfmx::Sprite& sprite,
                     std::unique_ptr<Action> action);
    ~ButtonSpriteBase() override = default;

protected:
    sfmx::Sprite sprite_;
};

} // namespace

#endif // TGP_BUTTON_H_
