#include "tgp_action.h"

using namespace tgp;

void Action::operator()() {
    SaveState();
    Do();
}
