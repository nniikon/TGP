#include "sfmx_render_window.h"

sfmx::RenderWindow::RenderWindow(sfmx::vec2u size, const char* name)
    : render_window_(sf::VideoMode(size.x, size.y), name) {}

void sfmx::RenderWindow::SetFramerateLimit(unsigned int fps) {
    return render_window_.setFramerateLimit(fps);
}

bool sfmx::RenderWindow::IsOpen() {
    return render_window_.isOpen();
}

bool sfmx::RenderWindow::PollEvent(sfmx::Event& event) {
    sf::Event sfml_event{};
    bool ret_value = render_window_.pollEvent(sfml_event);

    if (ret_value) {
        event = std::bit_cast<sfmx::Event>(sfml_event);
    }

    return ret_value;
}

void sfmx::RenderWindow::Draw(const sfmx::Sprite& sprite) {
    render_window_.draw(*(sf::Sprite*)(&sprite));
}

void sfmx::RenderWindow::Display() {
    render_window_.display();
}

void sfmx::RenderWindow::Close() {
    render_window_.close();
}

void sfmx::RenderWindow::Clear() {
    render_window_.clear();
}

const void* sfmx::RenderWindow::____GetInternalImplementation____() const {return &render_window_;}
