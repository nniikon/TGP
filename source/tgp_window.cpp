#include "tgp_window.h"

using namespace tgp;

void WindowContainerBase::AddWindow(std::unique_ptr<WindowBase> window) {
    windows_.emplace_back(std::move(window));
}

void WindowManager::SetMainWindow(std::unique_ptr<WindowBase> window) {
    main_window_ = std::move(window);
}
