#include "precompiled.h"
#include "game.h"

int main(int argc, char* argv[])
{
	using namespace mcomm;

    mcomm::MetaObjectManager::instance().bindClasses();
	Game::instance().setup();
	Game::instance().run();
	return 0;
}
