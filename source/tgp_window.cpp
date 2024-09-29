#include "tgp_window.h"

using namespace tgp;

void WindowManager::SetMainWindow(std::unique_ptr<WindowBase> window) {
    main_window_ = std::move(window);
}
