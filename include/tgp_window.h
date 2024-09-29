#ifndef TGP_WINDOW_H_
#define TGP_WINDOW_H_

#include "tgp_drawable.h"
#include "tgp_updatable.h"
#include <memory>

namespace tgp {

class WindowBase : public Drawable, public Updatable { 
    
};

class WindowContainerBase : public WindowBase { 
protected:
    std::vector<std::unique_ptr<WindowBase>> windows_;
};

class WindowManager : public Drawable, public Updatable { 
public:
    void SetMainWindow(std::unique_ptr<WindowBase> window);

protected:
    std::unique_ptr<WindowBase> main_window_;
};

}; // namespace

#endif // TGP_WINDOW_H_
