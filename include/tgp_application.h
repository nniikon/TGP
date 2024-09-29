#ifndef TGP_APPLICATION_H_
#define TGP_APPLICATION_H_

#include "sfmx_render_window.h"
#include "sfmx_vectors.h"

#include "tgp_window.h"

namespace tgp {

//=============================== Application =================================

class Application {
public:
    bool IsRunning();
    void Run();

    Application(sfmx::vec2u win_pos,
                sfmx::vec2u win_size,
                const char* window_name,
                unsigned int fps,
                std::unique_ptr<WindowManager> window_manager);
    ~Application() = default;

private:
    sfmx::RenderWindow             render_window_;
    std::unique_ptr<WindowManager> window_manager_;
};

//=========================== ApplicationBuilder ==============================

class ApplicationBuilder {
public:
    ApplicationBuilder();

    ApplicationBuilder& SetWindowPosition(const sfmx::vec2u& win_pos);
    ApplicationBuilder& SetWindowSize    (const sfmx::vec2u& win_size);
    ApplicationBuilder& SetWindowName(const char* window_name);
    ApplicationBuilder& SetFramerate(unsigned int fps);
    ApplicationBuilder& SetAdamWindow(std::unique_ptr<WindowManager> window_manager);

    Application Build();

private:
    sfmx::vec2u win_pos_;
    sfmx::vec2u win_size_;
    const char* window_name_;
    unsigned int fps_;
    std::unique_ptr<WindowManager> window_manager_;
};

}; // namespace

#endif // TGP_APPLICATION_H_
