#include "precompiled.h"
#include "game.h"
#include "bindings/external_types.h"
#include "bindings/bindings.h"

int main(int argc, char* argv[])
{
    using namespace mcomm;

    initBindings();
    Game::instance().setup();
    Game::instance().run();
    return 0;
}
