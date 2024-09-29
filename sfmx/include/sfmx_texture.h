#ifndef SFMX_TEXTURE_H_
#define SFMX_TEXTURE_H_

#include <SFML/Graphics/Texture.hpp>

namespace sfmx {

struct IntRect {
    int pos_x;
    int pos_y;
    int size_x;
    int size_y;
};

class Texture {
public:
    bool LoadFromFile(const char* filename);

private:
    sf::Texture texture_;
};

}; // namespace

#endif // SFMX_TEXTURE_H_
