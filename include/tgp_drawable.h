#ifndef TGP_DRAWABLE_H_
#define TGP_DRAWABLE_H_

#include "sfmx_render_window.h"

namespace tgp {

class Drawable {
public:
    virtual void Draw(sfmx::RenderWindow* window) = 0;
};

}; // namespace

#endif // TGP_DRAWABLE_H_
