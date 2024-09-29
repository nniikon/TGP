#ifndef TGP_UPDATABLE_H_
#define TGP_UPDATABLE_H_

#include "sfmx_event.h"
#include "sfmx_render_window.h"

namespace tgp {

class Updatable {
public:
    virtual bool Update(const sfmx::Event& event,
                        const sfmx::RenderWindow& window) = 0;
};

}; // namespace

#endif // TGP_UPDATABLE_H_
