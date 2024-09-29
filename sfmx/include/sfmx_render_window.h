#ifndef SFMX_RENDER_WINDOW_H_
#define SFMX_RENDER_WINDOW_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "sfmx_event.h"
#include "sfmx_sprite.h"
#include "sfmx_vectors.h"

namespace sfmx {

class RenderWindow {
public:
    RenderWindow(vec2u size, const char* name);
    void SetFramerateLimit(unsigned int fps);
    bool IsOpen();
    bool PollEvent(sfmx::Event& event);
    void Draw(const sfmx::Sprite& sprite);
    void Display();
    void Close();
    void Clear();

    const void* ____GetInternalImplementation____() const;

private:
    sf::RenderWindow render_window_;
};

}; // namespace

#endif // SFMX_RENDER_WINDOW_H_
