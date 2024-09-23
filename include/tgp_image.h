#ifndef TGP_IMAGE_H_
#define TGP_IMAGE_H_

#include <SFML/Graphics.hpp>

#include "tgp_manager.h"

namespace TGP {

class ImageBase : public Drawable {
public:
    virtual ~ImageBase() = default;
};

class ImageSprite : public ImageBase {
public:
    void Draw(sf::RenderWindow* window) override;

    ImageSprite(const sf::Sprite& sprite);

private:
    sf::Sprite sprite_;
};

} // namespace 

#endif // TGP_IMAGE_H_

