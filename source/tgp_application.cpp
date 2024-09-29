#include "tgp_application.h"

using namespace tgp;

Application::Application(sfmx::vec2u win_pos,
                         sfmx::vec2u win_size,
                         const char* window_name,
                         unsigned int fps,
                         std::unique_ptr<WindowManager> window_manager) 
    : render_window_(win_size, window_name),
      window_manager_(std::move(window_manager)) {

    render_window_.SetFramerateLimit(fps);
}

bool Application::IsRunning() {
    return render_window_.IsOpen();
}

void Application::Run() {
    sfmx::Event event{};
    if (render_window_.PollEvent(event)) {
        if (event.type == sfmx::Event::EventType::Closed) {
            render_window_.Close();
        }
    }

    render_window_.Clear();

    if (window_manager_ != nullptr) {
        window_manager_->Draw(&render_window_);
        window_manager_->Update(event, render_window_);
    }

    render_window_.Display();
}

//=========================== ApplicationBuilder ==============================

ApplicationBuilder::ApplicationBuilder()
    : win_pos_ (sfmx::vec2u(0, 0)),
      win_size_(sfmx::vec2u(800, 600)),
      window_name_("TGP_Application"),
      fps_(60),
      window_manager_(nullptr)
{}

ApplicationBuilder& ApplicationBuilder::SetWindowPosition(const sfmx::vec2u& win_pos) {
    win_pos_ = win_pos;
    return *this;
}

ApplicationBuilder& ApplicationBuilder::SetWindowSize(const sfmx::vec2u& win_size) {
    win_size_ = win_size;
    return *this;
}

ApplicationBuilder& ApplicationBuilder::SetWindowName(const char* window_name) {
    window_name_ = window_name;
    return *this;
}

ApplicationBuilder& ApplicationBuilder::SetFramerate(unsigned int fps) {
    fps_ = fps;
    return *this;
}

ApplicationBuilder& ApplicationBuilder::SetAdamWindow(std::unique_ptr<WindowManager> window_manager) {
    window_manager_ = std::move(window_manager);
    return *this;
}

Application ApplicationBuilder::Build() {
    return Application(win_pos_, win_size_, window_name_, fps_, std::move(window_manager_));
}
